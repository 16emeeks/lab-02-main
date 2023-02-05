/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     * argc and argv[] is used to get user input upon program initilization. argv is a pointer to 
     an array of charicters while argc is contains the number of arguments
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
    
    A Unix file descriptor us a is a number that identifies a file. It handles things like pipes,
    sockets, or data streams.
    
    A file descriptor table is a data structure that keeps track of open files, file types, 
    position, status, etc.
    
     *
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     * a struct is an object that can hold variouse information. It can be thaught of as a custom 
     * data type.
     
	struct sockaddr_in 
	{
	  short            sin_family;   // address family (AF_INET)
	  unsigned short   sin_port;     // port number in network byte order
	  struct in_addr   sin_addr;     // internet address
	  char             sin_zero[8];  // padding to make struct the same size as sockaddr
	};
     
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
    	
         1) Comunication domain
         2) Socket Type
     *   3) particular socket protocol
     
         returns the socket descripter as a non negative number. If it fails will return -1
     */
    
    if (sockfd < 0) 
       error("ERROR opening socket");
       
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
    
       1) bind()
          a. socket descriptor returned by socket()
          b. adress to be assigned to the socket. Requires a sockaddr structure
     *	  c. the size of the sockaddr structure
     
       2) listen()
          a. socket descriptor returned by socket()
          b. maximum nunmber of pending connections
          
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
      
        * The server can only comnicate with one client at a time
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to 
	better handle multiple connections?
         *  fork() can be used to handle comuinication between multiple devices by copying 
         *  the process after the fork() command. this lets the server to listen for other 
         *  incomming connections
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        //printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 * A system call is a way a computer program requests a service form from the operation system,
 * bind(), listen(), and socket() are examples of a system call
 */
