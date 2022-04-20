//Udp_Server.cpp
#include <iostream>
#include <string>
#include "UdpSocket.h"
using namespace std;

#define CHECK_RET(q) if((q)==false){return false;}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        cout << "Input ./Udp_Server IP Port" << endl ;
        return -1;
    }
    string ip = argv[1];
    uint16_t port = stoi(argv[2]);
    UdpSocket Srv_Sock;
    CHECK_RET(Srv_Sock.Socket());
    cout << "Socket Succ" << endl ;
    CHECK_RET(Srv_Sock.Bind(ip,port));
    cout << "Bind Succ" << endl ;
    while(1)
    {
        //Recive data
        string buf;
        string Peer_ip;
        uint16_t Peer_port;
        // cout << "buf: " << buf << endl;
		// cout << "&Peer_ip: " << &Peer_ip << endl << "Peer_ip: " << Peer_ip << endl;
		// cout << "&Peer_port" << &Peer_port << endl << "Peer_port: " << Peer_port << endl;
        //把buf对应的发送方的IP和Port填入
        CHECK_RET(Srv_Sock.Recv(&buf,&Peer_ip,&Peer_port));
        // cout << "&Peer_ip: " << &Peer_ip << endl << "Peer_ip: " << Peer_ip << endl;
		// cout << "&Peer_port" << &Peer_port << endl << "Peer_port: " << Peer_port << endl;
        cout << "client[" << Peer_ip << ":" << Peer_port << "]say:" << buf << endl ;
        //Send data
        buf.clear();
        cout << "server say: " ;
        cin >> buf;
        CHECK_RET(Srv_Sock.Send(buf,Peer_ip,Peer_port));
    }
    Srv_Sock.Close();
    return 0;
}