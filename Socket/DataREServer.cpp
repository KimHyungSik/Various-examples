#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

int main() {
	system("title server");
	WSADATA	wsadata;
	SOCKET	server;
	SOCKADDR_IN serverIP = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	// 1. ���� ���� ����
	// AF_INET --> IPv4�� ��.��
	// SOCK_STREM --> TCP,	SOCK_DGRAM --> UDP
	// IPPROTO_TCP --> TCP
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//2. �ּ� ���� �� ���Ͽ� ���ε�
	serverIP.sin_family = AF_INET;
	serverIP.sin_port = 55000;
	serverIP.sin_addr.s_addr = inet_addr("192.168.0.42");

	bind(server, (LPSOCKADDR)&serverIP, sizeof(serverIP));


	//3. ������ Ŭ���̾�Ʈ�� ���
	if (listen(server, 5) == SOCKET_ERROR) {
		printf("���� ��� ���� \n");
		closesocket(server);
		return 0;
	}

	//Ư�� �ϳ��� Ŭ���̾�Ʈ ������ �޾Ƽ�
	
	//Ư�� Ŭ���̾�Ʈ�� ���� SOCKET
	SOCKET client;

	//Ŭ���̾�Ʈ ip+port ���� ����
	SOCKADDR_IN clientIP;
	int size = sizeof(clientIP);
	
	//Ŭ���̾�Ʈ ������ ������ �ش� Ŭ���̾�Ʈ�� ���� socket�� ����
	client = accept(server, (LPSOCKADDR)&clientIP, &size);
	if (client == INVALID_SOCKET) {
		printf("Ŭ���̾�Ʈ ��� ���� \n");
		closesocket(client);
		return 0;
	}

	printf("Ŭ���̾�Ʈ ���� ����");

	closesocket(server);

	//Ư�� Ŭ���̾�Ʈ�� Ŭ���̾�Ʈ ������ �̿��ؼ� 
	//������ �ۼ���
	int nR, nS; //���ŵ� ������ ����, �۽ŵ� ������ ����
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