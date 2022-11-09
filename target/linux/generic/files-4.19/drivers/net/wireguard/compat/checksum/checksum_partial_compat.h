/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#include <net/route.h>
#include <net/esp.h>
#include <net/ip.h>
#include <net/ipv6.h>
#include <net/ip6_checksum.h>

#define IP6_MF          0x0001
#define IP6_OFFSET      0xFFF8
static inline int skb_maybe_pull_tail(struct sk_buff *skb, unsigned int len, unsigned int max)
{
	if (skb_headlen(skb) >= len)
		return 0;
	if (max > skb->len)
		max = skb->len;
	if (__pskb_pull_tail(skb, max - skb_headlen(skb)) == NULL)
		return -ENOMEM;
	if (skb_headlen(skb) < len)
		return -EPROTO;
	return 0;
}
#define MAX_IP_HDR_LEN 128
static inline int skb_checksum_setup_ip(struct sk_buff *skb, bool recalculate)
{
	unsigned int off;
	bool fragment;
	int err;
	fragment = false;
	err = skb_maybe_pull_tail(skb, sizeof(struct iphdr), MAX_IP_HDR_LEN);
	if (err < 0)
		goto out;
	if (ip_hdr(skb)->frag_off & htons(IP_OFFSET | IP_MF))
		fragment = true;
	off = ip_hdrlen(skb);
	err = -EPROTO;
	if (fragment)
		goto out;
	switch (ip_hdr(skb)->protocol) {
	case IPPROTO_TCP:
		err = skb_maybe_pull_tail(skb,
					  off + sizeof(struct tcphdr),
					  MAX_IP_HDR_LEN);
		if (err < 0)
			goto out;

		if (!skb_partial_csum_set(skb, off,
					  offsetof(struct tcphdr, check))) {
			err = -EPROTO;
			goto out;
		}

		if (recalculate)
			tcp_hdr(skb)->check =
				~csum_tcpudp_magic(ip_hdr(skb)->saddr,
						   ip_hdr(skb)->daddr,
						   skb->len - off,
						   IPPROTO_TCP, 0);
		break;
	case IPPROTO_UDP:
		err = skb_maybe_pull_tail(skb,
					  off + sizeof(struct udphdr),
					  MAX_IP_HDR_LEN);
		if (err < 0)
			goto out;

		if (!skb_partial_csum_set(skb, off,
					  offsetof(struct udphdr, check))) {
			err = -EPROTO;
			goto out;
		}

		if (recalculate)
			udp_hdr(skb)->check =
				~csum_tcpudp_magic(ip_hdr(skb)->saddr,
						   ip_hdr(skb)->daddr,
						   skb->len - off,
						   IPPROTO_UDP, 0);
		break;
	default:
		goto out;
	}
	err = 0;
out:
	return err;
}
#define MAX_IPV6_HDR_LEN 256
#define OPT_HDR(type, skb, off) \
	(type *)(skb_network_header(skb) + (off))
static inline int skb_checksum_setup_ipv6(struct sk_buff *skb, bool recalculate)
{
	int err;
	u8 nexthdr;
	unsigned int off;
	unsigned int len;
	bool fragment;
	bool done;
	fragment = false;
	done = false;
	off = sizeof(struct ipv6hdr);
	err = skb_maybe_pull_tail(skb, off, MAX_IPV6_HDR_LEN);
	if (err < 0)
		goto out;
	nexthdr = ipv6_hdr(skb)->nexthdr;
	len = sizeof(struct ipv6hdr) + ntohs(ipv6_hdr(skb)->payload_len);
	while (off <= len && !done) {
		switch (nexthdr) {
		case IPPROTO_DSTOPTS:
		case IPPROTO_HOPOPTS:
		case IPPROTO_ROUTING: {
			struct ipv6_opt_hdr *hp;

			err = skb_maybe_pull_tail(skb, off + sizeof(struct ipv6_opt_hdr), MAX_IPV6_HDR_LEN);
			if (err < 0)
				goto out;
			hp = OPT_HDR(struct ipv6_opt_hdr, skb, off);
			nexthdr = hp->nexthdr;
			off += ipv6_optlen(hp);
			break;
		}
		case IPPROTO_FRAGMENT: {
			struct frag_hdr *hp;
			err = skb_maybe_pull_tail(skb, off + sizeof(struct frag_hdr), MAX_IPV6_HDR_LEN);
			if (err < 0)
				goto out;
			hp = OPT_HDR(struct frag_hdr, skb, off);
			if (hp->frag_off & htons(IP6_OFFSET | IP6_MF))
				fragment = true;
			nexthdr = hp->nexthdr;
			off += sizeof(struct frag_hdr);
			break;
		}
		default:
			done = true;
			break;
		}
	}
	err = -EPROTO;
	if (!done || fragment)
		goto out;
	switch (nexthdr) {
		case IPPROTO_TCP:
			err = skb_maybe_pull_tail(skb,
						  off + sizeof(struct tcphdr),
						  MAX_IPV6_HDR_LEN);
			if (err < 0)
				goto out;

			if (!skb_partial_csum_set(skb, off,
						  offsetof(struct tcphdr, check))) {
				err = -EPROTO;
				goto out;
			}

			if (recalculate)
				tcp_hdr(skb)->check =
					~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
							 &ipv6_hdr(skb)->daddr,
							 skb->len - off,
							 IPPROTO_TCP, 0);
			break;
		case IPPROTO_UDP:
			err = skb_maybe_pull_tail(skb,
						  off + sizeof(struct udphdr),
						  MAX_IPV6_HDR_LEN);
			if (err < 0)
				goto out;

			if (!skb_partial_csum_set(skb, off,
						  offsetof(struct udphdr, check))) {
				err = -EPROTO;
				goto out;
			}

			if (recalculate)
				udp_hdr(skb)->check =
					~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
							 &ipv6_hdr(skb)->daddr,
							 skb->len - off,
							 IPPROTO_UDP, 0);
			break;
		default:
			goto out;
	}
	err = 0;
out:
	return err;
}
static inline int skb_checksum_setup(struct sk_buff *skb, bool recalculate)
{
	int err;
	switch (skb->protocol) {
	case htons(ETH_P_IP):
		err = skb_checksum_setup_ip(skb, recalculate);
		break;

	case htons(ETH_P_IPV6):
		err = skb_checksum_setup_ipv6(skb, recalculate);
		break;
	default:
		err = -EPROTO;
		break;
	}
	return err;
}
