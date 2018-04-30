#make run build accept arguments
ifeq (run,$(firstword $(MAKECMDGOALS)))
RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
$(eval $(RUN_ARGS):;@:)
endif

Server : Main.o MIEServer.o MIEServerMT.o SSEServer.o ServerUtil.o CashServer.o PaillierCashServer.o paillier.o
	g++ -Wno-unused-command-line-argument -o Server Main.o MIEServer.o MIEServerMT.o SSEServer.o ServerUtil.o CashServer.o PaillierCashServer.o paillier.o `pkg-config --cflags --libs opencv` -lcrypto -lz -lgmp -ldl -pthread

debug : Main.debug MIEServer.debug MIEServerMT.debug SSEServer.debug ServerUtil.debug CashServer.debug PaillierCashServer.debug paillier.debug
	g++ -Wno-unused-command-line-argument -o Server Main.o MIEServer.o MIEServerMT.o SSEServer.o ServerUtil.o CashServer.o PaillierCashServer.o paillier.o `pkg-config --cflags --libs opencv` -lcrypto -lz -lgmp -ldl -pthread

Main.o : Main.cpp
	g++ -Wno-unused-command-line-argument -std=c++11 `pkg-config --cflags --libs opencv` -pthread -c Main.cpp

MIEServer.o : MIEServer.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -c MIEServer.cpp

MIEServerMT.o : MIEServerMT.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -c MIEServerMT.cpp

SSEServer.o : SSEServer.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -c SSEServer.cpp

ServerUtil.o : ServerUtil.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -c ServerUtil.cpp

CashServer.o : CashServer.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -c CashServer.cpp

PaillierCashServer.o : PaillierCashServer.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -c PaillierCashServer.cpp

paillier.o : paillier.c
	gcc -I/usr/local/include -pthread -c paillier.c

Main.debug : Main.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -g -O0 -c Main.cpp

MIEServer.debug : MIEServer.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -g -O0 -c MIEServer.cpp

MIEServerMT.debug : MIEServerMT.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -g -O0 -c MIEServerMT.cpp

SSEServer.debug : SSEServer.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -g -O0 -c SSEServer.cpp

ServerUtil.debug : ServerUtil.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -g -O0 -c ServerUtil.cpp

CashServer.debug : CashServer.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -g -O0 -c CashServer.cpp

PaillierCashServer.debug : PaillierCashServer.cpp
	g++ -std=c++11 `pkg-config --cflags --libs opencv` -pthread -g -O0 -c PaillierCashServer.cpp

paillier.debug : paillier.c
	gcc -pthread -g -O0 -c paillier.c

clean :
	rm Server Main.o MIEServer.o MIEServerMT.o SSEServer.o ServerUtil.o CashServer.o PaillierCashServer.o paillier.o core

run : Server
	LD_LIBRARY_PATH=/usr/local/opencv/opencv3.1/lib/ DYLD_LIBRARY_PATH=/usr/local/opencv/opencv3.1/lib/ ./Server $(RUN_ARGS) >teste.txt 2>&1 &

.PHONY: run clean
