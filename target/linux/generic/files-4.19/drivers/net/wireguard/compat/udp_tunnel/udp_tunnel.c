#include <linux/module.h>
#include <linux/errno.h>
#include <linux/socket.h>
#include <linux/udp.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <net/net_namespace.h>
#include <net/inet_common.h>
#include <net/udp.h>
#include <net/udp_tunnel.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 12, 0)
#define __sk_user_data(sk) ((*((void __rcu **)&(sk)->sk_user_data)))
#define rcu_dereference_sk_user_data(sk) rcu_dereference(__sk_user_data((sk)))
#define rcu_assign_sk_user_data(sk, ptr) rcu_assign_pointer(__sk_user_data((sk)), ptr)
#endif

/* This is global so, uh, only one real call site... This is the kind of horrific hack you'd expect to see in compat code. */
static udp_tunnel_encap_rcv_t encap_rcv = NULL;
static void __compat_sk_data_ready(struct sock *sk
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 15, 0)
			      ,int unused_vulnerable_length_param
#endif
			      )
{
	struct sk_buff *skb;
	while ((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL) {
		skb_orphan(skb);
		sk_mem_reclaim(sk);
		encap_rcv(sk, skb);
	}
}

int udp_sock_create4(struct net *net, struct udp_port_cfg *cfg,
		     struct socket **sockp)
{
	int err;
	struct socket *sock = NULL;
	struct sockaddr_in udp_addr;

	err = __sock_create(net, AF_INET, SOCK_DGRAM, 0, &sock, 1);
	if (err < 0)
		goto error;

	udp_addr.sin_family = AF_INET;
	udp_addr.sin_addr = cfg->local_ip;
	udp_addr.sin_port = cfg->local_udp_port;
	err = kernel_bind(sock, (struct sockaddr *)&udp_addr,
			  sizeof(udp_addr));
	if (err < 0)
		goto error;

	if (cfg->peer_udp_port) {
		udp_addr.sin_family = AF_INET;
		udp_addr.sin_addr = cfg->peer_ip;
		udp_addr.sin_port = cfg->peer_udp_port;
		err = kernel_connect(sock, (struct sockaddr *)&udp_addr,
				     sizeof(udp_addr), 0);
		if (err < 0)
			goto error;
	}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 16, 0)
	sock->sk->sk_no_check = !cfg->use_udp_checksums;
#else
	sock->sk->sk_no_check_tx = !cfg->use_udp_checksums;
#endif

	*sockp = sock;
	return 0;

error:
	if (sock) {
		kernel_sock_shutdown(sock, SHUT_RDWR);
		sock_release(sock);
	}
	*sockp = NULL;
	return err;
}

void setup_udp_tunnel_sock(struct net *net, struct socket *sock,
			   struct udp_tunnel_sock_cfg *cfg)
{
	inet_sk(sock->sk)->mc_loop = 0;
	encap_rcv = cfg->encap_rcv;
	rcu_assign_sk_user_data(sock->sk, cfg->sk_user_data);
	/* We force the cast in this awful way, due to various Android kernels
	 * backporting things stupidly. */
	*(void **)&sock->sk->sk_data_ready = (void *)__compat_sk_data_ready;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 16, 0)
static inline __sum16 udp_v4_check(int len, __be32 saddr,
				   __be32 daddr, __wsum base)
{
	return csum_tcpudp_magic(saddr, daddr, len, IPPROTO_UDP, base);
}

static void udp_set_csum(bool nocheck, struct sk_buff *skb,
		  __be32 saddr, __be32 daddr, int len)
{
	struct udphdr *uh = udp_hdr(skb);

	if (nocheck)
		uh->check = 0;
	else if (skb_is_gso(skb))
		uh->check = ~udp_v4_check(len, saddr, daddr, 0);
	else if (skb_dst(skb) && skb_dst(skb)->dev &&
		 (skb_dst(skb)->dev->features & NETIF_F_V4_CSUM)) {

		BUG_ON(skb->ip_summed == CHECKSUM_PARTIAL);

		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = offsetof(struct udphdr, check);
		uh->check = ~udp_v4_check(len, saddr, daddr, 0);
	} else {
		__wsum csum;

		BUG_ON(skb->ip_summed == CHECKSUM_PARTIAL);

		uh->check = 0;
		csum = skb_checksum(skb, 0, len, 0);
		uh->check = udp_v4_check(len, saddr, daddr, csum);
		if (uh->check == 0)
			uh->check = CSUM_MANGLED_0;

		skb->ip_summed = CHECKSUM_UNNECESSARY;
	}
}

