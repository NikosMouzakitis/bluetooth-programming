#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main() {

    inquiry_info *devices = NULL;

    int max_devices = 8;  // Maximum number of devices to retrieve
    int len = 8;          // Inquiry duration in seconds

    int device_count, i;

    // Allocate memory for device array
    devices = (inquiry_info*)malloc(max_devices * sizeof(inquiry_info));
    if (!devices) {
        perror("malloc");
        exit(1);
    }

    // Open Bluetooth adapter
    int dev_id = hci_get_route(NULL);
    int sock = hci_open_dev(dev_id);
    if (dev_id < 0 || sock < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Set inquiry parameters
    device_count = hci_inquiry(dev_id, len, max_devices, NULL, &devices, IREQ_CACHE_FLUSH);

    // Print MAC addresses
    for (i = 0; i < device_count; i++) {
        bdaddr_t *addr = &(devices + i)->bdaddr;
        char addr_str[18];  // 17 characters for the MAC address + 1 for null terminator
        ba2str(addr, addr_str);
        printf("Device %d: %s\n", i + 1, addr_str);
    }

    // Clean up
    free(devices);
    close(sock);

    return 0;
}

