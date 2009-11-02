OBJECTS = source/usync.o
OUTPUT = libusync.a

all: $(OUTPUT)
%.o: %.c
	$(CC) -Wall -Os -g0 -pedantic -I./include -c -o $@ $<
$(OUTPUT): $(OBJECTS)
	$(AR) rcs "$(OUTPUT)" $(OBJECTS)
clean:
	rm -f "$(OUTPUT)" $(OBJECTS)
install-ppc:
	cp $(OUTPUT) $(DEVKITPRO)/libogc/lib/wii
	cp include/usync.h $(DEVKITPRO)/libogc/include
install-ds:
	cp $(OUTPUT) $(DEVKITPRO)/libnds/lib
	cp include/usync.h $(DEVKITPRO)/libnds/include
