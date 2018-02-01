INCLUDES=  
  
LIBLINKS=  

FLAGS = -std=c++11

SOURCES=./src/camera/camera.cpp \
		./src/event/events.cpp                          \
		./src/state/notshooting/idle.cpp              \
	    ./src/state/notshooting/notshooting.cpp       \
		./src/state/notshooting/configuring.cpp      \
	    ./src/state/shooting/shooting.cpp             \
		./src/state/shooting/focusing.cpp             \
		./src/state/shooting/focused.cpp              \
	    ./src/state/shooting/storing.cpp              

OBJS = $(subst cpp,o,$(SOURCES))

$(warning $(OBJS))
									  
EXE=bin/run  
										    
											  
all: clean build  
	  
build:$(EXE)  
	mkdir -p bin

$(EXE):$(OBJS)
	g++ -g -std=c++11 $(OBJS) -o $(EXE) $(INCLUDES)  $(LIBLINKS)  


%.o:%.cpp
	g++ -c $< -o $@


					  
clean:  
	rm -f $(EXE) 
	rm -f $(OBJS)
			  
test:  
	./$(EXE)  
