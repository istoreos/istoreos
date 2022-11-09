/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0)
#define udp_sock_create4 udp_sock_create
#define udp_sock_create6 udp_sock_create
#include <linux/socket.h>
#include <linux/if.h>
#include <linux/in.h>
#include <net/ip_tunnels.h>
#include <net/udp.h>
#include <net/inet_common.h>
#if IS_ENABLED(CONFIG_IPV6)
#include <linux/in6.h>
#include <net/ipv6.h>
#include <net/addrconf.h>
#include <net/ip6_checksum.h>
#include <net/ip6_tunnel.h>
#endif
static inline void __compat_fake_destructor(struct sk_buff *skb)
{
}
typedef int (*udp_tunnel_encap_rcv_t)(struct sock *sk, struct sk_buff *skb);
struct udp_tunnel_sock_cfg {
        void *sk_user_data;
        __u8  encap_type;
        udp_tunnel_encap_rcv_t encap_rcv;
};
/* This is global so, uh, only one real call site... This is the kind of horrific hack you'd expect to see in compat code. */
static udp_tunnel_encap_rcv_t encap_rcv = NULL;
static void __compat_sk_data_ready(struct sock *sk)
{
	struct sk_buff *skb;
	while ((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL) {
		skb_orphan(skb);
		sk_mem_reclaim(sk);
		encap_rcv(sk, skb);
	}
}
static inline void setup_udp_tunnel_sock(struct net *net, struct socket *sock,
                           struct udp_tunnel_sock_cfg *cfg)
{
	struct sock *sk = sock->sk;
	inet_sk(sk)->mc_loop = 0;
	encap_rcv = cfg->encap_rcv;
	rcu_assign_sk_user_data(sk, cfg->sk_user_data);
	sk->sk_data_ready = __compat_sk_data_ready;
}
static inline void udp_tunnel_sock_release(struct socket *sock)
{
	rcu_assign_sk_user_data(sock->sk, NULL);
	kernel_sock_shutdown(sock, SHUT_RDWR);
	sk_release_kernel(sock->sk);
}
static inline int udp_tunnel_xmit_skb(struct socket *sock, struct rtable *rt,
                        struct sk_buff *skb, __be32 src, __be32 dst,
                        __u8 tos, __u8 ttl, __be16 df, __be16 src_port,
                        __be16 dst_port, bool xnet)
{
	struct udphdr *uh;
	__skb_push(skb, sizeof(*uh));
	skb_reset_transport_header(skb);
	uh = udp_hdr(skb);
	uh->dest = dst_port;
	uh->source = src_port;
	uh->len = htons(skb->len);
	udp_set_csum(sock->sk->sk_no_check_tx, skb, src, dst, skb->len);
	return iptunnel_xmit(sock->sk, rt, skb, src, dst, IPPROTO_UDP,
			     tos, ttl, df, xnet);
}
#if IS_ENABLED(CONFIG_IPV6)
static inline int udp_tunnel6_xmit_skb(struct socket *sock, struct dst_entry *dst,
                         struct sk_buff *skb, struct net_device *dev,
                         struct in6_addr *saddr, struct in6_addr *daddr,
                         __u8 prio, __u8 ttl, __be16 src_port,
                         __be16 dst_port)
{
	struct udphdr *uh;
	struct ipv6hdr *ip6h;
	struct sock *sk = sock->sk;
	__skb_push(skb, sizeof(*uh));
	skb_reset_transport_header(skb);
	uh = udp_hdr(skb);
	uh->dest = dst_port;
	uh->source = src_port;
	uh->len = htons(skb->len);
	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
	IPCB(skb)->flags &= ~(IPSKB_XFRM_TUNNEL_SIZE | IPSKB_XFRM_TRANSFORMED
			    | IPSKB_REROUTED);
	skb_dst_set(skb, dst);
	udp6_set_csum(udp_get_no_check6_tx(sk), skb, &inet6_sk(sk)->saddr,
	              &sk->sk_v6_daddr, skb->len);
	__skb_push(skb, sizeof(*ip6h));
	skb_reset_network_header(skb);
	ip6h		  = ipv6_hdr(skb);
	ip6_flow_hdr(ip6h, prio, htonl(0));
	ip6h->payload_len = htons(skb->len);
	ip6h->nexthdr     = IPPROTO_UDP;
	ip6h->hop_limit   = ttl;
	ip6h->daddr	  = *daddr;
	ip6h->saddr	  = *saddr;
	ip6tunnel_xmit(skb, dev);
	return 0;
}
#endif
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 0, 0) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
#include <linux/in.h>
#include <linux/in6.h>
#include <linux/udp.h>
#include <linux/skbuff.h>
#include <linux/if.h>
#include <net/udp_tunnel.h>
#define udp_tunnel_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l) do { struct net_device *dev__ = (c)->dev; int ret__; ret__ = udp_tunnel_xmit_skb((b)->sk_socket, a, c, d, e, f, g, h, i, j, k); if (ret__) iptunnel_xmit_stats(ret__ - 8, &dev__->stats, dev__->tstats); } while (0)
#if IS_ENABLED(CONFIG_IPV6)
#define udp_tunnel6_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l) udp_tunnel6_xmit_skb((b)->sk_socket, a, c, d, e, f, g, h, j, k);
#endif
#elif LINUX_VERSION_CODE < KERNEL_VERSION(4, 1, 0) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
#include <linux/if.h>
#include <net/udp_tunnel.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 18, 0)
static inline void __compat_fake_destructor(struct sk_buff *skb)
{
}
#endif
#define udp_tunnel_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l) do { struct net_device *dev__ = (c)->dev; int ret__; if (!(c)->destructor) (c)->destructor = __compat_fake_destructor; if (!(c)->sk) (c)->sk = (b); ret__ = udp_tunnel_xmit_skb(a, c, d, e, f, g, h, i, j, k, l); if (ret__) iptunnel_xmit_stats(ret__ - 8, &dev__->stats, dev__->tstats); } while (0)
#if IS_ENABLED(CONFIG_IPV6)
#define udp_tunnel6_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l) do { if (!(c)->destructor) (c)->destructor = __compat_fake_destructor; if (!(c)->sk) (c)->sk = (b); udp_tunnel6_xmit_skb(a, c, d, e, f, g, h, j, k, l); } while(0)
#endif
#else

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 3, 0) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
#include <linux/if.h>
#include <net/udp_tunnel.h>
#define udp_tunnel_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l) do { struct net_device *dev__ = (c)->dev; int ret__ = udp_tunnel_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l); if (ret__) iptunnel_xmit_stats(ret__ - 8, &dev__->stats, dev__->tstats); } while (0)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 5, 0) && LINUX_VERSION_CODE >= KERNEL_VERSION(4, 3, 0)
#include <linux/if.h>
#include <net/udp_tunnel.h>
#define udp_tunnel_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l) do { struct net_device *dev__ = (c)->dev; int ret__ = udp_tunnel_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l); iptunnel_xmit_stats(ret__, &dev__->stats, dev__->tstats); } while (0)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 6, 0) && IS_ENABLED(CONFIG_IPV6) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
#include <linux/if.h>
#include <net/udp_tunnel.h>
#define udp_tunnel6_xmit_skb(a, b, c, d, e, f, g, h, i, j, k, l) udp_tunnel6_xmit_skb(a, b, c, d, e, f, g, h, j, k, l)
#endif

