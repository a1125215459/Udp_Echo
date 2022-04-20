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
        string peer_ip;
        uint16_t peer_port;
        // cout << "buf: " << buf << endl;
		// cout << "&peer_ip: " << &peer_ip << endl << "peer_ip: " << peer_ip << endl;
		// cout << "&peer_port" << &peer_port << endl << "peer_port: " << peer_port << endl;
        //把buf对应的发送方的IP和Port填入
        CHECK_RET(Srv_Sock.Recv(&buf,&peer_ip,&peer_port));
        // cout << "&peer_ip: " << &peer_ip << endl << "peer_ip: " << peer_ip << endl;
		// cout << "&peer_port" << &peer_port << endl << "peer_port: " << peer_port << endl;
        cout << "client[" << peer_ip << ":" << peer_port << "]say:" << buf << endl ;
        //Send data
        buf.clear();
        cout << "server say: " ;
        cin >> buf;
        CHECK_RET(Srv_Sock.Send(buf,peer_ip,peer_port));
    }
    Srv_Sock.Close();
    return 0;
}