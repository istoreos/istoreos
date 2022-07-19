#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <rtc.h>

#define BIT(x) (1 << (x))

#define RTK_RTC_BASE	(0x9801B600)
#define RTK_RBUS_BASE	(0x98000000)
#define RTK_ISO_BASE	(0x98007000)

#define REG_RTCSEC                      0x00
#define REG_RTCMIN                      0x04
#define REG_RTCHR                       0x08
#define REG_RTCDATE_LOW                 0x0C
#define REG_RTCDATE_HIGH                0x10
#define REG_ALARMMIN                    0x14
#define REG_ALARMHR                     0x18
#define REG_ALARMDATE_LOW               0x1C
#define REG_ALARMDATE_HIGH              0x20
#define REG_RTCSTOP                     0x24
#define REG_RTCACR                      0x28
#define REG_RTCEN                       0x2C
#define REG_RTCCR                       0x30

#define REG_ISO_ISR                     0x00
#define REG_ISO_RTC                     0x34

static void *rtk_rtc_base = (void*)RTK_RTC_BASE;
static void *rtk_rbus_base = (void*)RTK_RBUS_BASE;
static void *rtk_iso_base = (void*)RTK_ISO_BASE;

static unsigned long rtk_base_year = CONFIG_RTK_RTC_BASE_YEAR - 1900;

/* 1:enabled, 0:disabled */
static int rtc_enabled(void)
{
	if (!(readl(rtk_rbus_base + 0x10) & BIT(10)))
		return 0;

	if ((readl(rtk_rtc_base + REG_RTCEN) & 0xff) != 0x5a)
		return 0;

	if ((readl(rtk_rtc_base + REG_RTCACR) & 0x80) != 0x80 )
		return 0;

	return 1;
}

/* Enable RTC Start in Control register*/
void rtc_init(void)
{
	printf("RTC initialize not support yet\n");
	return;
}

/*
 * Reset the RTC. We set the date back to 1970-01-01.
 */
void rtc_reset(void)
{
	printf("RTC reset not support yet\n");
	return;
}

/*
 * Set the RTC
*/
int rtc_set(struct rtc_time *tmp)
{
	printf("RTC set not support yet\n");
	return -1;
}

/*
 * Get the current time from the RTC
 */
int rtc_get(struct rtc_time *tmp)
{
        unsigned int retried = 0;
        unsigned int day, hour, min, sec;
	unsigned long t_sec = 0;
	struct rtc_time rtc_tmp;
	
	if (!rtc_enabled()) {
		printf("%s: RTC not enabled!!\n", __func__);
		return -1;
	}

	if (tmp == NULL) {
		printf("%s: rtc_time NULL\n", __func__);
		return -1;
	}

retry:
	sec = readl(rtk_rtc_base + REG_RTCSEC) >> 1;    // One unit represents half second
	min = readl(rtk_rtc_base + REG_RTCMIN);
	hour = readl(rtk_rtc_base + REG_RTCHR);
	day = readl(rtk_rtc_base + REG_RTCDATE_LOW);
	day += readl(rtk_rtc_base + REG_RTCDATE_HIGH)<<8;

	if (sec == 0 && !retried) {
		retried++;
		goto retry;
	}

	rtc_tmp.tm_year = rtk_base_year + 1900;
	rtc_tmp.tm_mon = 1;
	rtc_tmp.tm_mday = 1;
	rtc_tmp.tm_hour = 0;
	rtc_tmp.tm_min = 0;
	rtc_tmp.tm_sec = 0;
	t_sec = ((day*24 + hour)*60 + min)*60 + sec + rtc_mktime(&rtc_tmp);
	//t_sec = ((day*24 + hour)*60 + min)*60 + sec + mktime(rtk_base_year + 1900, 1, 1, 0, 0, 0);
	rtc_to_tm(t_sec, tmp);

	//printf ( "Get DATE: %4d-%02d-%02d (wday=%d)  TIME: %2d:%02d:%02d\n",
	//	tmp->tm_year, tmp->tm_mon, tmp->tm_mday, tmp->tm_wday,
	//	tmp->tm_hour, tmp->tm_min, tmp->tm_sec);	

	return 0;
}

