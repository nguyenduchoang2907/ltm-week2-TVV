#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("PLEASE ENTER IP OR HOSTNAME:\n");
        return 0;
    }

    char *input = argv[1];
    struct hostent *host_info;

    struct in_addr ipv4;
    
    if (inet_pton(AF_INET, input, &ipv4) == 1) {
        host_info = gethostbyaddr(&ipv4, sizeof(struct in_addr), AF_INET);
        
        if (host_info == NULL || host_info->h_name == NULL) {
            printf("NOT FOUND INFORMATION\n");
        } else {
            printf("OFFICIAL NAME: %s\n", host_info->h_name);

            if (host_info->h_aliases != NULL && host_info->h_aliases[0] != NULL) {
                printf("ALIAS NAME:\n");
                for (char **alias = host_info->h_aliases; *alias != NULL; alias++) {
                    printf("%s\n", *alias);
                }
            }
        }
    } else {
        
        host_info = gethostbyname(input);
        
        if (host_info == NULL || host_info->h_addr_list == NULL) {
            printf("NOT FOUND INFORMATION\n");
        } else {
            printf("OFFICIAL IP: %s\n", inet_ntoa(*(struct in_addr *)host_info->h_addr_list[0]));
            printf("ALIAS IP:\n");
            for (char **ip = host_info->h_addr_list; *ip != NULL; ip++) {
                printf("%s\n", inet_ntoa(*(struct in_addr *)*ip));
            }
        }

    }

    return 0;
}