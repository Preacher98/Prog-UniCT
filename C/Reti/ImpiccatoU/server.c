#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<time.h>

typedef struct utente
{
     struct sockaddr_in6 remote_addr;
     char nome[20];
     int port;
     int vite;
}utenti;

void oscuraFrase(char matrice[4][100], char fraseC[50], char fraseO[50]);
int controllaFrase(char fraseC[50], char fraseO[50], char lettera);

int main(int argc, char **argv){
    srand(time(0));
    utenti u1,u2;
    u1.vite=3;
    u2.vite=3;
    int sockfd, n;
    char ipv6_addr[46];
    struct sockaddr_in6 local_addr;
    socklen_t len = sizeof(struct sockaddr_in6);
    char lettera;
    char msg[100];
    memset(msg, 0, sizeof(msg));
    char matrice_frasi[4][100];
    memset(matrice_frasi, 0, sizeof(matrice_frasi));
    char fraseOscurata[50];
    memset(fraseOscurata, 0, sizeof(fraseOscurata));
    char fraseChiara[50];
    memset(fraseChiara, 0, sizeof(fraseChiara));
    strcpy(matrice_frasi[0],"bello il mondo");
    strcpy(matrice_frasi[1],"Warhammer quarantamila");
    strcpy(matrice_frasi[2],"enemy of the imperium");
    strcpy(matrice_frasi[3],"mamma mia");
    oscuraFrase(matrice_frasi,fraseChiara,fraseOscurata);
    printf("%s\n",fraseChiara);
    printf("%s\n",fraseOscurata);

    if(argc < 2){
        printf("Errore! Inserisci numero di port\n");
        return -1;
    }   

    sockfd = socket(AF_INET6, SOCK_DGRAM, 0);
    if(sockfd < 0){
        printf("Errore nell'apertura di socket\n");
        return -1;
    }

    memset(&local_addr, 0, len);
    local_addr.sin6_family = AF_INET6;
    local_addr.sin6_port = htons(atoi(argv[1]));
    
    if(bind(sockfd, (struct sockaddr *)&local_addr, len) < 0){
        printf("Errore nell'apertura di bind\n");
        return -1;
    }
    //-----------------------------------------------------------------
    //Giocatore 1
    n = recvfrom(sockfd, msg, 999, 0, (struct sockaddr *)&u1.remote_addr, &len);
    msg[n] = 0;
    strcpy(u1.nome,msg);
    u1.port=ntohs(u1.remote_addr.sin6_port);
    memset(msg, 0, sizeof(msg));
    sprintf(msg, "%s", "Connessione Giocatore 1 Eseguita");
    sendto(sockfd, msg, 999, 0, (struct sockaddr *)&u1.remote_addr, len);
    printf("Nome=%s P = %d\n",u1.nome, u1.port);
    //GIOCATORE 2 GIOCATORE 2 --------------------------------------
    n = recvfrom(sockfd, msg, 999, 0, (struct sockaddr *)&u2.remote_addr, &len);
    msg[n] = 0;
    strcpy(u2.nome,msg);
    u2.port=ntohs(u2.remote_addr.sin6_port);
    memset(msg, 0, sizeof(msg));
    sprintf(msg, "%s", "Connessione Giocatore 2 Eseguita");
    sendto(sockfd, msg, 999, 0, (struct sockaddr *)&u2.remote_addr, len);
    printf("Nome=%s P = %d\n",u2.nome, u2.port);

   for(;;){
        //GIOCATORE 1 GIOCATORE 1 ------------------------------------------
        sendto(sockfd, fraseOscurata, strlen(fraseOscurata), 0, (struct sockaddr *)&u1.remote_addr, len);
        n = recvfrom(sockfd, &lettera, sizeof(lettera), 0, (struct sockaddr *)&u1.remote_addr, &len);
        msg[n] = 0;
        printf("%c \n",lettera);
        if (controllaFrase(fraseChiara,fraseOscurata,lettera) == 0)
        {
            memset(msg, 0, sizeof(msg));
            u1.vite--;
            if (u1.vite <= 0)
            {
                sprintf(msg, "%s","Hai perso coglione");
                sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&u1.remote_addr, len);
                sprintf(msg, "%s","Hai vinto coglione");
                sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&u2.remote_addr, len);
                break;
            }else{
            sprintf(msg, "%s = %d","Errore hai sbagliato vite rimanenti ",u1.vite);
            sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&u1.remote_addr, len);
            }
        }else{
            sprintf(msg, "%s = %d","Hai indovinato delle lettere",u1.vite);
            sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&u1.remote_addr, len);
        }
        
                //GIOCATORE 2 GIOCATORE 2 ------------------------------------------
        sendto(sockfd, fraseOscurata, strlen(fraseOscurata), 0, (struct sockaddr *)&u2.remote_addr, len);
        n = recvfrom(sockfd, &lettera, sizeof(lettera), 0, (struct sockaddr *)&u2.remote_addr, &len);
        msg[n] = 0;
        printf("%c \n",lettera);
        if (controllaFrase(fraseChiara,fraseOscurata,lettera) == 0)
        {
            memset(msg, 0, sizeof(msg));
            u2.vite--;
            if (u2.vite <= 0)
            {
                sprintf(msg, "%s","Hai perso coglione");
                sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&u2.remote_addr, len);
                sprintf(msg, "%s","Hai vinto coglione");
                sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&u1.remote_addr, len);
                break;
            }else{
            sprintf(msg, "%s = %d","Errore hai sbagliato vite rimanenti ",u2.vite);
            sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&u2.remote_addr, len);
            }
        }else{
            sprintf(msg, "%s = %d","Hai indovinato delle lettere",u2.vite);
            sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&u2.remote_addr, len);
        }
        
        //GIOCATORE 2 GIOCATORE 2 ------------------------------------------
        /*n = recvfrom(sockfd, msg, 999, 0, (struct sockaddr *)&u1.remote_addr, &len);
        msg[n] = 0;
        inet_ntop(AF_INET6, &(u1.remote_addr.sin6_addr), ipv6_addr, INET6_ADDRSTRLEN);
        printf("IP = %s, P = %d, MSG = %s\n", ipv6_addr, ntohs(u1.remote_addr.sin6_port), msg);
        sendto(sockfd, msg, n, 0, (struct sockaddr *)&u1.remote_addr, len);*/
    }

    return 0;
}

void oscuraFrase(char matrice[4][100], char fraseC[50], char fraseO[50]){
    int rng = rand()%4;
    strcpy(fraseC,matrice[rng]);
    for (int i = 0; i < strlen(fraseC); i++)
    {
        if (fraseC[i]==' '){fraseO[i]=' ';}
        else{fraseO[i]='_';}
    }
}

int controllaFrase(char fraseC[50], char fraseO[50], char lettera){
    int counter=0;
    for (int i = 0; i < strlen(fraseC); i++)
    {
        if (fraseC[i]==lettera)
        {
            fraseO[i]=fraseC[i];
            counter++;
        }
        
    }
    return counter;
}