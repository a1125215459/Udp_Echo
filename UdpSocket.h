//UdpSocket.h
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

class UdpSocket
{
    public:
        //构造函数默认赋值-1
        UdpSocket():_sockfd(-1)
        {}
        //根据指定协议创建套接字
        bool Socket()
        {
            //IP protocal family 2 数据报套接字(SOCK_DGRAM) UDP
            _sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
            if(_sockfd < 0)
            {
                cout << "sockfd error" << endl ;
                return false;
            }
            cout << "_sockfd: " << _sockfd << endl ;
            return true;
        }
        //描述Internet套接字地址的结构，给套接字绑定指定的IP/Port
        bool Bind(const string &ip,uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = port;
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            socklen_t len = sizeof(struct sockaddr_in);
            //给套接字FD本地地址ADDR(长度为LEN字节)。
            int ret = bind(_sockfd,(struct sockaddr*)&addr,len);
            if(ret < 0)
            {
                cout << "bind error" << endl ;
                return false;
            }
            cout << "ret: " << ret << endl ;
            return true;
        }
        //用于接收对方发送的数据，若参数IP/Port不为空则将发送方的数据填入描述Internet套接字地址的结构，可用于接收方根据该信息向发送方发送数据
        bool Recv(string *buf,string *ip = NULL,uint16_t *port = NULL)
        {   
            //用来接收对方的IP信息
            struct sockaddr_in peer_addr;
            socklen_t len = sizeof(struct sockaddr_in);
            char tmp[4096] = {0};
            //通过_sockfd读取4096个字节到tmp。如果peer_addr不为NULL，则将其字节与发送方地址填入，并将实际地址大小存储在len中。返回读取的字节数或-1错误。
            int ret = recvfrom(_sockfd,tmp,4096,0,(struct sockaddr*)&peer_addr,&len);
            if(ret < 0)
            {
                cout << "recvfrom error" << endl ;
                return false;
            }
            buf->assign(tmp,ret);
            if(ip != NULL)
            {
                *ip = inet_ntoa(peer_addr.sin_addr);
            }
            if(port != NULL)
            {
                *port = peer_addr.sin_port;
            }
            return true;
        }
        //根据缓冲区数据和传入的IP/Port参数向指定目的地发送数据
        bool Send(const string &data,string &ip,const uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = port;
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            socklen_t len = sizeof(struct sockaddr_in);
            //在_sockfd上发送data.size()个字节的data.c_str()到peer地址addr (addr长度为len字节)。返回发送的数字，或-1错误
            int ret = sendto(_sockfd,data.c_str(),data.size(),0,(struct sockaddr*)&addr,len);
            if(ret < 0)
            {
                cout << "sendto error" << endl ;
                return false;
            }
            return true;
        }
        //关闭套接字
        bool Close()
        {
            if(_sockfd > 0)
            {
                close(_sockfd);
                _sockfd = -1;
            }
            return true;
        }


    private:
        int _sockfd;
};