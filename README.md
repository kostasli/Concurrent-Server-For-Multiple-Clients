# Concurrent-Server-For-Multiple-Clients
This server will need to perform some calculations. Communication is via TCP AF_INET (internet domain) sockets. The socket-Server process receives data from the socket-Clients processes and produces the result via Remote Procedure Call. The README file contains the steps we followed to complete the exercise.

Step 1:
Initially, we installed rpcbind to be able to use the privileges it provides. Giving the command to the terminal:
sudo apt-get install rpcbind
Then, to see that it was successfully installed, we ran the rpcinfo command.

Step 2:
Then we started writing the kat.x program which is the interface file that through rpcgen automatically generates the required system modules and templates for the two application modules that we will need.

The kat.x program defines three different functions for each query.

Step 3:
Once kat.x has been created, just run the rpcgen -a -C kat.x command in the terminal. The -a parameter means that we want all files to be generated and the -C parameter means that we want them to be generated structured in ANSI C.

Step 4:
From the generated files we modified only kat_client.c and kat_server.c. As described in the pronunciation, the socket-Server should operate in parallel as an RPC-Client, ie kat_client should implement this purpose.
Of course, we first implemented the socket_client.c program which represents users requesting information from the remote server.

The program briefly accepts two parameters hostname and port so that the socket connection can be made. Then, after the necessary checks are done, she waits to connect to a server to get the information she needs. Then, as requested in the exercise, the menu is repeatedly displayed that asks the user for the necessary data and based on the choice of 1,2 or 3 sends the corresponding information. With option 4 the program ends.

Step 5:
After socket_client.c the two programs kat_client.c and kat_server.c were modified which were created automatically as mentioned above. Kat_client.c acts as an intermediary between socket_client and kat_server. In short, once connected, a user prints Connected in the terminal and depending on the user's choice sends the necessary data to the server for processing. This program is properly designed with the help of the fork command so that it serves multiple users at the same time. The kat_client.c program also accepts two parameters, the host name and the port number.

Step 6:
Finally, the program kat_server.c was modified which only collects the information and processes the data by making the necessary calculations and printing each time the function that the user chose to call. This program does not accept some parameters.

Remarks: The make command is used to generate executable files of all programs except socket_client.c which is done with the gcc -o client socket_client.c command.
The port number used is a random four-digit number whose value, however, must not be reserved. 
