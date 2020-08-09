#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <set>
#include "Server.h"
#pragma warning(disable: 4996)

using namespace std;

Server server;

void ClientHandler(SOCKET current_socket) {
	char msg[256];
	while (true) {
		if (recv(current_socket, msg, sizeof(msg), NULL) > 0) {
			for (const SOCKET& socket : server.connections) {
				if (socket == current_socket) {
					continue;
				}
				send(socket, msg, sizeof(msg), NULL);
			}

			cout << "4" << msg << endl;
		}
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
			char msg[256] = "Hello. It`s my first network program!";
			send(newConnection, msg, sizeof(msg), NULL);
			server.connections.insert(newConnection);


			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(newConnection), NULL, NULL);
			cout << "3\n";
		}

	}


	system("pause");
	return 0;
}