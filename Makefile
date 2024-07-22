TARGET = bin/dbcli
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
	./$(TARGET) -n -f mynewdb.db
	./$(TARGET) -f mynewdb.db -a "Tom Bombadil, Valley of Withywindle, -1"
	./$(TARGET) -f mynewdb.db -l


default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -f *.db

$(TARGET): $(OBJ)
	gcc -o $@ $?

obj/%.o : src/%.c
	gcc -c $< -o $@ -Iinclude



