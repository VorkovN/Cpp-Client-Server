#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <set>
#include "Server.h"
#pragma warning(disable: 4996)

using namespace std;

Server server;

void ClientHandler(SOCKET current_socket) {
	int msg_size;
	while (true) {
		recv(current_socket, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(current_socket, msg, msg_size, NULL);
		for (const SOCKET& socket : server.connections) {
			if (socket == current_socket) {
				continue;
			}

			send(socket, (char*)&msg_size, sizeof(int), NULL);
			send(socket, msg, msg_size, NULL);
		}
		delete[] msg;
	}
}

int main(int argc, char* argv[]) {




	while (true) {
		SOCKET newConnection = accept(server.sListen, (SOCKADDR*)&server.addr, &server.sizeofaddr);

		if (newConnection == 0) {
			cout << "Error #2\n";
		}
		else {
			cout << "Client Connected!\n";
			string msg = "Hello. It`s my first network program!";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);

			server.connections.insert(newConnection);
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(newConnection), NULL, NULL);
		}
	}


	system("pause");
	return 0;
}