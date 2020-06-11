CC := gcc
CFLAGS:= -std=gnu99 -O3 
DEBUG:=0
ifeq ($(DEBUG), 1)
    CFLAGS= -std=gnu99 -g -Wall  -Werror -DDEBUG
endif
LDFLAGS=
EXEC := myreadelf
OBJ := $(EXEC).o myreadelf_module.o error.o

all: $(EXEC) hello_world.o

hello_world.o: hello_world.c
	$(CC) hello_world.c -o hello_world.o $(LDFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

#$(EXEC).o: $(EXEC).c
#	$(CC) -o $(EXEC).o -c $(EXEC).c $(CFLAGS)

clean:
	rm *.o $(EXEC)






