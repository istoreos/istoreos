// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2018  Cisco Systems, Inc.
 *
 * Author: Thomas Fitzsimmons <fitzsim@fitzsim.org>
 */

#include <common.h>
#include <mach/sdhci.h>
#include <malloc.h>
#include <sdhci.h>

/*
 * The BCMSTB SDHCI has a quirk in that its actual maximum frequency
 * capability is 100 MHz.  The divisor that is eventually written to
 * SDHCI_CLOCK_CONTROL is calculated based on what the MMC device
 * reports, and relative to this maximum frequency.
 *
 * This define used to be set to 52000000 (52 MHz), the desired
 * maximum frequency, but that would result in the communication
 * actually running at 100 MHz (seemingly without issue), which is
 * out-of-spec.
 *
 * Now, by setting this to 0 (auto-detect), 100 MHz will be read from
 * the capabilities register, and the resulting divisor will be
 * doubled, meaning that the clock control register will be set to the
 * in-spec 52 MHz value.
 */
#define BCMSTB_SDHCI_MAXIMUM_CLOCK_FREQUENCY	0
/*
 * When the minimum clock frequency is set to 0 (auto-detect), U-Boot
 * sets it to 100 MHz divided by SDHCI_MAX_DIV_SPEC_300, or 48,875 Hz,
 * which results in the controller timing out when trying to
 * communicate with the MMC device.  Hard-code this value to 400000
 * (400 kHz) to prevent this.
 */
#define BCMSTB_SDHCI_MINIMUM_CLOCK_FREQUENCY	400000

static char *BCMSTB_SDHCI_NAME = "bcmstb-sdhci";

/*
 * This driver has only been tested with eMMC devices; SD devices may
 * not work.
 */
int bcmstb_sdhci_init(phys_addr_t regbase)
{
	struct sdhci_host *host = NULL;

	host = (struct sdhci_host *)malloc(sizeof(struct sdhci_host));
	if (!host) {
		printf("%s: Failed to allocate memory\n", __func__);
		return 1;
	}
	memset(host, 0, sizeof(*host));

	host->name = BCMSTB_SDHCI_NAME;
	host->ioaddr = (void *)regbase;
	host->quirks = 0;

	host->cfg.part_type = PART_TYPE_DOS;

	host->version = sdhci_readw(host, SDHCI_HOST_VERSION);

	return add_sdhci(host,
			 BCMSTB_SDHCI_MAXIMUM_CLOCK_FREQUENCY,
			 BCMSTB_SDHCI_MINIMUM_CLOCK_FREQUENCY);
}
