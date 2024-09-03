#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc, char **argv){

    int sockfd, n;
    struct sockaddr_in6 remote_addr;
    char sendline[1000];
    char recvline[1000];
    char nome[20];
    memset(nome, 0, sizeof(nome));
    char car='0';
    char ipv6_addr[INET6_ADDRSTRLEN];
    socklen_t len = sizeof(struct sockaddr_in6);

    if(argc != 3){
        printf("Errore! Inserisci IPv6 e port\n");
        return -1;
    }

    if((sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0){
        printf("Errore nell'apertura di socket\n");
        return -1;
    }

    memset(&remote_addr, 0, len);
    remote_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, argv[1], &(remote_addr.sin6_addr));
    remote_addr.sin6_port = htons(atoi(argv[2]));

    printf("Inserisci il nome: ");
    scanf(" %s",nome);
    sendto(sockfd, nome, strlen(nome), 0, (struct sockaddr *)&remote_addr, len);
    n = recvfrom(sockfd, recvline, 999, 0, (struct sockaddr *)&remote_addr, &len);
        recvline[n] = 0;
    printf("%s",recvline);
    for(;;){

        n = recvfrom(sockfd, recvline, 999, 0, (struct sockaddr *)&remote_addr, &len);
        recvline[n] = 0;
        printf("\n %s frase in gioco\n",recvline);
        char c;
       // while ((c = getchar()) != '\n' && c != EOF); //Importante per pulire il buffer
        printf("inserisci la lettera da provare: ");
        scanf(" %c", &car);
        sendto(sockfd, &car, sizeof(car), 0, (struct sockaddr *)&remote_addr, len);
        //printf("%c",car);
        //ricezione esito lettera
        n = recvfrom(sockfd, recvline, 999, 0, (struct sockaddr *)&remote_addr, &len);
        recvline[n] = 0;
        if(strcmp(recvline,"Hai perso coglione")==0 || strcmp(recvline,"Hai vinto coglione")==0){printf("%s ",recvline); break;}
        else{printf("%s",recvline);}
        /*sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&remote_addr, len);
        n = recvfrom(sockfd, recvline, 999, 0, (struct sockaddr *)&remote_addr, &len);
        recvline[n] = 0;
        inet_ntop(AF_INET6, &(remote_addr.sin6_addr), ipv6_addr, INET6_ADDRSTRLEN);
        printf("IPv6 = %s, Port = %d, Msg = %s\n", ipv6_addr, ntohs(remote_addr.sin6_port), recvline);*/
    }

    return 0;
}