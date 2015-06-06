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
int sock,bytes_recv;
struct sockaddr_in server_addr;
char recv_data[1024],send_data[1024],cmd[20],recvbuf[1024];
struct hostnet *host;
int choice;
int x=0,flag=0;
double load1,load2,minload;
char *ptr;
while(x==0){
printf("\n\n\t THIS IS THE CLIENT PROGRAM \n\n");
printf("\n THE FUNCTIONS PROVIDED ARE AS FOLLOWS: \n1. LOAD BALANCING\n2. REMOTE COMMAND EXECUTION\n3. EXIT\n\n");

label:printf("Enter your choice below:\n");
scanf("%d",&choice);

switch(choice){

case 1://create socket
           if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
           perror("Socket");
            exit(1);
              }
  
      server_addr.sin_family=AF_INET;         	       	           //internet protocol(AF_INET)
      server_addr.sin_port=htons(5001);                     		   //address port(16 bits)
      server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");               //Internet address(32 bits)
  
    //establishing the connection: connect(sockfd,address of passive participant,address length)
                                      
      if((connect(sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)))==-1){
       perror("Connect");
       exit(1);
        }
  
      // perform the function
                                                 
     while(1){
       bytes_recv=recv(sock,recv_data,1024,0);                 //recv(sockid, recvBuf, buflen, flags)
       recv_data[bytes_recv]='\0';
      // if(strcmp(recv_data,"q")==0){
       //    close(sock);
        //   break;
         //    }
          // else{
      //     printf("The received data is %s\n",recv_data);       //print the data received by the server
             load1 =strtod(recv_data,&ptr);
             printf("\nLoad of system 1: %.2f\n",load1);

           break;
        }
          
       break;   //must remove


      /*
            if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
           perror("Socket");
            exit(1);
              }

            server_addr.sin_family=AF_INET;                              //internet protocol(AF_INET)
            server_addr.sin_port=htons(5003);                                    //address port(16 bits)
            server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");               //Internet address(32 bits)

              if((connect(sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)))==-1){
              perror("Connect");
              exit(1);
                }
              
              while(1){
             bytes_recv=recv(sock,recv_data,1024,0);                 //recv(sockid, recvBuf, buflen, flags)
             recv_data[bytes_recv]='\0';
             if(strcmp(recv_data,"q")==0){
                close(sock);
                 break;
              }
            else{
             printf("The received data is %s\n",recv_data);       //print the data received by the server
             load2 =strtod(recv_data,&ptr);
             printf("\nLoad of system 2: %.2f\n",load1);

              break;
          }
        }
         if(load1>load2) {
                printf("System 2 has the least load , command to be executed in system 2");
                minload=load2;
                flag=1;
                }  
            else{
              printf("System 1 has the least load , command to be executed in system 1");
               minload=load1;
           }
       
   */

           break;






case 2:  //if(flag==0){ 
        //creates socket for system1 
        if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("Socket");
        exit(1);
        }

        server_addr.sin_family=AF_INET;                                   //internet protocol(AF_INET)
        server_addr.sin_port=htons(5008);                                 //address port(16 bits) of rpc server
        server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");               //Internet address(32 bits)

       //establishing the connection: connect(sockfd,address of passive participant,address length)
  
        if((connect(sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)))==-1){
        perror("Connect");
        exit(1);
             }
      // perform the function
  
  
      while(1){
          printf("Enter the command you wish to execute remotely (Eg: ls , dir),\n {type quit to exit}\n");
          scanf("%s",cmd);
             if(strcmp(cmd,"quit")==0)
                  break;
           send(sock,cmd,strlen(cmd),0);
             

           bytes_recv=recv(sock,recv_data,1024,0);                 //recv(sockid, recvBuf, buflen, flags)
           recv_data[bytes_recv]='\0';
            printf("\nData Received from server:\n %s\n\n",recv_data);  
              }
    // }
        


//else{

        /*  // creates socket for system2
    system2:   if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
               perror("Socket");
               exit(1);
              }

              server_addr.sin_family=AF_INET;                                   //internet protocol(AF_INET)
              server_addr.sin_port=htons(5007);                                 //address port(16 bits) of rpc server
              server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");               //Internet address(32 bits)

              if((connect(sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr)))==-1){
              perror("Connect");
             exit(1);
             }

               while(1){
                printf("Enter the command you wish to execute remotely (Eg: ls , dir), or say quit to exit\n");
                scanf("%s",cmd);
                if(strcmp(cmd,"quit")==0)
                  break;
                send(sock,cmd,strlen(cmd),0);


                bytes_recv=recv(sock,recv_data,1024,0);                 //recv(sockid, recvBuf, buflen, flags)
                recv_data[bytes_recv]='\0';
                 printf("\nData Received from server:\n %s\n\n",recv_data);
              }

  


     } */    
          


case 3: x=1;
        break;





  default: printf("Invalid option\n");
     }
    }

   return 0;
  }






/*to convert string to float
 *  *  num =strtod(message,&ptr);
 *   *   printf("\nIn variable num:%.2f\n",num);
 *    *     */

