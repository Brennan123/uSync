OBJECTS = source/usync.o
OUTPUT = libusync.a

all: $(OUTPUT)
%.o: %.c
	$(CC) -Wall -Os -g0 -pedantic -I./include -c -o $@ $<
$(OUTPUT): $(OBJECTS)
	$(AR) rcs "$(OUTPUT)" $(OBJECTS)

export LIBUSYNC_MAJOR	:= 0
export LIBUSYNC_MINOR	:= 2

include/usyncversion.h:
	@echo "#ifndef USYNCVERSION_H_" > $@
	@echo "#define USYNCVERSION_H_" >> $@
	@echo >> $@
	@echo "#define USYNC_VERSION_MAJOR	$(LIBUSYNC_MAJOR)" >> $@
	@echo "#define USYNC_VERSION_MINOR	$(LIBUSYNC_MINOR)" >> $@
	@echo >> $@
	@echo '#define USYNC_VERSION_STRING	"µSync '$(LIBUSYNC_MAJOR).$(LIBUSYNC_MINOR)'"' >> $@
	@echo >> $@
	@echo "#endif /* USYNCVERSION_H_ */" >> $@

clean:
	rm -f "$(OUTPUT)" $(OBJECTS)
install-ppc: include/usyncversion.h
	cp $(OUTPUT) $(DEVKITPRO)/libogc/lib/wii
	cp include/usync.h $(DEVKITPRO)/libogc/include
	cp include/usyncversion.h $(DEVKITPRO)/libogc/include
install-ds: include/usyncversion.h
	cp $(OUTPUT) $(DEVKITPRO)/libnds/lib
	cp include/usync.h $(DEVKITPRO)/libnds/include
	cp include/usyncversion.h $(DEVKITPRO)/libnds/include
