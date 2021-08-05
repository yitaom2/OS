#include "types.h"
#include "gdt.h"
#include "interrupts.h"

void printf(char * str) {
	uint16_t* videoMemory = (uint16_t*)0xb8000;

    static uint8_t row = 0; static uint8_t col = 0;
    
	for (int i = 0; str[i] != '\0'; i++) {
        switch(str[i]) {
            case '\n':
                row++;
                col = 0;
                break;
            default:
                videoMemory[80*row+col] = (videoMemory[80*row+col] & 0xFF00)| str[i];
                col++;
                break;
        }

        if (col == 80) {
            row++;
            col = 0;
        }

        if (row == 25) {
            for (int j = 0; j < 80*25; j++) {
                videoMemory[j] = (videoMemory[j] & 0xFF00) | ' ';
            }
            row = 0;
            col = 0;
        }
	}
}


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();    
    }
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("Hello World\n");
    printf("Hello World\n");
    GlobalDescriptorTable gdt;

    InterruptManager interrupts(&gdt);

//    interrupts.Activate();
    while(1);
}