#endif

static void __compat_fake_destructor(struct sk_buff *skb)
{
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 11, 0)
static void __compat_iptunnel_xmit(struct rtable *rt, struct sk_buff *skb,
		  __be32 src, __be32 dst, __u8 proto,
		  __u8 tos, __u8 ttl, __be16 df, bool xnet)
{
	struct iphdr *iph;
	struct pcpu_tstats *tstats = this_cpu_ptr(skb->dev->tstats);

	skb_scrub_packet(skb, xnet);

	skb->rxhash = 0;
	skb_dst_set(skb, &rt->dst);
	memset(IPCB(skb), 0, sizeof(*IPCB(skb)));

	/* Push down and install the IP header. */
	skb_push(skb, sizeof(struct iphdr));
	skb_reset_network_header(skb);

	iph = ip_hdr(skb);

	iph->version	=	4;
	iph->ihl	=	sizeof(struct iphdr) >> 2;
	iph->frag_off	=	df;
	iph->protocol	=	proto;
	iph->tos	=	tos;
	iph->daddr	=	dst;
	iph->saddr	=	src;
	iph->ttl	=	ttl;
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 53)
	__ip_select_ident(iph, &rt->dst, (skb_shinfo(skb)->gso_segs ?: 1) - 1);
#else
	__ip_select_ident(iph, skb_shinfo(skb)->gso_segs ?: 1);
#endif

	iptunnel_xmit(skb, skb->dev);
	u64_stats_update_begin(&tstats->syncp);
	tstats->tx_bytes -= 8;
	u64_stats_update_end(&tstats->syncp);
}
#define iptunnel_xmit __compat_iptunnel_xmit
#endif

void udp_tunnel_xmit_skb(struct rtable *rt, struct sock *sk, struct sk_buff *skb,
			 __be32 src, __be32 dst, __u8 tos, __u8 ttl,
			 __be16 df, __be16 src_port, __be16 dst_port,
			 bool xnet, bool nocheck)
{
	struct udphdr *uh;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 11, 0)
	struct net_device *dev = skb->dev;
	int ret;
#endif

	__skb_push(skb, sizeof(*uh));
	skb_reset_transport_header(skb);
	uh = udp_hdr(skb);

	uh->dest = dst_port;
	uh->source = src_port;
	uh->len = htons(skb->len);

	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));

	udp_set_csum(nocheck, skb, src, dst, skb->len);

	if (!skb->sk)
		skb->sk = sk;
	if (!skb->destructor)
		skb->destructor = __compat_fake_destructor;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 11, 0)
	ret =
#endif
	     iptunnel_xmit(
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0)
			   sk,
#endif
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 12, 0) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 11, 0)
			   dev_net(dev),
#endif
			   rt, skb, src, dst, IPPROTO_UDP, tos, ttl, df
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 12, 0) || LINUX_VERSION_CODE < KERNEL_VERSION(3, 11, 0)
			   , xnet
#endif
	     );
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 11, 0)
	if (ret)
		iptunnel_xmit_stats(ret - 8, &dev->stats, dev->tstats);
#endif
}

void udp_tunnel_sock_release(struct socket *sock)
{
	rcu_assign_sk_user_data(sock->sk, NULL);
	kernel_sock_shutdown(sock, SHUT_RDWR);
	sock_release(sock);
}

#if IS_ENABLED(CONFIG_IPV6)
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/socket.h>
#include <linux/udp.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/in6.h>
#include <net/udp.h>
#include <net/udp_tunnel.h>
#include <net/net_namespace.h>
#include <net/netns/generic.h>
#include <net/ip6_tunnel.h>
#include <net/ip6_checksum.h>

int udp_sock_create6(struct net *net, struct udp_port_cfg *cfg,
		     struct socket **sockp)
{
	struct sockaddr_in6 udp6_addr;
	int err;
	struct socket *sock = NULL;

	err = __sock_create(net, AF_INET6, SOCK_DGRAM, 0, &sock, 1);
	if (err < 0)
		goto error;

