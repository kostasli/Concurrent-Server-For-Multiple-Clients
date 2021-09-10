#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

//function to return error if the socket cannot be opened
void error(char *msg){

  perror(msg);
  exit(0);
}

int main(int argc, char *argv[]){

  int i, result_2[2], choice, n, flag = 1;
  float a, result_1, *result_3;
  int sockfd, portno;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  int *Y;

  //Usage
  if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }

  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    error("ERROR opening socket");

  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
  serv_addr.sin_port = htons(portno);


  printf("Trying to connect...\n");
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");

  printf("Connected.\n");
  do {
    //menu
	printf("1. Calculate average of Y\n");
	printf("2. Calculate maximum and minimum of Y\n");
	printf("3. Calculate a*Y[]\n");
	printf("4. Exit\n");
	fflush(stdout);
    printf("\n\nEnter choice: ");
    scanf("%d", &choice);
    send(sockfd, &choice, sizeof(int), 0);


    if (choice == 1){

    
      printf("Give size of Y[]: ");
      scanf("%d", &n);
      send(sockfd, &n, sizeof(int), 0);
      Y = (int *) malloc(n*sizeof(int));

      for(i=0;i<n;i++){
        printf("Y[%d] = ", i+1);
        scanf("%d", &Y[i]);

      }
      send(sockfd, Y, n*sizeof(int), 0);
      recv(sockfd, &result_1, sizeof(float), 0);
      printf("\n\nAverage of Y[]: %.2f\n\n\n\n",result_1);

    }

    else if (choice == 2){

      printf("\n\n\nGive size of Y[]: ");
      scanf("%d", &n);
      send(sockfd, &n, sizeof(int), 0);
      
      Y = (int *) malloc(n*sizeof(int));

      for(i=0;i<n;i++){
        printf("Y[%d] = ", i+1);
        scanf("%d", &Y[i]);

      }
      send(sockfd, Y, n*sizeof(int), 0);

      recv(sockfd, result_2, 2*sizeof(int), 0);
      printf("\n\nMax: %d\nMin: %d.\n\n\n\n", result_2[0], result_2[1]);

    }
    else if (choice == 3) {

      printf("Give size of Y[]: ");
      scanf("%d", &n);
      send(sockfd, &n, sizeof(int), 0);

      Y = (int *) malloc(n*sizeof(int));

      for(i=0; i<n; i++){
        printf("Y[%d] = ", i+1);
        scanf("%d", &Y[i]);

      }
      send(sockfd, Y, n*sizeof(int), 0);

      printf("Give floating number a: ");
      scanf("%f", &a);
      send(sockfd, &a, sizeof(float), 0);
      
      result_3 = (float *) malloc(n*sizeof(float));
      recv(sockfd, result_3, n*sizeof(float), 0);
      printf("\n\n");

      for(i=0; i<n; i++)
        printf("a*Y[%d] = %.2f\n\n\n\n", i+1, result_3[i]);


    }
    else if (choice == 4)
      flag = 0;

    else
      printf("Wrong option, please try again\n");


  } while (flag);
  close(sockfd);

  return 0;
}
