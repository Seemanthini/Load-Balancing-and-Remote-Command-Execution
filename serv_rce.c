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

int main(){
  struct sockaddr_in server_addr , client_addr;
  int sock,connected,bytes_recv;
  char send_data[1024],recv_data[1024],recvbuf[1000],buf1[1000];
  int sin_size,choice,i;
  char cmd[10],c,answer[10];
  FILE *fp;

printf("------------------------WELCOME REMOTE COMMAND EXECUTION SERVER----------------------------\n");
   //establish the 'sock' file descriptor 

    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("Socket");
        exit(1);
       }
   
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(5008);
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

   sin_size= sizeof(struct sockaddr_in);

  //accept(sockid, &clientAddr, &addrLen) : server gets socket for incoming client by calling accept

 connected=accept(sock, (struct sockaddr*)&client_addr, &sin_size);    //connected=new socket(used for data transfer)


 while(1){
  label:  printf("waiting for command to be received.... \n");     
           bytes_recv=recv(connected,recv_data,1024,0);                 //recv(sockid, recvBuf, buflen, flags)
                   recvbuf[strlen(recvbuf)-1]=0;

         if(strcmp(recv_data,"q")==0){
                  close(sock);
                  break;
              }
       else
         printf("\nThe received data is %s\n",recv_data);
             strcpy(recvbuf,recv_data);
             strcat(recvbuf,">file");  // add to redirected file
	   printf("Recvbuf:%s\n",recvbuf); // ls>file
	     int status=0;
 	  pid_t pid=vfork();
 	  if(pid==0)
   	 execlp("sh","sh","-c",recvbuf,(char *)0); // executed the ls command and redirected to  file 
             else
             {
     	     wait(&status);
    	     fp=fopen("file","r"); //open the file read the content and stored to buffer
         	 while((c=getc(fp))!=EOF)
       	           buf1[i++]=c;
       	           buf1[i]='\0';
                   printf("%s\n",buf1);
                fclose(fp);
              send(connected,buf1,1000,0);   //sending the contents of the file to the client
         
           }
printf("do you wish to terminate the server?\n");

scanf("%s",answer);
  if(strcmp(answer,"yes")==0){ 
   close(sock);
   return 0;
   }
else{
   system("clear");
   goto label;
  }

}

}
