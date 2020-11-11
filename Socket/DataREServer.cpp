#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

int main() {
	system("title server");
	WSADATA	wsadata;
	SOCKET	server;
	SOCKADDR_IN serverIP = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	// 1. 서버 소켓 생성
	// AF_INET --> IPv4를 의.미
	// SOCK_STREM --> TCP,	SOCK_DGRAM --> UDP
	// IPPROTO_TCP --> TCP
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//2. 주소 설정 및 소켓에 바인딩
	serverIP.sin_family = AF_INET;
	serverIP.sin_port = 55000;
	serverIP.sin_addr.s_addr = inet_addr("192.168.0.42");

	bind(server, (LPSOCKADDR)&serverIP, sizeof(serverIP));


	//3. 서버가 클라이언트를 대기
	if (listen(server, 5) == SOCKET_ERROR) {
		printf("서버 대기 에러 \n");
		closesocket(server);
		return 0;
	}

	//특정 하나의 클라이언트 접속을 받아서
	
	//특정 클라이언트를 위한 SOCKET
	SOCKET client;

	//클라이언트 ip+port 저장 변수
	SOCKADDR_IN clientIP;
	int size = sizeof(clientIP);
	
	//클라이언트 접속이 들어오면 해당 클라이언트에 대한 socket에 저장
	client = accept(server, (LPSOCKADDR)&clientIP, &size);
	if (client == INVALID_SOCKET) {
		printf("클라이언트 대기 에러 \n");
		closesocket(client);
		return 0;
	}

	printf("클라이언트 접속 성공");

	closesocket(server);

	//특정 클라이언트와 클라이어트 소켓을 이용해서 
	//데이터 송수신
	int nR, nS; //수신된 데이터 길이, 송신된 데이터 길이
	char buf[256];

	do {
		nR = recv(client, buf, 256, 0);
		nS = send(client, buf, nR, 0);
		if (nS == SOCKET_ERROR)
			break;
	} while (nR > 0);

	closesocket(client);
	WSACleanup();
	return 1;
}