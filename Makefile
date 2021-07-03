GPPPARAMS = -m32
ASPARAMS = --32
OBJECTS = loader.o kernel.o
LDPARAMS = -melf_i386

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(OBJECTS)
	ld $(LDPARAMS) -T $< -o $@ $(OBJECTS)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin