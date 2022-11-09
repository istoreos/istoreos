/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _INCLUDE_LIBFDT_H_
#define _INCLUDE_LIBFDT_H_

#ifndef USE_HOSTCC
#include <linux/libfdt_env.h>
#endif
#include "../../scripts/dtc/libfdt/libfdt.h"

/* U-Boot local hacks */

#ifndef SWIG /* Not available in Python */
struct fdt_region {
	int offset;
	int size;
};

/*
 * Flags for fdt_find_regions()
 *
 * Add a region for the string table (always the last region)
 */
#define FDT_REG_ADD_STRING_TAB		(1 << 0)

/*
 * Add all supernodes of a matching node/property, useful for creating a
 * valid subset tree
 */
#define FDT_REG_SUPERNODES		(1 << 1)

/* Add the FDT_BEGIN_NODE tags of subnodes, including their names */
#define FDT_REG_DIRECT_SUBNODES	(1 << 2)

/* Add all subnodes of a matching node */
#define FDT_REG_ALL_SUBNODES		(1 << 3)

/* Add a region for the mem_rsvmap table (always the first region) */
#define FDT_REG_ADD_MEM_RSVMAP		(1 << 4)

/* Indicates what an fdt part is (node, property, value) */
#define FDT_IS_NODE			(1 << 0)
#define FDT_IS_PROP			(1 << 1)
#define FDT_IS_VALUE			(1 << 2)	/* not supported */
#define FDT_IS_COMPAT			(1 << 3)	/* used internally */
#define FDT_NODE_HAS_PROP		(1 << 4)	/* node contains prop */

#define FDT_ANY_GLOBAL		(FDT_IS_NODE | FDT_IS_PROP | FDT_IS_VALUE | \
					FDT_IS_COMPAT)
#define FDT_IS_ANY			0x1f		/* all the above */

/* We set a reasonable limit on the number of nested nodes */
#define FDT_MAX_DEPTH			32

/* Decribes what we want to include from the current tag */
enum want_t {
	WANT_NOTHING,
	WANT_NODES_ONLY,		/* No properties */
	WANT_NODES_AND_PROPS,		/* Everything for one level */
	WANT_ALL_NODES_AND_PROPS	/* Everything for all levels */
};

/* Keeps track of the state at parent nodes */
struct fdt_subnode_stack {
	int offset;		/* Offset of node */
	enum want_t want;	/* The 'want' value here */
	int included;		/* 1 if we included this node, 0 if not */
};

struct fdt_region_ptrs {
	int depth;			/* Current tree depth */
	int done;			/* What we have completed scanning */
	enum want_t want;		/* What we are currently including */
	char *end;			/* Pointer to end of full node path */
	int nextoffset;			/* Next node offset to check */
};

/* The state of our finding algortihm */
struct fdt_region_state {
	struct fdt_subnode_stack stack[FDT_MAX_DEPTH];	/* node stack */
	struct fdt_region *region;	/* Contains list of regions found */
	int count;			/* Numnber of regions found */
	const void *fdt;		/* FDT blob */
	int max_regions;		/* Maximum regions to find */
	int can_merge;		/* 1 if we can merge with previous region */
	int start;			/* Start position of current region */
	struct fdt_region_ptrs ptrs;	/* Pointers for what we are up to */
};

