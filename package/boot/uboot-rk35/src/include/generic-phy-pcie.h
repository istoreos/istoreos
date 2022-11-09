/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 Rockchip Inc.
 */

#ifndef __PHY_PCIE_H_
#define __PHY_PCIE_H_

/**
 * struct phy_configure_opts_pcie - PCIe PHY configuration set
 *
 * This structure is used to represent the configuration state of a
 * PCIe phy.
 */
struct phy_configure_opts_pcie {
	bool is_bifurcation; /* Bifurcation mode support */
};

#endif /* __PHY_PCIE_H_ */
