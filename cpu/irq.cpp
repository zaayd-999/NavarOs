#include "../drivers/keyboard/keyboard.h"
#include "pic.h"
#include "irq.h"

extern "C" void irq_handler(int irq) {
    if(irq == 1) {
        keyboard_handler();
    }
    pic_send_eoi(irq);
}