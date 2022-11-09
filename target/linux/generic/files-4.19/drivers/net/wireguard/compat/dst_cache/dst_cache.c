/*
 * net/core/dst_cache.c - dst entry cache
 *
 * Copyright (c) 2016 Paolo Abeni <pabeni@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/percpu.h>
#include <net/dst_cache.h>
#include <net/route.h>
#if IS_ENABLED(CONFIG_IPV6)
#include <net/ip6_fib.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 2, 0) && LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)) || LINUX_VERSION_CODE < KERNEL_VERSION(3, 16, 50)
static inline u32 rt6_get_cookie(const struct rt6_info *rt)
{
	if ((unlikely(rt->dst.flags & DST_NOCACHE) && rt->dst.from))
		rt = (struct rt6_info *)(rt->dst.from);

	return rt->rt6i_node ? rt->rt6i_node->fn_sernum : 0;
}
#endif
#endif
#include <uapi/linux/in.h>

struct dst_cache_pcpu {
	unsigned long refresh_ts;
	struct dst_entry *dst;
	u32 cookie;
	union {
		struct in_addr in_saddr;
		struct in6_addr in6_saddr;
	};
};

static void dst_cache_per_cpu_dst_set(struct dst_cache_pcpu *dst_cache,
				      struct dst_entry *dst, u32 cookie)
{
	dst_release(dst_cache->dst);
	if (dst)
		dst_hold(dst);

	dst_cache->cookie = cookie;
	dst_cache->dst = dst;
}

static struct dst_entry *dst_cache_per_cpu_get(struct dst_cache *dst_cache,
					       struct dst_cache_pcpu *idst)
{
	struct dst_entry *dst;

	dst = idst->dst;
	if (!dst)
		goto fail;

	/* the cache already hold a dst reference; it can't go away */
	dst_hold(dst);

	if (unlikely(!time_after(idst->refresh_ts, dst_cache->reset_ts) ||
		     (dst->obsolete && !dst->ops->check(dst, idst->cookie)))) {
		dst_cache_per_cpu_dst_set(idst, NULL, 0);
		dst_release(dst);
		goto fail;
	}
	return dst;

fail:
	idst->refresh_ts = jiffies;
	return NULL;
}

struct dst_entry *dst_cache_get(struct dst_cache *dst_cache)
{
	if (!dst_cache->cache)
		return NULL;

	return dst_cache_per_cpu_get(dst_cache, this_cpu_ptr(dst_cache->cache));
}

struct rtable *dst_cache_get_ip4(struct dst_cache *dst_cache, __be32 *saddr)
{
	struct dst_cache_pcpu *idst;
	struct dst_entry *dst;

	if (!dst_cache->cache)
		return NULL;

	idst = this_cpu_ptr(dst_cache->cache);
	dst = dst_cache_per_cpu_get(dst_cache, idst);
	if (!dst)
		return NULL;

	*saddr = idst->in_saddr.s_addr;
	return container_of(dst, struct rtable, dst);
}

void dst_cache_set_ip4(struct dst_cache *dst_cache, struct dst_entry *dst,
		       __be32 saddr)
{
	struct dst_cache_pcpu *idst;

	if (!dst_cache->cache)
		return;

	idst = this_cpu_ptr(dst_cache->cache);
	dst_cache_per_cpu_dst_set(idst, dst, 0);
	idst->in_saddr.s_addr = saddr;
}

#if IS_ENABLED(CONFIG_IPV6)
void dst_cache_set_ip6(struct dst_cache *dst_cache, struct dst_entry *dst,
		       const struct in6_addr *addr)
{
	struct dst_cache_pcpu *idst;

	if (!dst_cache->cache)
		return;

	idst = this_cpu_ptr(dst_cache->cache);
	dst_cache_per_cpu_dst_set(this_cpu_ptr(dst_cache->cache), dst,
				  rt6_get_cookie((struct rt6_info *)dst));
	idst->in6_saddr = *addr;
}

struct dst_entry *dst_cache_get_ip6(struct dst_cache *dst_cache,
				    struct in6_addr *saddr)
{
	struct dst_cache_pcpu *idst;
	struct dst_entry *dst;

	if (!dst_cache->cache)
		return NULL;

	idst = this_cpu_ptr(dst_cache->cache);
	dst = dst_cache_per_cpu_get(dst_cache, idst);
	if (!dst)
		return NULL;

	*saddr = idst->in6_saddr;
	return dst;
}
#endif

int dst_cache_init(struct dst_cache *dst_cache, gfp_t gfp)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0)
	BUG_ON(gfp & GFP_ATOMIC);
	dst_cache->cache = alloc_percpu(struct dst_cache_pcpu);
#else
	dst_cache->cache = alloc_percpu_gfp(struct dst_cache_pcpu,
					    gfp | __GFP_ZERO);
#endif
	if (!dst_cache->cache)
		return -ENOMEM;

	dst_cache_reset(dst_cache);
	return 0;
}

void dst_cache_destroy(struct dst_cache *dst_cache)
{
	int i;

	if (!dst_cache->cache)
		return;

	for_each_possible_cpu(i)
		dst_release(per_cpu_ptr(dst_cache->cache, i)->dst);

	free_percpu(dst_cache->cache);
}
