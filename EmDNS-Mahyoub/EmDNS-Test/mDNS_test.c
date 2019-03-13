/**
 * \file
 *         EmDNS test example
 *
 * \author Mohammed Mahyoub <malmeraby@gmail.com>
 */

#include "contiki.h"
#include "net/ip/resolv.h"
#include "net/ip/uip.h"
#include "net/ipv6/uip-ds6.h"
#include "uip-debug.h"
#include "sys/node-id.h"
#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"
#include "EmDNS-log.h"
#include "simple-energest.h"

/*---------------------------------------------------------------------------*/
static void
print_local_addresses(void)
{
  int i;
  uint8_t state;
  PRINTF("Client IPv6 addresses: ");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused &&
       (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
      PRINT6ADDR(&uip_ds6_if.addr_list[i].ipaddr);
      PRINTF("\n");
      /* hack to make address "final" */
      if (state == ADDR_TENTATIVE) {
	uip_ds6_if.addr_list[i].state = ADDR_PREFERRED;
      }
    }
  }
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
PROCESS(mDNS_Test_Process, "mDNS_Test_Process");
AUTOSTART_PROCESSES (&mDNS_Test_Process);
int call_pss;
uint8_t NODES_NUM =5;
char hostname [30]= "contiki";
uip_ipaddr_t ** ipaddr;
resolv_status_t state;
uint8_t hit_times;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(mDNS_Test_Process, ev, data)
{
  PROCESS_BEGIN();
  simple_energest_start();
  print_local_addresses();
#if WITH_EmDNS
  call_pss =0;
#endif /*WITH_EmDNS*/
  process_start(&resolv_process,NULL);
  PROCESS_WAIT_EVENT();
  if(ev == convergence_event_found){
	uint8_t i;
	hit_times = 0;
	for(i=0; i< NODES_NUM ; i++){
		uint8_t val = i;
	      char str[2];
	      sprintf(str, "%d", val);
	      strncat(hostname, str, sizeof(str));
	      state = resolv_lookup(hostname,ipaddr);
	      if(state == RESOLV_STATUS_CACHED){
	    	  EmDNS_LOG("EmDNS: the requested hostname is found in the cache");
	    	  hit_times ++;
	      }else{
	    	  EmDNS_LOG("EmDNS: the requested hostname is not in the cache");
	      }
	}
  }
  if(node_id > NODES_NUM/2){
#if WITH_EmDNS
  call_pss = 1;
#endif /*WITH_EmDNS*/
  	  process_start(&resolv_process,NULL);
	  }
  PROCESS_WAIT_EVENT_UNTIL(ev == convergence_event_found);
}
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

