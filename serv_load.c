#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>

int main(){
  struct sockaddr_in server_addr , client_addr;
  int sock,connected,bytes_recv;
  char send_data[1024],recv_data[1024],ans[5];
  int sin_size,freemem[5];
  double load=0.0;
  FILE *fr;
  char *message,*ptr;

printf("---------------------WELCOME TO LOAD COMPUTING SERVER------------------------\n\n");
   //establish the 'sock' file descriptor 
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("Socket");
        exit(1);
       }
   
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(5001);
  server_addr.sin_addr.s_addr=INADDR_ANY;

  //bind(sockid, &addrport, size): assosciates and reserves a port for use by the socket

  if(bind(sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr))==-1){
    perror("Unable to bind");
    exit(1);
      }

 //listen(sockid,queuelen(number of participants that can wait for a connection)):To listen for connections

 if(listen(sock,5)==-1){
    perror("Listen");
    exit(1);
  }

label:  printf("COMPUTING THE IDLE CPU\n");
   sin_size= sizeof(struct sockaddr_in);

  //accept(sockid, &clientAddr, &addrLen) : server gets socket for incoming client by calling accept

 connected=accept(sock, (struct sockaddr*)&client_addr, &sin_size);    //connected=new socket(used for data transfer)
while(1){  
   while(1){
  //execute mpstat command and redirect output into "loadval" file    
   system("mpstat;mpstat>loadval");
   printf("System IDLE(in %):\n");
  //get only the idle value from the data present in the file and store it in another file called loadval1
   system("tail -c -6 loadval>loadval1");
    fr = fopen("loadval1", "r");
   /*create variable of stat*/
   struct stat stp ={0};
   /*These functions return information about a file. No permissions are required on the file itself*/
   stat("loadval1", &stp);
   /*determine the size of data which is in file*/
   float filesize = stp.st_size;
   /*allocates the address to the message pointer and allocates memory*/
   message = (char *) malloc(sizeof(char) * filesize);
      if (fread(message, 1, filesize - 1, fr) == -1) {
          printf("\nerror in reading\n");
          /**close the read file*/
          fclose(fr);
          /*free input string*/
          free(message);
      }
printf("The Load of the system is: %s\n",message);
send(connected,message,strlen(message),0);
break;
 }

   printf("do you wish to quit?\n");
   scanf("%s",ans);
   if((strcmp(ans,"yes"))==0)
        break;
   else{
      system("clear");
      goto label;
      } 
 }
   
  close(sock);
   
}





/*to convert string to float
 *  num =strtod(message,&ptr);
 *   printf("\nIn variable num:%.2f\n",num);
 *     */

