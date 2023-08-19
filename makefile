CC=clang
CFILES=test.c json.c list.c dynamic_string.c json_lexer.c
OFILES=test.o json.o list.o dynamic_string.o json_lexer.o

build: $(OFILES)
	$(CC) $(OFILES)
	
$(OFILES): $(CFILES)
	$(CC) -c $(CFILES)

compile_commands.json: test.c
	clang -MJ compile_commands.json test.c