	if (cfg->ipv6_v6only) {
		int val = 1;

		err = kernel_setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY,
					(char *) &val, sizeof(val));
		if (err < 0)
			goto error;
	}

	udp6_addr.sin6_family = AF_INET6;
	memcpy(&udp6_addr.sin6_addr, &cfg->local_ip6,
	       sizeof(udp6_addr.sin6_addr));
	udp6_addr.sin6_port = cfg->local_udp_port;
	err = kernel_bind(sock, (struct sockaddr *)&udp6_addr,
			  sizeof(udp6_addr));
	if (err < 0)
		goto error;

	if (cfg->peer_udp_port) {
		udp6_addr.sin6_family = AF_INET6;
		memcpy(&udp6_addr.sin6_addr, &cfg->peer_ip6,
		       sizeof(udp6_addr.sin6_addr));
		udp6_addr.sin6_port = cfg->peer_udp_port;
		err = kernel_connect(sock,
				     (struct sockaddr *)&udp6_addr,
				     sizeof(udp6_addr), 0);
	}
	if (err < 0)
		goto error;

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 16, 0)
	sock->sk->sk_no_check = !cfg->use_udp_checksums;
#else
	udp_set_no_check6_tx(sock->sk, !cfg->use_udp6_tx_checksums);
	udp_set_no_check6_rx(sock->sk, !cfg->use_udp6_rx_checksums);
#endif

	*sockp = sock;
	return 0;

error:
	if (sock) {
		kernel_sock_shutdown(sock, SHUT_RDWR);
		sock_release(sock);
	}
	*sockp = NULL;
	return err;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 16, 0)
static inline __sum16 udp_v6_check(int len,
		const struct in6_addr *saddr,
		const struct in6_addr *daddr,
		__wsum base)
{
	return csum_ipv6_magic(saddr, daddr, len, IPPROTO_UDP, base);
}
static void udp6_set_csum(bool nocheck, struct sk_buff *skb,
		   const struct in6_addr *saddr,
		   const struct in6_addr *daddr, int len)
{
	struct udphdr *uh = udp_hdr(skb);

	if (nocheck)
		uh->check = 0;
	else if (skb_is_gso(skb))
		uh->check = ~udp_v6_check(len, saddr, daddr, 0);
	else if (skb_dst(skb) && skb_dst(skb)->dev &&
		 (skb_dst(skb)->dev->features & NETIF_F_IPV6_CSUM)) {

		BUG_ON(skb->ip_summed == CHECKSUM_PARTIAL);

		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = offsetof(struct udphdr, check);
		uh->check = ~udp_v6_check(len, saddr, daddr, 0);
	} else {
		__wsum csum;

		BUG_ON(skb->ip_summed == CHECKSUM_PARTIAL);

		uh->check = 0;
		csum = skb_checksum(skb, 0, len, 0);
		uh->check = udp_v6_check(len, saddr, daddr, csum);
		if (uh->check == 0)
			uh->check = CSUM_MANGLED_0;

		skb->ip_summed = CHECKSUM_UNNECESSARY;
	}
}
#endif

int udp_tunnel6_xmit_skb(struct dst_entry *dst, struct sock *sk,
			 struct sk_buff *skb,
			 struct net_device *dev, struct in6_addr *saddr,
			 struct in6_addr *daddr,
			 __u8 prio, __u8 ttl, __be32 label,
			 __be16 src_port, __be16 dst_port, bool nocheck)
{
	struct udphdr *uh;
	struct ipv6hdr *ip6h;

	__skb_push(skb, sizeof(*uh));
	skb_reset_transport_header(skb);
	uh = udp_hdr(skb);

	uh->dest = dst_port;
	uh->source = src_port;

	uh->len = htons(skb->len);

	skb_dst_set(skb, dst);

	udp6_set_csum(nocheck, skb, saddr, daddr, skb->len);

	__skb_push(skb, sizeof(*ip6h));
	skb_reset_network_header(skb);
	ip6h		  = ipv6_hdr(skb);
	ip6_flow_hdr(ip6h, prio, label);
	ip6h->payload_len = htons(skb->len);
	ip6h->nexthdr     = IPPROTO_UDP;
	ip6h->hop_limit   = ttl;
	ip6h->daddr	  = *daddr;
	ip6h->saddr	  = *saddr;

	if (!skb->sk)
		skb->sk = sk;
	if (!skb->destructor)
		skb->destructor = __compat_fake_destructor;

	ip6tunnel_xmit(skb, dev);
	return 0;
}
#endif
