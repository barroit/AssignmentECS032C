SOURCE=bintree
TARGET=btdemo

all: $(TARGET)

$(TARGET): $(TARGET).o $(SOURCE).o
	@gcc $^ -o $@

$(SOURCE).o: $(SOURCE).c
	@gcc -c -Wall -Werror $^ -o $@

$(TARGET).o: $(TARGET).c
	@gcc -c -Wall -Werror $< -o $@

clean:
	rm -rvf *.o $(TARGET)