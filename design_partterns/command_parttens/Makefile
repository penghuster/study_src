CC=gcc
CXX=g++

BIN=controler

SRCS=./src/client.cpp ./src/simple_rctrl.cpp ./src/light.cpp ./src/light_on_command.o
INC=-I./inc 

FLAG= -c -std=c++11 -g
LINKFLAG= -std=c++11

LIBS=
LIBSDIR=-L./

OBJS=$(SRCS:%.cpp=%.o)

$(warning $(OBJS))


all:$(BIN)


$(BIN):$(OBJS)
	$(CXX) $(LINKFLAG) $(LIBSDIR) $(LIBS) $(OBJS)  -o $@

%.o:%.cpp
	$(CXX) $(FLAG) $(INC)  $< -o $@


clean:
	rm -rf $(BIN) $(OBJS)
