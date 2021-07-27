#include "types.h"

void printf(char * str) {
	uint16_t* videoMemory = (uint16_t*)0xb8000;
	for (int i = 0; str[i] != '\0'; i++) {
		videoMemory[i] = (videoMemory[i] & 0xFF00)| str[i];
	}
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("Hello World");
    while(1);
}
