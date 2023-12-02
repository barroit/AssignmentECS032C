TARGET=selsort

all: $(TARGET)

$(TARGET): $(TARGET).o
	gcc $< -o $@

$(TARGET).o: $(TARGET).c
	gcc -c -Wall -Werror $< -o $@

clean:
	rm -rvf *.o $(TARGET)
