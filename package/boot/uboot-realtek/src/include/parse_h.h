#ifndef __PARSEH_H__
#define __PARSEH_H__

#ifdef PANEL_CONFIG_FROM_FACTORY_PANEL_HEADER
uint parse_main(char *src_addr, uint length);
#endif
uint parse_h(char *target_str, char *src_addr, uint length, uint* pRetVal, char **pRetAddr);

#endif

