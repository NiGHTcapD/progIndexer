// progIndexer.cpp : Defines the entry point for the console application.
//

#pragma comment(lib, "ws2_32")
//#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include <winsock2.h>
//#include <stdio.h>

//#include <iostream>
//using namespace std;

#include "stdafx.h"
#include <stdio.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define words 25
//include ability to access "backend"; the database.
//Included within is a vector length "axe", the website names; a vector of arrays "axe" by 25, the heatmaps of programming terms; and a spare vector of vectors "axe" by "why" for any additional search terms.
//whatever. This sends along the data to progDatabase once it recieves it from webCrawler.


void findAllOccurances(vector<size_t> & vec, string data, string toSearch)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);
	// Repeat till end is reached
	while (pos != std::string::npos)
	{
		// Add position to the vector
		vec.push_back(pos);
		// Get the next occurrence from the current position
		pos = data.find(toSearch, pos + toSearch.size());
	}
}

int main(int argc, char **argv)
{
	//In case I need to redo the port to switch, the initialization of data goes up here.
	string sitename;
	string websites[125];//storage!
	string website;//=whatever was just sent over from webCrawler
	string progwords[words] = { "program", "code", " C ", "C++" };// and more, and more, and more terms
	int wordsfound[words];
	string elsewords[25];
	int swords[25];
	int elses = 0;

	char str[3000];
	int something = 0;

	WSADATA wsaData;

	// Initialize Winsock version 2.2
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	printf("Winsock DLL status is %s.\n", wsaData.szSystemStatus);

	// Code to handle socket:
	SOCKET Socket;

	// Create a new socket to make a client or server connection.
	// AF_INET = 2, The Internet Protocol version 4 (IPv4) address family, TCP protocol
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		printf("Socket() failed!Error code : %ld\n", WSAGetLastError());
		// Do the clean up
		WSACleanup();
		// Exit with error
		return -1;
	}


	//address structure
	SOCKADDR_IN ServerAddr;
	unsigned int Port = 21000;

	// IPv4
	ServerAddr.sin_family = AF_INET;
	// Port no.
	ServerAddr.sin_port = htons(Port);
	// The IP address
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//hardcoded


														// Make a connection to the server with socket SendingSocket.
	int RetCode = connect(Socket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
	if (RetCode != 0)//this is where it fails...?
	{
		printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());
		// Close the socket
		closesocket(Socket);
		// Do the clean up
		WSACleanup();
		// Exit with error
		return -1;
	}

	char senderbuffer[1000];
	memset(senderbuffer, 0, 1000);
	const char* sendbuf = &senderbuffer[0];

	/*char name[22] = "Grossman-Lempert,Evan";//hardcoded
	strcpy(senderbuffer, "GET ");
	strcat(senderbuffer, name);
	strcat(senderbuffer, "\r\n");
	// Sends some data
	int BytesSent = send(Socket, sendbuf, strlen(sendbuf), 0);
	if (BytesSent == SOCKET_ERROR) { printf("Client: send() error %ld.\n", WSAGetLastError()); }*/


	char recvbuf[1000];
	memset(recvbuf, 0, 1000);
	//char* recvbuf = &recieverbuffer[0];
	int BytesReceived;

	/*int wololo = 1;
	while (wololo == 1) {*/

	////recieve data
	BytesReceived = recv(Socket, recvbuf, sizeof(recvbuf), 0);
	if (BytesReceived == SOCKET_ERROR) { printf("Client: recv() error %ld.\n", WSAGetLastError()); }


	///stop loop if end of message. maybe put it all into an array of characters and run through it to determine if it's actually the end?
	/*if(something){wololo=0;}
	}*/


	//disconnect
	closesocket(Socket);
	//WSACleanup();


	//GET IP  (it was what was recieved here)
	if (recvbuf[0] == 'O'&&recvbuf[1] == 'K') {
		//um...copy the address-structure thing and make a new socket?
		int yoy = 2, zoz = 2;
		while (yoy != 0) {
			if (recvbuf[zoz] == ' ') {
				yoy--;
			}
			zoz++;
		}

		bool xox = true;
		int mybrainisouttolunch = 0;
		char plop[25];
		while (xox == true) {
			plop[mybrainisouttolunch] = recvbuf[zoz];
			zoz++;
			if (recvbuf[zoz] == '\r' || recvbuf[zoz] == 0) {
				xox = false;
			}
			mybrainisouttolunch++;
		}
		plop[mybrainisouttolunch] = 0;

		Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (Socket == INVALID_SOCKET)
		{
			printf("Socket() failed!Error code : %ld\n", WSAGetLastError());
			// Do the clean up
			WSACleanup();
			// Exit with error
			return -1;
		}

		Port = 21001;
		// IPv4
		ServerAddr.sin_family = AF_INET;
		// Port no.
		ServerAddr.sin_port = htons(Port);
		// The IP address
		ServerAddr.sin_addr.s_addr = inet_addr(plop);



		RetCode = connect(Socket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
		if (RetCode != 0)
		{
			printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());
			// Close the socket
			closesocket(Socket);
			// Do the clean up
			WSACleanup();
			// Exit with error
			return -1;
		}
	
	

		bool forever = true;
		while (forever == true) {

			//Assuming I look at crawler...

			//recieve
			memset(recvbuf, 0, 1000);
			BytesReceived = recv(Socket, recvbuf, sizeof(recvbuf), 0);
			if (BytesReceived == SOCKET_ERROR) { printf("Client: recv() error %ld.\n", WSAGetLastError()); }

			if (recvbuf[0] == 'G' && recvbuf[1] == 'I' && recvbuf[2] == 'B') {//slang for "give"
				int length;
				if (isdigit(recvbuf[4])) {
					char *recvNext = recvbuf;
					char *recvCurr = recvbuf;

					recvCurr = recvbuf + 4;//point to link length
					length = atoi(recvCurr);//atoi takes as many integer characters as it can
					recvNext = strchr(recvCurr, ' ');//find the space after the link length

					recvCurr = recvNext + 1;//point to link
					sitename = string(recvCurr, length);
					recvNext = strchr(recvCurr, ' ');//find the space after the link

					recvCurr = recvNext + 1;//point to length of html data
					length = atoi(recvCurr);//atoi takes as many integer characters as it can
					recvNext = strchr(recvCurr, ' ');//find the space after the length of html data

					recvCurr = recvNext + 1;//point to html data
					website = string(recvCurr, length);


					int yote = 0;
					for (int axe = 0; axe < 4/*words*/; axe++) {
						vector<size_t> total;
						findAllOccurances(total, website, progwords[axe]);
						wordsfound[axe] = total.size();
						if (total.size() > 0) { yote = 1; }
					}
					if (yote == 1) {
						websites[something] = website;
						something++;
						for (int axe = 0; axe < elses; axe++) {
							vector<size_t> total;
							findAllOccurances(total, website, elsewords[axe]);
							wordsfound[axe] = total.size();
						}

						/*//~~something something (sitename, wordsfound)~~
						//~~char str[3000];~~
						strcpy(str, sitename.c_str());
						for (int why = 0; why<4//words//; why++) {
							strcat(str, " ");
							int lenny = 1;
							while (10 ^ lenny > wordsfound[why]) { lenny++; }
						if (lenny = 1) {
							char number[1] = ("" + wordsfound[why]).toCharArray();
								strcat(str, number);
						}
						else if (lenny = 2) {
							char number[2] = ("" + wordsfound[why]).toCharArray();
								strcat(str, number);
						}
						else if (lenny = 3) {
							char number[3] = ("" + wordsfound[why]).toCharArray();
							strcat(str, number);
						}
						else if (lenny = 4) {
							char number[4] = ("" + wordsfound[why]).toCharArray();
							strcat(str, number);
						}
						else {
							//I doubt that.
						}
					}
					//send along str via whatever method; i.e. surround this whole thing with socket code.*/




					}
				}
			}


		



			//Assuming I now look at database...actually, this was what happens next anyways, either way. Bully!
			//...unless I need to go back through it all to connect to a new port, looping and switching back and forth between opening new ports and new connections...which I'd hate.

			//send it
			memset(senderbuffer, 0, 1000);
			strcpy(senderbuffer, "SET ");
			strcat(senderbuffer, str);
			strcat(senderbuffer, "\r\n");

			//recieve
			memset(recvbuf, 0, 1000);
			BytesReceived = recv(Socket, recvbuf, sizeof(recvbuf), 0);
			if (BytesReceived == SOCKET_ERROR) { printf("Client: recv() error %ld.\n", WSAGetLastError()); }

			//if it's OK, that's good
			if (recvbuf[0] == 'O'&&recvbuf[1] == 'K') {//all good
			}
			//if it's NOK...ho ho ho no, this is where the "fun" begins.
			if (recvbuf[0] == 'N'&&recvbuf[1] == 'O'&&recvbuf[2] == 'K') {
				string newbie = recvbuf + 4;
				elsewords[elses] = newbie;
				elses++;

				memset(senderbuffer, 0, 1000);//I guess I need to
				strcpy(senderbuffer, "YES");
								

				for (int bonanza = 0; bonanza < something; bonanza++) {
					strcat(senderbuffer, " ");
					website = websites[bonanza];//I *think* I use an ampersand to dereference, here...?

					vector<size_t> total;
					findAllOccurances(total, website, newbie);
					int oy = total.size();

					int lenny = 1;//I cannot think of a better way to do this bit...
					while (10 ^ lenny > oy) { lenny++; }
					if (lenny = 1) {
						char number[1] = ("" + oy).toCharArray();
						strcat(senderbuffer, number);
					}
					else if (lenny = 2) {
						char number[2] = ("" + oy).toCharArray();
						strcat(senderbuffer, number);
					}
					else if (lenny = 3) {
						char number[3] = ("" + oy).toCharArray();
						strcat(senderbuffer, number);
					}
					else if (lenny = 4) {
						char number[4] = ("" + oy).toCharArray();//I doubt that.
						strcat(senderbuffer, number);
					}
					else {
						//I HIGHLY doubt that.
					}
				}
				strcat(senderbuffer, "\r\n");

				int BytesSent = send(Socket, sendbuf, strlen(sendbuf), 0);
				if (BytesSent == SOCKET_ERROR) { printf("Client: send() error %ld.\n", WSAGetLastError()); }
			}
			//maybe, for OK and NOK, make it a loop that only gives out once OK and loops if NOK...actually, no, the database is expecting another link anyways.





		}
		//is forever over yet
	}














	/*for (int axe = 0; axe<4//words//; axe++) {
		vector<size_t> total;
		findAllOccurances(total, website, progwords[axe]);
		wordsfound[axe] = total.size();
	}


	
	//call whatever the database is and give them the website, and the words
	//~~honestly think I might need curl for this one too~~ nope, I just need to recieve the whole text from webCrawler and comb through that. I don't need curl for this segment at all!

	//~~something something (sitename, wordsfound)~~
	char str[3000];
	strcpy(str, sitename.c_str());
	for (int why = 0; why<4//words//; why++) {
		strcat(str, " ");
		int lenny = 1;
		while (10 ^ lenny > wordsfound[why]) { lenny++; }
		if (lenny = 1){
			char number[1] = ("" + wordsfound[why]).toCharArray();
			strcat(str, number);
		}
		else if (lenny = 2) {
			char number[2] = ("" + wordsfound[why]).toCharArray();
			strcat(str, number);
		}
		else if (lenny = 3) {
			char number[3] = ("" + wordsfound[why]).toCharArray();
			strcat(str, number);
		}
		else if (lenny = 4) {
			char number[4] = ("" + wordsfound[why]).toCharArray();
			strcat(str, number);
		}
		else{
			//I doubt that.
		}
	}
	//send along str via whatever method; i.e. surround this whole thing with socket code.*/

	/*//ask user for number
		char wai[3];
		cout << "1 to 20" << endl;
		cin >> wai;


		//send
		memset(senderbuffer, 0, 1000);
		strcpy(senderbuffer, "GET ");
		strcat(senderbuffer, wai);
		strcat(senderbuffer, "\r\n");


		int BytesSent = send(Socket, sendbuf, strlen(sendbuf), 0);
		if (BytesSent == SOCKET_ERROR) { printf("Client: send() error %ld.\n", WSAGetLastError()); }

		//recieve
		memset(recvbuf, 0, 1000);
		BytesReceived = recv(Socket, recvbuf, sizeof(recvbuf), 0);
		if (BytesReceived == SOCKET_ERROR) { printf("Client: recv() error %ld.\n", WSAGetLastError()); }

		//print
		if (recvbuf[0] == 'O'&&recvbuf[1] == 'K') {
			//The client will print out the name, IP address of the quote server, the number requested and the quote for each quote requested.
			cout << name << " " << plop << " " << recvbuf + 3;}*/












	////shutdown connection when done
	// Shutdown sending of data
	if (shutdown(Socket, SD_SEND) != 0)
	{
		printf("Client: Well, there is something wrong with the shutdown(). The error code: %ld\n", WSAGetLastError());
	}
	else
	{
		printf("Client: shutdown() looks OK...\n\n");
	}

	////close socket
	if (closesocket(Socket) != 0)
	{
		printf("Server: Cannot close socket. Error code: %ld\n", WSAGetLastError());
	}
	else
	{
		printf("Server: Closing socket...\n");
	}

	////call cleanup when no more sockets remain
	if (WSACleanup() != 0)
	{
		printf("Client: WSACleanup() failed!...\n");
	}





	// Cleanup socket
	WSACleanup();
}

