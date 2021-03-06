

#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_

#undef RESOLV_CONF_SUPPORTS_MDNS
#define RESOLV_CONF_SUPPORTS_MDNS 1

#define CONTIKI_CONF_DEFAULT_HOSTNAME "contiki0" //WITH_EmDNS

#undef QUEUEBUF_CONF_NUM
#define QUEUEBUF_CONF_NUM 4 //default 4

#undef CSMA_CONF_MAX_NEIGHBOR_QUEUES
#define  CSMA_CONF_MAX_NEIGHBOR_QUEUES 2 //default 2

#undef WITH_EmDNS
#define WITH_EmDNS 0
#define ENERGEST_CONF_ON 1
#define UIP_CONF_RESOLV_ENTRIES 4

#undef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC contikimac_driver // nullrdc_driver //
#undef NULLRDC_CONF_802154_AUTOACK
#define NULLRDC_CONF_802154_AUTOACK       1

#undef NEIGHBOR_CONF_MAX_NEIGHBORS
#define NEIGHBOR_CONF_MAX_NEIGHBORS 16

#undef UIP_CONF_TCP
#define UIP_CONF_TCP 0

#define UIP_CONF_STATISTICS 1

#undef QUEUEBUF_CONF_NUM
#define QUEUEBUF_CONF_NUM 8

#undef CSMA_CONF_MAX_NEIGHBOR_QUEUES
#define  CSMA_CONF_MAX_NEIGHBOR_QUEUES 2
#endif
