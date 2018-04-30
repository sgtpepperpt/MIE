#make run build accept arguments
ifeq (run,$(firstword $(MAKECMDGOALS)))
RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
$(eval $(RUN_ARGS):;@:)
endif

DEBUG_FLAGS := -g -O0

C_FLAGS := -I/usr/local/include `pkg-config --cflags --libs opencv` -Wno-unused-command-line-argument -pthread $(DEBUG_FLAGS)
CPP_FLAGS := $(C_FLAGS) -std=c++11

Server : Main.o MIEServer.o MIEServerMT.o SSEServer.o ServerUtil.o CashServer.o PaillierCashServer.o paillier.o
	g++ -o Server Main.o MIEServer.o MIEServerMT.o SSEServer.o ServerUtil.o CashServer.o PaillierCashServer.o paillier.o $(CPP_FLAGS) -lcrypto -lz -lgmp -ldl

Main.o : Main.cpp
	g++ $(CPP_FLAGS) -c Main.cpp

MIEServer.o : MIEServer.cpp
	g++ $(CPP_FLAGS) -c MIEServer.cpp

MIEServerMT.o : MIEServerMT.cpp
	g++ $(CPP_FLAGS) -c MIEServerMT.cpp

SSEServer.o : SSEServer.cpp
	g++ $(CPP_FLAGS) -c SSEServer.cpp

ServerUtil.o : ServerUtil.cpp
	g++ $(CPP_FLAGS) -c ServerUtil.cpp

CashServer.o : CashServer.cpp
	g++ $(CPP_FLAGS) -c CashServer.cpp

PaillierCashServer.o : PaillierCashServer.cpp
	g++ $(CPP_FLAGS) -c PaillierCashServer.cpp

paillier.o : paillier.c
	gcc $(C_FLAGS) -c paillier.c

clean :
	rm -f Server Main.o MIEServer.o MIEServerMT.o SSEServer.o ServerUtil.o CashServer.o PaillierCashServer.o paillier.o

run : Server
	LD_LIBRARY_PATH=/usr/local/opencv/opencv3.1/lib/ DYLD_LIBRARY_PATH=/usr/local/opencv/opencv3.1/lib/ ./Server $(RUN_ARGS) >teste.txt 2>&1 &

.PHONY: run clean
