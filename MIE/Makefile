#make run build accept arguments
ifeq (run,$(firstword $(MAKECMDGOALS)))
RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
$(eval $(RUN_ARGS):;@:)
endif

DEBUG_FLAGS := -g -O0

C_FLAGS := -I/usr/local/include -L/usr/local/lib `pkg-config --cflags --libs opencv` -Wno-unused-command-line-argument -pthread $(DEBUG_FLAGS)
CPP_FLAGS := $(C_FLAGS) -std=c++11

Client : Main.o CashClient.o PaillierCashClient.o CashCrypt.o EnglishAnalyzer.o MIEClient.o SBE.o SSEClient.o SSECrypt.o TextCrypt.o Util.o paillier.o
	g++ -o Client Main.o CashClient.o CashCrypt.o PaillierCashClient.o EnglishAnalyzer.o MIEClient.o SBE.o SSEClient.o SSECrypt.o TextCrypt.o Util.o paillier.o $(CPP_FLAGS) -lz -lcrypto -lgmp -ldl

Main.o : Main.cpp
	g++ $(CPP_FLAGS) -c Main.cpp

CashClient.o : CashClient.cpp
	g++ $(CPP_FLAGS) -c CashClient.cpp

PaillierCashClient.o : PaillierCashClient.cpp
	g++ $(CPP_FLAGS) -c PaillierCashClient.cpp

CashCrypt.o : CashCrypt.cpp
	g++ $(CPP_FLAGS) -c CashCrypt.cpp

EnglishAnalyzer.o : EnglishAnalyzer.cpp
	g++ $(CPP_FLAGS) -c EnglishAnalyzer.cpp

MIEClient.o : MIEClient.cpp
	g++ $(CPP_FLAGS) -c MIEClient.cpp

SBE.o : SBE.cpp
	g++ $(CPP_FLAGS) -c SBE.cpp

SSEClient.o : SSEClient.cpp
	g++ $(CPP_FLAGS) -c SSEClient.cpp

SSECrypt.o : SSECrypt.cpp
	g++ $(CPP_FLAGS) -c SSECrypt.cpp

TextCrypt.o : TextCrypt.cpp
	g++ $(CPP_FLAGS) -c TextCrypt.cpp

Util.o : Util.cpp
	g++ $(CPP_FLAGS) -c Util.cpp

paillier.o : paillier.c
	gcc $(C_FLAGS) -c paillier.c

clean :
	rm -f Client Main.o CashClient.o CashCrypt.o PaillierCashClient.o EnglishAnalyzer.o MIEClient.o SBE.o SSEClient.o SSECrypt.o TextCrypt.o Util.o paillier.o

run : Client
	LD_LIBRARY_PATH=/usr/local/opencv/opencv2/lib/ DYLD_LIBRARY_PATH=/usr/local/opencv/opencv2/lib/ ./Client $(RUN_ARGS) >teste.txt 2>&1 &

.PHONY: run clean
