#include "contiki.h"
#include "simple-energest.h"
#include <stdio.h>
#include "sys/compower.h"
#include "net/packetbuf.h"
#include "EmDNS-log.h"
#include "net/ip/uip.h"
#define DEBUG DEBUG_NONE
#include "net/ip/uip-debug.h"



unsigned long  all_cpu, all_lpm, all_tx, all_rx, all_flash_write, all_flash_read;

PROCESS(simple_energest_process, "Simple Energest");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(simple_energest_process, ev, data)
{
  static struct etimer periodic;
  PROCESS_BEGIN();
  etimer_set(&periodic, 3 *60 * CLOCK_SECOND);

  while(1) {
    PROCESS_WAIT_UNTIL(etimer_expired(&periodic));
    etimer_reset(&periodic);
    uip_statistics_print();
    simple_energest_print();
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
void simple_energest_start() {
  energest_flush();
  all_tx = energest_type_time(ENERGEST_TYPE_TRANSMIT);
  all_rx = energest_type_time(ENERGEST_TYPE_LISTEN);
  all_cpu = energest_type_time(ENERGEST_TYPE_CPU);
  all_lpm=energest_type_time(ENERGEST_TYPE_LPM);
  all_flash_write=energest_type_time(ENERGEST_TYPE_FLASH_WRITE);
  all_flash_read=energest_type_time(ENERGEST_TYPE_FLASH_READ);
  process_start(&simple_energest_process, NULL);
}

/*---------------------------------------------------------------------------*/
void simple_energest_print() {
  energest_flush();

  all_cpu = energest_type_time(ENERGEST_TYPE_CPU) ;
  all_lpm=energest_type_time(ENERGEST_TYPE_LPM);
  all_rx = energest_type_time(ENERGEST_TYPE_LISTEN);
  all_tx = energest_type_time(ENERGEST_TYPE_TRANSMIT);
 EmDNS_LOG("energy:  %lu  %lu  %lu  %lu, %lu \n",all_cpu+all_flash_write+all_flash_read,
		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 all_lpm,all_rx,all_tx);
}

/*---------------------------------------------------------------------------*/
void uip_statistics_print() {
	  printf("stack_stats:  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u  %u\n",
			  uip_stat.ip.sent, uip_stat.ip.recv, uip_stat.ip.forwarded, uip_stat.ip.drop,
			  uip_stat.udp.sent, uip_stat.udp.recv, uip_stat.udp.drop,
			  uip_stat.icmp.sent, uip_stat.icmp.recv, uip_stat.icmp.drop,
			  uip_stat.nd6.sent, uip_stat.nd6.recv, uip_stat.nd6.drop);
}
/*---------------------------------------------------------------------------*/
