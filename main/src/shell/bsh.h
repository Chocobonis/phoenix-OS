#include "cli.h"

void _RTOS_SHELL_SETUP_(){
    _RTOS_CLI_SETUP_();
    Serial.begin(9600);
}
String last_data;
String data;

int _RTOS_SHELL_UPDATE_ (){
    last_data = "";
    data = Serial.readStringUntil('\r\n');
    if(data.length() == 0){
        last_data = "";
    }else{
        last_data = _RTOS_CORE_EXECUTE_ (data);
        Serial.println("(Input command) root@phoenix>> " + last_data + " size: " + data.length());
    }
    return _RTOS_SUCCESS_; 
}

void _BONYX_SHELL_LOOP_ (void * pvParameters) {
    Serial.println("(System) SHELL RUNNING ON CORE 1");

    for(;;){
        // LOOP CODE GOES HERE
        _RTOS_SHELL_UPDATE_ ();
        delay(10);
    }
}