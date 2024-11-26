# Variáveis para o compilador e as opções de compilação
CC = gcc
CFLAGS = -Wall -Iinclude

# Nome do arquivo executável
EXECUTABLE = tp3.out

# Lista dos arquivos de código-fonte
SOURCES = src/main.c src/OrdInd.c
# Lista dos arquivos objeto correspondentes
OBJECTS = $(SOURCES:.c=.o)

# A primeira regra é a que será executada quando não se especifica uma regra
all: $(EXECUTABLE)

# Como construir o executável final
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

# Como construir cada arquivo objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
