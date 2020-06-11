CC := gcc
CFLAGS:= -std=gnu99 -O3 
DEBUG:=0
ifeq ($(DEBUG), 1)
    CFLAGS= -std=gnu99 -g -Wall  -Werror -DDEBUG
endif
LDFLAGS := -lpthread
EXEC := horses
OBJ := $(EXEC).o  error.o vt100.o horses_module.o

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

#$(EXEC).o: $(EXEC).c
#	$(CC) -o $(EXEC).o -c $(EXEC).c $(CFLAGS)

clean:
	rm $(OBJ) $(EXEC)

test:
	make clean; make; ./horses Veillantif Tencendur Passecerf Tachebrun

test2:
	make clean; make; ./horses Cocotte Chocolat Papillon Tank Ermes Pegase Louis Epona







