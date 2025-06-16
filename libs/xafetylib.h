#ifndef XAFETY
#define XAFETY
#include <stdlib.h>
#include <pcap.h>
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
int sniff(void);
#endif