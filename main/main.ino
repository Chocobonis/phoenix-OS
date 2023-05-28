// ------ [ CONFIGURATION IMPORT ]-------
#include "cfg/config.h"
// ----- [ KERNEL MODULE IMPORT ] -------
#include <esp_task_wdt.h>
#include "src/kernel/kernel_main.h"
// ----- [ PIN DRIVERS IMPORT ] -------

// ----- [ BONYX's SHELL IMPORT ] ----- 
#ifdef _RTOS_SHELL_ENABLED_
  #include "src/shell/bsh.h"
#endif
// -------------------------------------------
TaskHandle_t _KERNEL_PROCESS_;
TaskHandle_t _SHELL_CLI_PROC_;
// ----- { THIS IS THE CORE OF THE OS } ------
void setup() {
  // WHEN THE BOOTLOADER STARTS THE OS THE STARTUP GOES HERE
  // --------------------------------------------------------
  #ifdef _RTOS_SHELL_ENABLED_
    _RTOS_SHELL_SETUP_();
  #endif
  #ifdef _RTOS_SYSMD_ENABLED_
    _BONYX_KERNEL_SETUP_();
  #endif
  Serial.println(".............................");
  Serial.println("· WELCOME TO PHOENIX OS 1.0 ·");
  Serial.println(".............................");
  // ---------------------------------------------------------------
  xTaskCreatePinnedToCore(
                    _BONYX_KERNEL_MAIN_, // Task function. 
                    "KERNEL THREAD",     // name of task. 
                    10000,               // Stack size of task 
                    NULL,                // parameter of the task 
                    1,                   // priority of the task 
                    &_KERNEL_PROCESS_,   // Task handle to keep track of created task 
                    0);                  // pin task to core 0                   
  delay(500); 
  // --------------------------------------------------------------
  xTaskCreatePinnedToCore(
                    _BONYX_SHELL_LOOP_,           // Task function. 
                    "COMMAND LINE INTERFACE",     // name of task. 
                    10000,                        // Stack size of task 
                    NULL,                         // parameter of the task 
                    1,                            // priority of the task 
                    &_SHELL_CLI_PROC_,            // Task handle to keep track of created task 
                    1);                           // pin task to core 1  
  delay(500);
}

/*
 -----------------------------------------------------------------------------------------
 - THIS IS THE LOOP PROCESS FOR WHEN THE SYSTEM IS RUNNING ON SINGLE THREAD PROCESS MODE -
 -----------------------------------------------------------------------------------------
*/
#ifndef _RTOS_SHELL_ENABLED_
void loop() {
  // SYSTEM MAIN LOOP FOR REFRESH AND KERNEL UPDATES GO HERE
  // ---------------------------------------------------------
}
#else
void loop(){}
#endif