TARGET = out/wavver
# CC = x86_64-w64-mingw32-gcc
CC = gcc
MAKE = make
CFLAGS = -Wall -Iinc -flto -lm
CHMOD = chmod

PREBUILD_DIRS = out/ out/src

.PHONY: default all run clean

default: $(TARGET)
all: default run

HEADERS = $(wildcard *.h)
HEADERS += $(wildcard inc/*.h)

SRC_C =  $(wildcard *.c)
SRC_C += $(wildcard src/*.c)

OBJECTS = $(addprefix out/, $(SRC_C:.c=.o))

$(PREBUILD_DIRS):
	mkdir -p $@

out/%.o: %.c $(HEADERS) | $(PREBUILD_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(CFLAGS) -o $@
	$(CHMOD) -f +x $@ || true
	$(CHMOD) -f +x $@.exe || true

run: $(TARGET)
	$(TARGET)

clean:
	-rm -f out/*.o
	-rm -f out/src/*.o
	-rm -f $(TARGET)
	-rm -f $(TARGET).exe
