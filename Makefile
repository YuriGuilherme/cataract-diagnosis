include config.mk

SRC = src/main.c
OBJ = $(SRC:.c=.o)

all: catdig

catdig: $(OBJ)
	$(CC) -o bin/$@ $(OBJ)

$(ID): $(ID).c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	@rm -rf bin/* $(OBJ) src/*~

install: all
	@install -D bin/catdig /bin/

uninstall:
	@rm -f /bin/catdig

.PHONY: all catdig clean install uninstall