/**
 * fdt_find_regions() - find regions in device tree
 *
 * Given a list of nodes to include and properties to exclude, find
 * the regions of the device tree which describe those included parts.
 *
 * The intent is to get a list of regions which will be invariant provided
 * those parts are invariant. For example, if you request a list of regions
 * for all nodes but exclude the property "data", then you will get the
 * same region contents regardless of any change to "data" properties.
 *
 * This function can be used to produce a byte-stream to send to a hashing
 * function to verify that critical parts of the FDT have not changed.
 *
 * Nodes which are given in 'inc' are included in the region list, as
 * are the names of the immediate subnodes nodes (but not the properties
 * or subnodes of those subnodes).
 *
 * For eaxample "/" means to include the root node, all root properties
 * and the FDT_BEGIN_NODE and FDT_END_NODE of all subnodes of /. The latter
 * ensures that we capture the names of the subnodes. In a hashing situation
 * it prevents the root node from changing at all Any change to non-excluded
 * properties, names of subnodes or number of subnodes would be detected.
 *
 * When used with FITs this provides the ability to hash and sign parts of
 * the FIT based on different configurations in the FIT. Then it is
 * impossible to change anything about that configuration (include images
 * attached to the configuration), but it may be possible to add new
 * configurations, new images or new signatures within the existing
 * framework.
 *
 * Adding new properties to a device tree may result in the string table
 * being extended (if the new property names are different from those
 * already added). This function can optionally include a region for
 * the string table so that this can be part of the hash too.
 *
 * The device tree header is not included in the list.
 *
 * @fdt:	Device tree to check
 * @inc:	List of node paths to included
 * @inc_count:	Number of node paths in list
 * @exc_prop:	List of properties names to exclude
 * @exc_prop_count:	Number of properties in exclude list
 * @region:	Returns list of regions
 * @max_region:	Maximum length of region list
 * @path:	Pointer to a temporary string for the function to use for
 *		building path names
 * @path_len:	Length of path, must be large enough to hold the longest
 *		path in the tree
 * @add_string_tab:	1 to add a region for the string table
 * @return number of regions in list. If this is >max_regions then the
 * region array was exhausted. You should increase max_regions and try
 * the call again.
 */
int fdt_find_regions(const void *fdt, char * const inc[], int inc_count,
		     char * const exc_prop[], int exc_prop_count,
		     struct fdt_region region[], int max_regions,
		     char *path, int path_len, int add_string_tab);

/**
 * fdt_first_region() - find regions in device tree
 *
 * Given a nodes and properties to include and properties to exclude, find
 * the regions of the device tree which describe those included parts.
 *
 * The use for this function is twofold. Firstly it provides a convenient
 * way of performing a structure-aware grep of the tree. For example it is
 * possible to grep for a node and get all the properties associated with
 * that node. Trees can be subsetted easily, by specifying the nodes that
 * are required, and then writing out the regions returned by this function.
 * This is useful for small resource-constrained systems, such as boot
 * loaders, which want to use an FDT but do not need to know about all of
 * it.
 *
 * Secondly it makes it easy to hash parts of the tree and detect changes.
 * The intent is to get a list of regions which will be invariant provided
 * those parts are invariant. For example, if you request a list of regions
 * for all nodes but exclude the property "data", then you will get the
 * same region contents regardless of any change to "data" properties.
 *
 * This function can be used to produce a byte-stream to send to a hashing
 * function to verify that critical parts of the FDT have not changed.
 * Note that semantically null changes in order could still cause false
 * hash misses. Such reordering might happen if the tree is regenerated
 * from source, and nodes are reordered (the bytes-stream will be emitted
 * in a different order and many hash functions will detect this). However
 * if an existing tree is modified using libfdt functions, such as
 * fdt_add_subnode() and fdt_setprop(), then this problem is avoided.
 *
 * The nodes/properties to include/exclude are defined by a function
 * provided by the caller. This function is called for each node and
 * property, and must return:
 *
 *    0 - to exclude this part
 *    1 - to include this part
 *   -1 - for FDT_IS_PROP only: no information is available, so include
 *		if its containing node is included
 *
 * The last case is only used to deal with properties. Often a property is
 * included if its containing node is included - this is the case where
 * -1 is returned.. However if the property is specifically required to be
 * included/excluded, then 0 or 1 can be returned. Note that including a
 * property when the FDT_REG_SUPERNODES flag is given will force its
 * containing node to be included since it is not valid to have a property
 * that is not in a node.
 *
 * Using the information provided, the inclusion of a node can be controlled
 * either by a node name or its compatible string, or any other property
 * that the function can determine.
 *
 * As an example, including node "/" means to include the root node and all
 * root properties. A flag provides a way of also including supernodes (of
 * which there is none for the root node), and another flag includes
 * immediate subnodes, so in this case we would get the FDT_BEGIN_NODE and
 * FDT_END_NODE of all subnodes of /.
 *
 * The subnode feature helps in a hashing situation since it prevents the
 * root node from changing at all. Any change to non-excluded properties,
 * names of subnodes or number of subnodes would be detected.
 *
 * When used with FITs this provides the ability to hash and sign parts of
 * the FIT based on different configurations in the FIT. Then it is
 * impossible to change anything about that configuration (include images
 * attached to the configuration), but it may be possible to add new
 * configurations, new images or new signatures within the existing
 * framework.
 *
 * Adding new properties to a device tree may result in the string table
 * being extended (if the new property names are different from those
 * already added). This function can optionally include a region for
 * the string table so that this can be part of the hash too. This is always
 * the last region.
 *
 * The FDT also has a mem_rsvmap table which can also be included, and is
 * always the first region if so.
 *
 * The device tree header is not included in the region list. Since the
 * contents of the FDT are changing (shrinking, often), the caller will need
 * to regenerate the header anyway.
 *
 * @fdt:	Device tree to check
 * @h_include:	Function to call to determine whether to include a part or
 *		not:
 *
 *		@priv: Private pointer as passed to fdt_find_regions()
 *		@fdt: Pointer to FDT blob
 *		@offset: Offset of this node / property
 *		@type: Type of this part, FDT_IS_...
 *		@data: Pointer to data (node name, property name, compatible
 *			string, value (not yet supported)
 *		@size: Size of data, or 0 if none
 *		@return 0 to exclude, 1 to include, -1 if no information is
 *		available
 * @priv:	Private pointer passed to h_include
 * @region:	Returns list of regions, sorted by offset
 * @max_regions: Maximum length of region list
 * @path:	Pointer to a temporary string for the function to use for
 *		building path names
 * @path_len:	Length of path, must be large enough to hold the longest
 *		path in the tree
 * @flags:	Various flags that control the region algortihm, see
 *		FDT_REG_...
 * @return number of regions in list. If this is >max_regions then the
 * region array was exhausted. You should increase max_regions and try
 * the call again. Only the first max_regions elements are available in the
 * array.
 *
 * On error a -ve value is return, which can be:
 *
 *	-FDT_ERR_BADSTRUCTURE (too deep or more END tags than BEGIN tags
 *	-FDT_ERR_BADLAYOUT
 *	-FDT_ERR_NOSPACE (path area is too small)
 */
