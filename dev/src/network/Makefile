CXXFLAGS = $(DEBUG) -c -I../sdk/threads -I../logging -I../protocol -I../protocol/pdu -I../protocol/dataType

all: hostaddress.o socket.o tcpserver.o server.o

hostaddress.o: hostaddress.h hostaddress.cpp 

socket.o: socket.h socket.cpp

tcpserver.o: tcpserver.h tcpserver.cpp

server.o: server.h server.cpp

clean:
	@-rm -f *.o
