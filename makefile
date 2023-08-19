CC=clang
CFILES=test.c json.c list.c dynamic_string.c
OFILES=test.o json.o list.o dynamic_string.o

build: $(OFILES)
	$(CC) $(OFILES)
	
$(OFILES): $(CFILES)
	$(CC) -c $(CFILES)