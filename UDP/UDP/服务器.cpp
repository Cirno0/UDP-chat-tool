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
	sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(1234);
	addr.sin_addr.S_un.S_addr=INADDR_ANY;
	int temp=bind(sockListen,(const sockaddr *)&addr,sizeof(addr));
	if (temp==SOCKET_ERROR)
	{
		closesocket(sockListen);
		WSACleanup();
		return 1;
	}
	sockaddr_in addrClient;
	int nSize=sizeof(addrClient);
	char szbuf[1024]={0};
	
	
	while (1)
	{
		int nres=recvfrom(sockListen,szbuf,sizeof(szbuf),0,(sockaddr *)&addrClient,&nSize);
		
		if (nres>0)
		{
			cout<<inet_ntoa(addrClient.sin_addr)<<" say:"<<szbuf<<endl;
			/*cin>>szbuf;
			sendto(sockListen,szbuf, sizeof(szbuf), 0, (SOCKADDR *) & addrClient, sizeof (addrClient));
			*/
		}
	}
	closesocket(sockListen);
	//πÿ√≈ -- –∂‘ÿø‚-- WSACleanUp
	WSACleanup();

	system("pause");
	return 0;
}