
/**
 * \file
 *         Tools for logging EmDNS state and tracing data packets
 *
 * \author Mohammed Mahyoub <malmeraby@gmail.com>
 */


#include "EmDNS-log.h"
#include "contiki.h"
#include <stdio.h>
#include <string.h>
#include "net/ip/uip.h"
#include "sys/node-id.h"
#include "net/ipv6/uip-ds6.h"
#include "net/packetbuf.h"

/*---------------------------------------------------------------------------*/
/* Copy an appdata to another with no assumption that the addresses are aligned */
void
app_copy_data(struct app_data *dst, struct app_data *src)
{
  int i;
  for(i=0; i<sizeof(struct app_data); i++) {
    ((char*)dst)[i] = (((char*)src)[i]);
  }
}
/*---------------------------------------------------------------------------------------*/
/* Get dataptr from the packet currently in uIP buffer */
struct app_data *
appdataptr_from_uip()
{
  return (struct app_data *)((char*)uip_buf + ((uip_len - sizeof(struct app_data))));
}
/*---------------------------------------------------------------------------------------*/
/* Get dataptr from the current packetbuf */
struct app_data *
appdataptr_from_packetbuf()
{
  struct app_data *ptr;
  struct app_data data;
  if(packetbuf_datalen() < sizeof(struct app_data)) return NULL;
  ptr = (struct app_data *)((char*)packetbuf_dataptr() + ((packetbuf_datalen() - sizeof(struct app_data))));
  app_copy_data(&data, ptr);
  if(data.magic == EmDNS_LOG_MAGIC) {
    return ptr;
  } else {
    return NULL;
  }
}
/*---------------------------------------------------------------------------------------*/
/* Log information about a data packet along with HRPL routing information */
void
log_appdataptr(struct app_data *dataptr)
{
  struct app_data data;
  if(dataptr) {
	  app_copy_data(&data, dataptr);

	  printf("HRPL: [seqno:%u hops:%u %u->%u]\n",
        data.seqno,
        data.hop,
        data.src,
        data.dest
        );
  }

}
/*---------------------------------------------------------------------------------------*/