int rtc_alarm_state(struct rtc_time *tmp)
{
	int day, hour, min;
	unsigned long t_sec = 0;
	struct rtc_time rtc_tmp;

	if (!tmp) {
		printf("%s: rtc_time NULL\n", __func__);
		return -1;
	}

	if (!rtc_enabled()) {
		printf("RTC not enabled!\n");
		return -1;
	}

	if (!(readl(rtk_iso_base + REG_ISO_RTC) && 0x1))
		return -1;

	min = readl(rtk_rtc_base + REG_ALARMMIN);
	hour = readl(rtk_rtc_base + REG_ALARMHR);
	day = readl(rtk_rtc_base + REG_ALARMDATE_LOW);
	day += readl(rtk_rtc_base + REG_ALARMDATE_HIGH) << 8;

	rtc_tmp.tm_year = rtk_base_year + 1900;
	rtc_tmp.tm_mon = 1;
	rtc_tmp.tm_mday = 1;
	rtc_tmp.tm_hour = 0;
	rtc_tmp.tm_min = 0;
	rtc_tmp.tm_sec = 0;
	t_sec = ((day*24 + hour)*60 + min)*60 + rtc_mktime(&rtc_tmp);
	//t_sec = ((day*24 + hour)*60 + min)*60 + mktime(rtk_base_year + 1900, 1, 1, 0, 0, 0);
	rtc_to_tm(t_sec, tmp);

	return 0;
}

int rtc_alarm_set(struct rtc_time *tmp)
{
	int day, hour, min, hms;
	unsigned long t_sec = 0, base_sec = 0, off_sec = 0;
	struct rtc_time rtc_tmp;

	if (!tmp) {
		printf("%s: rtc_time NULL\n", __func__);
		return -1;
	}

	if (!rtc_enabled()) {
		printf("RTC not enabled!\n");
		return -1;
	}
	// Turn OFF ALARM first
	writel(0, rtk_iso_base + REG_ISO_RTC);

	printf ( "%s:ALARM DATE: %4d-%02d-%02d (wday=%d)  TIME: %2d:%02d:%02d\n",
		__func__, tmp->tm_year, tmp->tm_mon, tmp->tm_mday, tmp->tm_wday,
		tmp->tm_hour, tmp->tm_min, tmp->tm_sec);	

	//t_sec = mktime(tmp->tm_year, tmp->tm_mon, tmp->tm_mday,
	//		tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
	//base_sec = mktime(rtk_base_year + 1900, 1, 1, 0, 0, 0);
	t_sec = rtc_mktime(tmp);
	rtc_tmp.tm_year = rtk_base_year + 1900;
	rtc_tmp.tm_mon = 1;
	rtc_tmp.tm_mday = 1;
	rtc_tmp.tm_hour = 0;
	rtc_tmp.tm_min = 0;
	rtc_tmp.tm_sec = 0;
	base_sec = rtc_mktime(&rtc_tmp);
	off_sec = t_sec - base_sec;

	if(base_sec > t_sec) {
		printf("RTC alarm set time error! The time cannot be set to the date before year %ld.\n", rtk_base_year + 1900);
		printf("base_sec:%lu, t_sec:%lu\n", base_sec, t_sec);
		return -1;
	}

	day = off_sec / (24*60*60);
	hms = off_sec % (24*60*60);
	hour = hms / 3600;
	min = (hms % 3600) / 60;

	if(day > 16383) {
		printf("RTC alarm day field overflow.\n");
		return -1;
	}

	writel(min, rtk_rtc_base + REG_ALARMMIN);
	writel(hour, rtk_rtc_base + REG_ALARMHR);
	writel(day & 0x00ff, rtk_rtc_base + REG_ALARMDATE_LOW);
	writel((day & 0x3f00) >> 8, rtk_rtc_base + REG_ALARMDATE_HIGH);

	// Turn ALARM back on
	writel(0x2000, rtk_iso_base + REG_ISO_ISR);
	writel(0x1, rtk_iso_base + REG_ISO_RTC);

	return 0;
}
