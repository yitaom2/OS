#include "../drivers/ports.h"
#include "../cpu/isr.h"

void main() {
  isr_install();
  asm volatile("sti");
  // init_timer(5);
  init_keyboard();
}