#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 3, 0) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
#include <linux/skbuff.h>
#include <linux/if.h>
#include <net/udp_tunnel.h>
struct __compat_udp_port_cfg {
	u8 family;
	union {
		struct in_addr local_ip;
#if IS_ENABLED(CONFIG_IPV6)
		struct in6_addr local_ip6;
#endif
	};
	union {
		struct in_addr peer_ip;
#if IS_ENABLED(CONFIG_IPV6)
		struct in6_addr peer_ip6;
#endif
	};
	__be16 local_udp_port;
	__be16 peer_udp_port;
	unsigned int use_udp_checksums:1, use_udp6_tx_checksums:1, use_udp6_rx_checksums:1, ipv6_v6only:1;
};
static inline int __maybe_unused __compat_udp_sock_create(struct net *net, struct __compat_udp_port_cfg *cfg, struct socket **sockp)
{
	struct udp_port_cfg old_cfg = {
		.family = cfg->family,
		.local_ip = cfg->local_ip,
#if IS_ENABLED(CONFIG_IPV6)
		.local_ip6 = cfg->local_ip6,
#endif
		.peer_ip = cfg->peer_ip,
#if IS_ENABLED(CONFIG_IPV6)
		.peer_ip6 = cfg->peer_ip6,
#endif
		.local_udp_port = cfg->local_udp_port,
		.peer_udp_port = cfg->peer_udp_port,
		.use_udp_checksums = cfg->use_udp_checksums,
		.use_udp6_tx_checksums = cfg->use_udp6_tx_checksums,
		.use_udp6_rx_checksums = cfg->use_udp6_rx_checksums
	};
	if (cfg->family == AF_INET)
		return udp_sock_create4(net, &old_cfg, sockp);

#if IS_ENABLED(CONFIG_IPV6)
	if (cfg->family == AF_INET6) {
		int ret;
		int old_bindv6only;
		struct net *nobns;

		if (cfg->ipv6_v6only) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 2, 0)
			nobns = &init_net;
#else
			nobns = net;
#endif
			/* Since udp_port_cfg only learned of ipv6_v6only in 4.3, we do this horrible
			 * hack here and set the sysctl variable temporarily to something that will
			 * set the right option for us in sock_create. It's super racey! */
			old_bindv6only = nobns->ipv6.sysctl.bindv6only;
			nobns->ipv6.sysctl.bindv6only = 1;
		}
		ret = udp_sock_create6(net, &old_cfg, sockp);
		if (cfg->ipv6_v6only)
			nobns->ipv6.sysctl.bindv6only = old_bindv6only;
		return ret;
	}
#endif
	return -EPFNOSUPPORT;
}
#define udp_port_cfg __compat_udp_port_cfg
#define udp_sock_create(a, b, c) __compat_udp_sock_create(a, b, c)
#endif
