
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <memory.h>

int main(int argc,char **argv)
{
	int fd;
	int len;
	char recvBuf[100] = {0};
	struct sockaddr_in server_addr;
	
	if(argc != 2)
	{
		printf("%s:%d Parameter is wrong!\r\n",__FUNCTION__,__LINE__);
		return -1;
	}
	
	if((fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("%s:%d Create a TCP socket failed!\r\n",__FUNCTION__,__LINE__);
		return -1;
	}

	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(13);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(fd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
	{
		printf("%s:%d Connet to time server failed!\r\n");
		return -1;
	}

	while((len = read(fd,recvBuf,100)) >0)
	{
		printf("Time: %s\r\n",recvBuf);
	}
	
	return 0;
}
