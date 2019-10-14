// SocketScanner.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")

#define port_closed 0
#define host_unresolved -1
#define port_open 1

int main()
{
	SOCKET socket;
	int error, MinPort, MaxPort, port;
	char ws[1024], buff[256], host[512];
	std::cout << "Enter hosst name : ";
	std::cin >> host;
	std::cout << "Socket list for " << host << " :\n";

}

DWORD CheckConnection(char* host, WORD port) {
	DWORD result = host_unresolved;

	hostent* hostInfo;
	sockaddr_in Destination_Addr;
	SOCKET m_Socket;

	if (hostInfo = gethostbyname(host)) {
		Destination_Addr.sin_family = AF_INET;
		Destination_Addr.sin_port = htons(port);
		Destination_Addr.sin_addr = *((struct in_addr*)hostInfo - &gt, h_addr);
		memset(&(Destination_Addr.sin_zero), 0, 8);
		if ((m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) != SOCKET_ERROR) {
			if (connect(m_Socket, (sockaddr*)& Destination_Addr, sizeof(sockaddr)) == NULL) {
				result = port_open;
			}
			else {
				result = port_closed;
			}
			closesocket(m_Socket);
		}
	}
	return result;
}