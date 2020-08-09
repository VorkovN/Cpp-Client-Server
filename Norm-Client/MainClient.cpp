#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include "Client.h"
#pragma warning(disable: 4996)


Client client;

void ClientHandler() {
	int msg_size;
	while (true) {
		recv(client.Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(client.Connection, msg, msg_size, NULL);
		cout << msg << endl;
		delete[] msg;
	}
}

int main(int argc, char* argv[]) {
	

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	string msg1;
	while (true) {
		getline(cin, msg1);
		int msg_size = msg1.size();
		send(client.Connection, (char*)&msg_size, sizeof(int), NULL);
		send(client.Connection, msg1.c_str(), msg_size, NULL);
		Sleep(10);
	}

	system("pause");
	return 0;
}
