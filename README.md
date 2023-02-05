# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Members
- team member 1: Elliott Meeks

## Lab Question Answers

Answer for Question 1: 
50% of what I sent to the server was lost. This happened because we forced a 50% 
packet lost on the local environment. So 50% of the outgoing packets were lost.

Answer for Question 2:
When I forced a 50% packet loss usinf TCP, no messages were lost. TCP is designed to be reliable. If  a packet is not recived, the reeciever asks the sender for the packet again, untill all packets are succesfully recieved.

Answer for Question 3:
TCP protocol is much slower because TCP verifies that it has recieved all the packets it was supposed to.

1. What is argc and *argv[]?
* argc and argv[] is used to get user input upon program initilization. argv is a pointer to 
an array of charicters while argc is contains the number of arguments


2. What is a UNIX file descriptor and file descriptor table?

A Unix file descriptor us a is a number that identifies a file. It handles things like pipes,
sockets, or data streams.

A file descriptor table is a data structure that keeps track of open files, file types, 
position, status, etc.

     
     
3. What is a struct? What's the structure of sockaddr_in?
a struct is an object that can hold variouse information. It can be thaught of as a custom 
data type.

struct sockaddr_in 
{
  short            sin_family;   // address family (AF_INET)
  unsigned short   sin_port;     // port number in network byte order
  struct in_addr   sin_addr;     // internet address
  char             sin_zero[8];  // padding to make struct the same size as sockaddr
};

     
     
4. What are the input parameters and return value of socket()

 1) Comunication domain
 2) Socket Type
 3) particular socket protocol

 returns the socket descripter as a non negative number. If it fails will return -1



5. What are the input parameters of bind() and listen()?

1) bind()
  a. socket descriptor returned by socket()
  b. adress to be assigned to the socket. Requires a sockaddr structure
  c. the size of the sockaddr structure

2) listen()
  a. socket descriptor returned by socket()
  b. maximum nunmber of pending connections
  

6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
The server can only comnicate with one client at a time


7. Research how the command fork() works. How can it be applied here to 
better handle multiple connections?
 fork() can be used to handle comuinication between multiple devices by copying 
 the process after the fork() command. this lets the server to listen for other 
 incomming connections. More generally, fork() can preform equivelent processes at the same time.
         
         
 This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
  
  A system call is a way a computer program requests a service form from the operation system,
  bind(), listen(), and socket() are examples of a system call
 
 
 
...