int fdt_first_region(const void *fdt,
		     int (*h_include)(void *priv, const void *fdt, int offset,
				      int type, const char *data, int size),
		     void *priv, struct fdt_region *region,
		     char *path, int path_len, int flags,
		     struct fdt_region_state *info);

/** fdt_next_region() - find next region
 *
 * See fdt_first_region() for full description. This function finds the
 * next region according to the provided parameters, which must be the same
 * as passed to fdt_first_region().
 *
 * This function can additionally return -FDT_ERR_NOTFOUND when there are no
 * more regions
 */
int fdt_next_region(const void *fdt,
		    int (*h_include)(void *priv, const void *fdt, int offset,
				     int type, const char *data, int size),
		    void *priv, struct fdt_region *region,
		    char *path, int path_len, int flags,
		    struct fdt_region_state *info);

/**
 * fdt_add_alias_regions() - find aliases that point to existing regions
 *
 * Once a device tree grep is complete some of the nodes will be present
 * and some will have been dropped. This function checks all the alias nodes
 * to figure out which points point to nodes which are still present. These
 * aliases need to be kept, along with the nodes they reference.
 *
 * Given a list of regions function finds the aliases that still apply and
 * adds more regions to the list for these. This function is called after
 * fdt_next_region() has finished returning regions and requires the same
 * state.
 *
 * @fdt:	Device tree file to reference
 * @region:	List of regions that will be kept
 * @count:	Number of regions
 * @max_regions: Number of entries that can fit in @region
 * @info:	Region state as returned from fdt_next_region()
 * @return new number of regions in @region (i.e. count + the number added)
 * or -FDT_ERR_NOSPACE if there was not enough space.
 */
int fdt_add_alias_regions(const void *fdt, struct fdt_region *region, int count,
			  int max_regions, struct fdt_region_state *info);
#endif /* SWIG */

extern struct fdt_header *working_fdt;  /* Pointer to the working fdt */

/* adding a ramdisk needs 0x44 bytes in version 2008.10 */
#define FDT_RAMDISK_OVERHEAD	0x80

#endif /* _INCLUDE_LIBFDT_H_ */
