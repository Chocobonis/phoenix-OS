#include "rfs/core.h"
#include "sys/calls.h"

void _BONYX_KERNEL_SETUP_ () {

    #ifdef _RTOS_SYSMD_ENABLED_
        Serial.println("\n= [Phoenyx OS - 1.0 Startup] =\n(Systemd) starting....");
            RFS->_RFS_SETUP_ ();
        Serial.println("(Systemd) done!");
    #endif
}

void _BONYX_KERNEL_MAIN_ (void * pvParameters){
    Serial.print("(Kernel) KERNEL RUNNING ON CORE 0\n");
   // Serial.println(xPortGetCoreID());

    for(;;){
        // LOOP CODE GOES HERE
        delay(100);
    }
}