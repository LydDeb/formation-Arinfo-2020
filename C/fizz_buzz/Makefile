CC := gcc
CFLAGS:= -std=gnu99 -O3 
DEBUG:=0
ifeq ($(DEBUG), 1)
    CFLAGS= -std=gnu99 -g -Wall  -Werror -DDEBUG
endif
LDFLAGS := 
EXEC := fizz_buzz
OBJ := $(EXEC).o

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

#$(EXEC).o: $(EXEC).c
#	$(CC) -o $(EXEC).o -c $(EXEC).c $(CFLAGS)

clean:
	rm $(OBJ) $(EXEC)

test:
	make clean; make DEBUG=1; ./$(EXEC)








