#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include<string>

int main() {
	char buf[256];
	system("title client");
	WSADATA wsadata;
	SOCKET server;
	SOCKADDR_IN serverIP = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	serverIP.sin_family = AF_INET;
	serverIP.sin_port = 55000;
	serverIP.sin_addr.s_addr = inet_addr("192.168.0.");

	int addTark = 10;

	int nRet = connect(server, (LPSOCKADDR)&serverIP, sizeof(serverIP));
	while (nRet == SOCKET_ERROR) {
		printf("서버 연결 에러 \n");
		char ipTrak[13] = "192.168.0.";
		char num[2];
		_itoa(addTark, num, 10);

		strcat(ipTrak, num);

		serverIP.sin_addr.s_addr = inet_addr(ipTrak);
		nRet = connect(server, (LPSOCKADDR)&serverIP, sizeof(ipTrak));
		printf("%s\n", ipTrak);
		addTark++;
		if (addTark > 99) {
			closesocket(server);
			return 1;
		}
	}

	printf("서버에 접속 성공....\n");

	//데이터 송수신
	int nR, nS;

	do {
		printf("[clinet] : ");
		gets_s(buf, 256);
		if (strcmp(buf, "bye") == 0)
			break;
		nS = send(server, buf, strlen(buf)+1, 0);
		nR = recv(server, buf, 256, 0);
		printf("[server] : %s\n", buf);
	} while (1);

	closesocket(server);
	WSACleanup();
	return 1;
}