OBJECTS = source/usync.o
OUTPUT = libusync.a

all: $(OUTPUT)
%.o: %.c
	$(CC) -Wall -Os -g0 -pedantic -I./include -c -o $@ $<
$(OUTPUT): $(OBJECTS)
	$(AR) rcs "$(OUTPUT)" $(OBJECTS)
clean:
	rm -f "$(OUTPUT)" $(OBJECTS)
install-wii:
	cp $(BUILD)/$(BIN) $(DEVKITPRO)/libogc/lib/wii
	cp include/usync.h $(DEVKITPRO)/libogc/include
