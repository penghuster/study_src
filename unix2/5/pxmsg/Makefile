BIN=msgcreate mqgetattr mqsend mqnotifysig3

all: $(BIN)

msgcreate : msgcreate.c 
	gcc msgcreate.c -lrt -o msgcreate

mqgetattr : mqgetattr.c
	gcc mqgetattr.c -lrt -o mqgetattr

mqsend : mqsend.c
	gcc mqsend.c -lrt -o mqsend

mqnotifysig3 : mqnotifysig3.c
	gcc mqnotifysig3.c -lrt -o mqnotifysig3




clean:
	rm -rf $(BIN)
