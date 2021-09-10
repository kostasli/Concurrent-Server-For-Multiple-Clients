#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "kat.h"

//global variables for faster transfer of data
int *Y, n, choice;
float *temp, a, *result_1;
max_min *result_2;
aY  *result_3;

//function to return error if the socket cannot be opened
void error(char *msg){
	perror(msg);
	exit(1);
}

void concurrent_server_prog_1(char *host)
{
	CLIENT *clnt;
	Y_arr  average_1_arg;
	Y_arr  maxmin_1_arg;
	a_mul_Y  product_1_arg;
	int i;

#ifndef	DEBUG
	clnt = clnt_create (host, CONCURRENT_SERVER_PROG, CONCURRENT_SERVER_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
		
		if(choice==1)
		{
			
			//match variables for average of Y
		
			average_1_arg.Y.Y_len=n;
			average_1_arg.Y_size=n;
			average_1_arg.Y.Y_val=(int *) malloc(n*sizeof(int));
		
			for(i=0;i<n;i++)
			average_1_arg.Y.Y_val[i] = Y[i];

			result_1 = average_1(&average_1_arg, clnt);
			
			if (result_1 == (float *) NULL) 
			{
				clnt_perror (clnt, "call failed");
			}
			
		}
		else if(choice==2)
		{
		
			maxmin_1_arg.Y.Y_len=n;
			maxmin_1_arg.Y_size=n;
			maxmin_1_arg.Y.Y_val=(int *) malloc(n*sizeof(int));
			
			for(i=0;i<n;i++)
			maxmin_1_arg.Y.Y_val[i] = Y[i];	
	
			result_2 = maxmin_1(&maxmin_1_arg, clnt);
			
			if (result_2 == (max_min *) NULL) 
			{
				clnt_perror (clnt, "call failed");
			}
			
		}		
		else if(choice==3)
		{
			//match variables for a*Y[]
			
			product_1_arg.Y.Y_len=n;
			product_1_arg.Y_size=n;
			product_1_arg.Y.Y_val=(int *) malloc(n*sizeof(int));
			
			for(i=0;i<n;i++)
			product_1_arg.Y.Y_val[i]=Y[i];	
			product_1_arg.a=a;
			
			result_3 = product_1(&product_1_arg, clnt);

			temp = (float *) malloc(n*sizeof(float));
			for(i=0;i<n;i++)
				temp[i]  =  result_3->prod.prod_val[i];
			
			if (result_3 == (aY *) NULL) 
			{
				clnt_perror (clnt, "call failed");
			}	
		}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

int main (int argc, char *argv[])
{
	char *host;
	int i, sockfd, newsockfd, portno, clilen;
  	pid_t procId;
	struct sockaddr_in serv_addr, cli_addr;
  	unsigned int children = 0;

	if (argc < 3) {
		printf ("usage: %s server_host port_number\n", argv[0]);
		exit (1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
	error("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
  	portno = atoi(argv[2]);
  	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(portno);
  	serv_addr.sin_addr.s_addr = INADDR_ANY;

  	if (bind(sockfd, (struct sockaddr *) &serv_addr,
	sizeof(serv_addr)) < 0)
  	error("ERROR on binding");

  	listen(sockfd,5);

  for (;;)  {

    printf("Waiting for a connection...\n");
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
    error("ERROR on accept");

	//fork is used for implementing the parallel use of many clients
    if (fork() == 0)  { 

      close (sockfd);
      printf("Connected.\n");

      do {
		  
        host = argv[1];

        //receive choice from client
		
        recv(newsockfd, &choice, sizeof(int), 0);

        if (choice == 1){

          //receive the appropriate data from client and send the result

          recv(newsockfd, &n, sizeof(int), 0);
          Y=(int *)malloc(n*sizeof(int));
          recv(newsockfd, Y, n*sizeof(int), 0);
          concurrent_server_prog_1(host);
          send(newsockfd,result_1, sizeof(float), 0);

        }

        else if (choice == 2){

          //receive the appropriate data from client and send the result

          recv(newsockfd, &n, sizeof(int), 0);
          Y=(int *)malloc(n*sizeof(int));
          recv(newsockfd, Y, n*sizeof(int), 0);
          concurrent_server_prog_1(host);
          send(newsockfd,result_2, 2*sizeof(int), 0);

        }

        else if (choice == 3){

          //receive the appropriate data from client and send the result

          recv(newsockfd, &n, sizeof(int), 0);
          Y=(int *)malloc(n*sizeof(int));
          recv(newsockfd, Y, n*sizeof(int), 0);
          recv(newsockfd, &a, sizeof(float), 0);
          concurrent_server_prog_1(host);
          send(newsockfd, temp, n*sizeof(float), 0);

        }

      } while (1);
      exit (0) ;
    }
    close(newsockfd);

    children++;

    while (children){

      procId=waitpid((pid_t) -1, NULL, WNOHANG);

      if (procId<0) error("waitpid error");
      else if (procId==0) break;
      else printf("\n");

    }
  }
  return 0;
}
