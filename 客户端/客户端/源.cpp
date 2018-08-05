#include <iostream>
#include <Winsock2.h>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;
int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}


	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}
	else
		printf("The Winsock 2.2 dll was found okay\n");
	SOCKET sockListen=socket(AF_INET ,SOCK_DGRAM ,IPPROTO_UDP );
	if (sockListen==INVALID_SOCKET )
	{
		WSACleanup();
		return 1;
	}
	BOOL bopt=TRUE;
	setsockopt(sockListen,SOL_SOCKET,SO_BROADCAST,(char *)&bopt,sizeof(bopt));
	sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(1234);
	addr.sin_addr.S_un.S_addr=inet_addr("255,255,255,255");
	sockaddr_in addrClient;
	int nSize=sizeof(addrClient);
	char szbuf[1024]={0};
	
	while (1)
	{
		cin>>szbuf;
		sendto(sockListen,szbuf, sizeof(szbuf), 0, (SOCKADDR *) & addr, sizeof (addr));
	}
	
	closesocket(sockListen);
	//πÿ√≈ -- –∂‘ÿø‚-- WSACleanUp
	WSACleanup();

	system("pause");
	return 0;
}