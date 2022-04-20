//Udp_Client.cpp
#include <iostream>
#include <string>
#include "UdpSocket.h"
using namespace std;

#define CHECK_RET(q) if((q) == false){return -1;}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        cout << "./Udp_Client IP Port" << endl ;
        return -1;
    }
    string ip = argv[1];
    uint16_t port = stoi(argv[2]);

    UdpSocket Cli_Sock;
    CHECK_RET(Cli_Sock.Socket());
    while (1)
    {
        //send data
        cout << "Client say: ";
        string buf;
        cin >> buf;
        CHECK_RET(Cli_Sock.Send(buf,ip,port));
        //recive data
        buf.clear();
        string Peer_ip;
        uint16_t Peer_port;
        CHECK_RET(Cli_Sock.Recv(&buf,&Peer_ip,&Peer_port));
        //cout << "&Peer_ip: " << Peer_ip << endl;
        //cout << "&Peer_port: " << Peer_port << endl;
        cout << "Server say: " << buf << endl;
    }
    Cli_Sock.Close();
    return 0;
}