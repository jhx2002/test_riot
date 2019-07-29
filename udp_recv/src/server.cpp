#include <stdio.h>   
#include <sys/types.h>   
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <unistd.h>   
#include <errno.h>   
#include <string.h>   
#include <stdlib.h>   
#include <arpa/inet.h>
   
#define SERV_PORT   10000   
char* sv_ipv6 = "fe80::f58c:2fb7:adad:1%enp2s0";

// test :
// echo “hello” > /dev/udp/fe80::f58c:2fb7:adad:1%enp2s0/1111


int main()  
{  
  /* sock_fd --- socket文件描述符 创建udp套接字*/  
  int sock_fd = socket(AF_INET6, SOCK_DGRAM, 0);
  if(sock_fd < 0)  {
      perror("socket");  
      exit(1);  
  }  

  /*声明服务器地址和客户链接地址*/
  struct sockaddr_in6 addr_serv;

  /* 设置服务器sockaddr_in6结构*/
  bzero(&addr_serv , sizeof(addr_serv));

  addr_serv.sin6_family = AF_INET6;
  //  addr_serv.sin6_addr = in6addr_any;
  addr_serv.sin6_port = htons(SERV_PORT);

  if(inet_pton(AF_INET6 , sv_ipv6 , &addr_serv.sin6_addr) < 0) {
      printf("inet_pton error for %s\n",sv_ipv6);
      exit(1);
  }

  /* 绑定socket */  
  if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)   {
      perror("bind error:");  
      exit(1);  
  }  
    
  int recv_num;  
  char recv_buf[20];  
  struct sockaddr_in6 addr_client;  
   
  while(1)  {
      printf("server wait:\n");  
       
      recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0,
			  (struct sockaddr *)&addr_client, (socklen_t *)&recv_num);  
      if(recv_num < 0) {
	  perror("recvfrom error:");  
	  exit(1);  
      }  
  
      recv_buf[recv_num] = '\0';  
      printf("server receive %d bytes: %s\n", recv_num, recv_buf);  
  }
     
  close(sock_fd);
  
  return 0;  
}
