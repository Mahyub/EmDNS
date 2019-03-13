
/**
 * \file
 *         Header file for EmDNS-log.c, and a set of macros for EmDNS logging
 *
 * \author Mohammed Mahyoub <malmeraby@gmail.com>
 */

#ifndef HRPL_LOG_H
#define HRPL_LOG_H
#include "contiki-net.h"

/* Used to identify packets carrying EmDNS log */
#define EmDNS_LOG_MAGIC 0xcafebabe

/* Data structure copied at the end of all data packets, making it possible
 * to trace packets at every hop, from every layer. */
struct app_data {
  uint32_t magic;
  uint32_t seqno;
  uint16_t src;
  uint16_t dest;
  uint8_t hop;
  clock_time_t snd_tm;
};
void EmDNS_get_global_addr(uip_ipaddr_t *addr, uint16_t id);
/* Copy an appdata to another with no assumption that the addresses are aligned */
void app_copy_data(struct app_data *dst, struct app_data *src);/* Get dataptr from the packet currently in uIP buffer */
struct app_data *appdataptr_from_uip();
/* Get dataptr from the current packetbuf */
struct app_data *appdataptr_from_packetbuf();
/* Log information about a data packet along with HRPL routing information */
void log_appdataptr(struct app_data *dataptr);
/* Log information about a uip layers statistics */
void uip_statistics_print();
#define HRPL_LOG_FROM_PACKETBUF log_appdataptr(appdataptr_from_packetbuf())
#define HRPL_LOG_INC_HOPCOUNT_FROM_PACKETBUF() { struct app_data *ptr = appdataptr_from_packetbuf(); if(ptr) ptr->hop++; }
#define EmDNS_LOG(...) printf(__VA_ARGS__)

extern process_event_t convergence_event_found;
PROCESS_NAME(mDNS_Test_Process);

#endif /* HRPL_LOG */
