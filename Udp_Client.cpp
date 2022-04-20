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
        string peer_ip;
        uint16_t peer_port;
        CHECK_RET(Cli_Sock.Recv(&buf,&peer_ip,&peer_port));
        //cout << "&peer_ip: " << peer_ip << endl;
        //cout << "&peer_port: " << peer_port << endl;
        cout << "Server say: " << buf << endl;
    }
    Cli_Sock.Close();
    return 0;
}