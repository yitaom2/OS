#ifndef __GDT_H
#define __GDT_H

#include "types.h"
class GlobalDescriptorTable {
    public:
        class SegmentDescriptor {
            private:
                uint16_t limit_lo;
                uint16_t base_lo;
                uint8_t base_hi;
                uint8_t type;
                uint8_t flags_limit_hi;
                uint8_t base_vhi;           
            public:
                SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
                uint32_t Base();
                uint32_t Limit();
        } __attribute__((packed));
        
        SegmentDescriptor nullSegmentDescriptor;
        SegmentDescriptor unusedSegmentDescriptor;
        SegmentDescriptor dataSegmentDescriptor;
        SegmentDescriptor codeSegmentDescriptor;

    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();
        uint16_t DataSegmentDescriptor();
        uint16_t CodeSegmentDescriptor();
};

#endif
