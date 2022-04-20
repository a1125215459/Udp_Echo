all:Udp_Server Udp_Client

Udp_Server:Udp_Server.cpp UdpSocket.h
	g++ $^ -o $@
Udp_Client:Udp_Client.cpp UdpSocket.h
	g++ $^ -o $@
.PHONY:clean
clean:
	-rm Udp_Server Udp_Client
