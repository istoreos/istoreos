/*
 * Logging support test program
 *
 * Copyright (c) 2017 Google, Inc
 * Written by Simon Glass <sjg@chromium.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

/* emit some sample log records in different ways, for testing */
static int log_run(enum uclass_id cat, const char *file)
{
	int i;

	debug("debug\n");
	for (i = LOGL_FIRST; i < LOGL_COUNT; i++) {
		log(cat, i, "log %d\n", i);
		_log(log_uc_cat(cat), i, file, 100 + i, "func", "_log %d\n",
		     i);
	}

	return 0;
}

static int log_test(int testnum)
{
	int ret;

	printf("test %d\n", testnum);
	switch (testnum) {
	case 0: {
		/* Check a category filter using the first category */
		enum log_category_t cat_list[] = {
			log_uc_cat(UCLASS_MMC), log_uc_cat(UCLASS_SPI),
			LOGC_NONE, LOGC_END
		};

		ret = log_add_filter("console", cat_list, LOGL_MAX, NULL);
		if (ret < 0)
			return ret;
		log_run(UCLASS_MMC, "file");
		ret = log_remove_filter("console", ret);
		if (ret < 0)
			return ret;
		break;
	}
	case 1: {
		/* Check a category filter using the second category */
		enum log_category_t cat_list[] = {
			log_uc_cat(UCLASS_MMC), log_uc_cat(UCLASS_SPI), LOGC_END
		};

		ret = log_add_filter("console", cat_list, LOGL_MAX, NULL);
		if (ret < 0)
			return ret;
		log_run(UCLASS_SPI, "file");
		ret = log_remove_filter("console", ret);
		if (ret < 0)
			return ret;
		break;
	}
	case 2: {
		/* Check a category filter that should block log entries */
		enum log_category_t cat_list[] = {
			log_uc_cat(UCLASS_MMC),  LOGC_NONE, LOGC_END
		};

		ret = log_add_filter("console", cat_list, LOGL_MAX, NULL);
		if (ret < 0)
			return ret;
		log_run(UCLASS_SPI, "file");
		ret = log_remove_filter("console", ret);
		if (ret < 0)
			return ret;
		break;
	}
	case 3: {
		/* Check a passing file filter */
		ret = log_add_filter("console", NULL, LOGL_MAX, "file");
		if (ret < 0)
			return ret;
		log_run(UCLASS_SPI, "file");
		ret = log_remove_filter("console", ret);
		if (ret < 0)
			return ret;
		break;
	}
	case 4: {
		/* Check a failing file filter */
		ret = log_add_filter("console", NULL, LOGL_MAX, "file");
		if (ret < 0)
			return ret;
		log_run(UCLASS_SPI, "file2");
		ret = log_remove_filter("console", ret);
		if (ret < 0)
			return ret;
		break;
	}
	case 5: {
		/* Check a passing file filter (second in list) */
		ret = log_add_filter("console", NULL, LOGL_MAX, "file,file2");
		if (ret < 0)
			return ret;
		log_run(UCLASS_SPI, "file2");
		ret = log_remove_filter("console", ret);
		if (ret < 0)
			return ret;
		break;
	}
	case 6: {
		/* Check a passing file filter */
		ret = log_add_filter("console", NULL, LOGL_MAX,
				     "file,file2,log/log_test.c");
		if (ret < 0)
			return ret;
		log_run(UCLASS_SPI, "file2");
		ret = log_remove_filter("console", ret);
		if (ret < 0)
			return ret;
		break;
	}
	case 7: {
		/* Check a log level filter */
		ret = log_add_filter("console", NULL, LOGL_WARNING, NULL);
		if (ret < 0)
			return ret;
		log_run(UCLASS_SPI, "file");
		ret = log_remove_filter("console", ret);
		if (ret < 0)
			return ret;
		break;
	}
	case 8: {
		/* Check two filters, one of which passes everything */
		int filt1, filt2;

		ret = log_add_filter("console", NULL, LOGL_WARNING, NULL);
		if (ret < 0)
			return ret;
		filt1 = ret;
		ret = log_add_filter("console", NULL, LOGL_MAX, NULL);
		if (ret < 0)
			return ret;
		filt2 = ret;
		log_run(UCLASS_SPI, "file");
		ret = log_remove_filter("console", filt1);
		if (ret < 0)
			return ret;
		ret = log_remove_filter("console", filt2);
		if (ret < 0)
			return ret;
		break;
	}
	case 9: {
		/* Check three filters, which together pass everything */
		int filt1, filt2, filt3;

		ret = log_add_filter("console", NULL, LOGL_MAX, "file)");
		if (ret < 0)
			return ret;
		filt1 = ret;
		ret = log_add_filter("console", NULL, LOGL_MAX, "file2");
		if (ret < 0)
			return ret;
		filt2 = ret;
		ret = log_add_filter("console", NULL, LOGL_MAX,
				     "log/log_test.c");
		if (ret < 0)
			return ret;
		filt3 = ret;
		log_run(UCLASS_SPI, "file2");
		ret = log_remove_filter("console", filt1);
		if (ret < 0)
			return ret;
		ret = log_remove_filter("console", filt2);
		if (ret < 0)
			return ret;
		ret = log_remove_filter("console", filt3);
		if (ret < 0)
			return ret;
		break;
	}
	}

	return 0;
}

#ifdef CONFIG_LOG_TEST
int do_log_test(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int testnum = 0;
	int ret;

	if (argc > 1)
		testnum = simple_strtoul(argv[1], NULL, 10);

	ret = log_test(testnum);
	if (ret)
		printf("Test failure (err=%d)\n", ret);

	return ret ? CMD_RET_FAILURE : 0;
}
#endif
