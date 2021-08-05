#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
:nullSegmentDescriptor(0,0,0),
unusedSegmentDescriptor(0,0,0),
dataSegmentDescriptor(0,64*1024*1024,0x9A),
codeSegmentDescriptor(0,64*1024*1024,0x92)
{
    uint32_t i[2];
    i[0] = (uint32_t)this;
    i[1] = sizeof(GlobalDescriptorTable) << 16;
    // what does +2 do?
    asm volatile("lgdt (%0)": : "p" (((uint8_t*)i)+2));
}

GlobalDescriptorTable::~GlobalDescriptorTable() 
{
}

// return the address distance?
uint16_t GlobalDescriptorTable::DataSegmentDescriptor() 
{
    return (uint8_t*)&dataSegmentDescriptor - (uint8_t*)this;
}

//?
uint16_t GlobalDescriptorTable::CodeSegmentDescriptor() 
{
    return (uint8_t*)&codeSegmentDescriptor - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type) 
{
    uint8_t* target = (uint8_t*)this;
    // why 2 ** 16 instead of 2 ** 12 here?
    if (limit <= 65536) {
        target[6] = 0x40;
    } else {
        if (limit & 0xFFF == 0xFFF) {
            limit >>= 12;
        } else {
            // the actual limit is smaller than desired
            limit >>= 12;
            limit -= 1;
        }
        target[6] = 0xC0;
    }
    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16);
    // assign base pointer    
    target[2] = base & 0xFF;
    base >>= 8;
    target[3] = base & 0xFF;
    base >>= 8;
    target[4] = base & 0xFF;
    base >>= 8;
    target[7] = base & 0xFF;
    // assign flags
    target[5] = type;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base() 
{
    uint8_t* target = (uint8_t*)this;
    uint32_t base = target[7];
    base <<= 8;
    base += target[4];
    base <<= 8;
    base += target[3];
    base <<= 8;
    base += target[2];
    return base;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit() 
{
    uint8_t* target = (uint8_t*)this;
    uint32_t limit = target[6] & 0xF;
    limit <<= 8;
    limit += target[1];
    limit <<= 8;
    limit += target[0];

    if (target[6] & 0x40 == 0x40) {
        return limit;
    } else {
        return (limit<<12)|0xFFF;
    }
}



