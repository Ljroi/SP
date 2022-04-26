#include "PinNames.h"
#include "mbed.h"
#include "InterruptIn.h"

DigitalOut oled1(PA_8);
DigitalOut oled2(LED1);
InterruptIn ibutton1(BUTTON1);

typedef struct {
int vnyt; 
int vnesh; 
} message_t;

MemoryPool<message_t, 16> mpool;
Queue<message_t, 16> queue;
Thread thread;

uint32_t i1 = 0;

void pressed()
{
i1++; 
message_t *message = mpool.alloc();

message->vnyt = i1%2;

queue.put(message);

}





// main() runs in its own thread in the OS
int main()
{
    ibutton1.rise(&pressed);
    //thread.start(send_thread);
    while (true) {
    osEvent evt = queue.get();
    if (evt.status == osEventMessage) {
    message_t *message = (message_t *)evt.value.p;
    if((message->vnyt)==0)
    {
        oled1=1;
        oled2=1;
    }
    else 
    {
        oled1=0;
        oled2=0;
    }
    mpool.free(message);
    }
    }
}