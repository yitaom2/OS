GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
OBJECTS = loader.o kernel.o
LDPARAMS = -melf_i386

all: mykernel.bin clean

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(OBJECTS)
	ld $(LDPARAMS) -T $< -o $@ $(OBJECTS)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin
	
clean:
	rm *.o
