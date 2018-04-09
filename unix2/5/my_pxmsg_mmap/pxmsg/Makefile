BIN=msgcreate mqgetattr mqsend mqnotifysig3 mqreceive

all: $(BIN)

msgcreate : msgcreate.c 
	gcc -I../ msgcreate.c -L../ -lmymq -g -lpthread -o msgcreate

mqgetattr : mqgetattr.c
	gcc -I../  mqgetattr.c -L../ -lmymq -g -lpthread -o mqgetattr

mqsend : mqsend.c
	gcc -I../ mqsend.c -L../ -lmymq -g -lpthread -o mqsend

mqnotifysig3 : mqnotifysig3.c
	gcc -I../ mqnotifysig3.c -L../ -lmymq -g -lpthread -o mqnotifysig3

mqreceive : mqreceive.c
	gcc -I../ mqreceive.c -L../ -lmymq -g -lpthread -o mqreceive
	




clean:
	rm -rf $(BIN)
