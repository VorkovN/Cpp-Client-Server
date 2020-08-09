#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>
#include "Client.h"
#pragma warning(disable: 4996)


Client client;

void ClientHandler() {
	char msg[256];
	while (true) {
		if (recv(client.Connection, msg, 256, NULL) > 0) {
			cout << msg << endl;
			Sleep(10);
			cout << "2\n";
		}
	}
}

int main(int argc, char* argv[]) {
	

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	char msg1[256];
	while (true) {
		cin.getline(msg1, sizeof(msg1));
		send(client.Connection, msg1, sizeof(msg1), NULL);
		Sleep(10);
		cout << "1\n";
	}

	system("pause");
	return 0;
}
