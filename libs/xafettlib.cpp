#include "xafetylib.h"
#include <stdio.h>
#include <pcap.h>
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    printf("Paquete capturado: %d bytes - Timestamp: %ld.%ld\n", 
           header->len, header->ts.tv_sec, header->ts.tv_usec);
}

int sniff() {
    pcap_if_t *alldevs, *d;
    char errbuf[PCAP_ERRBUF_SIZE];
    int i = 0, interface = 0;

    // Obtain a list of interfaces
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Error when looking for interfaces: %s\n", errbuf);
        return 1;
    }

    // List interfaces
    printf("Available interfaces:\n");
    for (d = alldevs; d; d = d->next) {
        printf("%d. %s", ++i, d->name);
        if (d->description)
            printf(" (%s)", d->description);
        printf("\n");
    }

    if (i == 0) {
        printf("No interfaces found.\n");
        return 0;
    }

    // Ask the user for a interface
    printf("Select an interface (number): ");
    scanf("%d", &interface);

    if (interface < 1 || interface > i) {
        printf("Invalid number.\n");
        pcap_freealldevs(alldevs);
        return 0;
    }

    // Look for the selected interface
    d = alldevs;
    for (i = 1; i < interface; i++)
        d = d->next;

    // Open selected interface
    pcap_t *handle = pcap_open_live(d->name, 65536, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open the interface: %s\n", errbuf);
        pcap_freealldevs(alldevs);
        return 1;
    }

    printf("Hearing packages... (Ctrl+C to exit)\n");

    // Capture packets in real time
    pcap_loop(handle, 0, packet_handler, NULL);

    // Close session on interfaces
    pcap_close(handle);
    pcap_freealldevs(alldevs);
    return 0;
}