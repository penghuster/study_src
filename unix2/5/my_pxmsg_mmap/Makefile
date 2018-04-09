all: libmymq.so

BIN=libmymq.so
OBJS= mq_close.o mq_getattr.o  mq_notify.o mq_open.o mq_receive.o  mq_send.o  mq_setattr.o  mq_unlink.o 

CC=gcc
RM=rm -rf

INC= -I./ 
CFLAGS= -c -g 
LFLAGS= -shared 

$(BIN):$(OBJS)
	$(CC) $(LFLAGS) -o $@  $^

%.o : %.c
	$(CC) $(CFLAGS) $(INC)  $< -o $@


clean:
	$(RM) $(BIN) $(OBJS)
