#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"
#include "port.h"
#include "gdt.h"

class InterruptManager
{
    protected:
        struct GateDescriptor 
        {
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBits;
        } __attribute__((packed));

        static GateDescriptor interruptDescriptorTable[256];

        struct interruptDescriptorTablePointer
        {
            uint16_t size;
            uint32_t base;
        } __attribute__((packed));

        static void SetInterruptDescriptorTableEntry(
            uint8_t interruptNumber,
            uint16_t codeSegmentOffset,
            void (*handler) (),
            uint8_t descriptorPrivilageLevel,
            uint8_t descriptType
        );

        Port8Bit picMasterCommand;
        Port8Bit picMasterData;
        Port8Bit picSlaveCommand;
        Port8Bit picSlaveData;

    public:

        InterruptManager(GlobalDescriptorTable* gdt);
        ~InterruptManager();

        void Activate();

        static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);

        static void IgnoreInterruptRequest();
        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();
};

#endif
