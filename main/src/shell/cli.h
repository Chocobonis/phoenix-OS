#include "cmd.h"

String (*command_line_interface[1000])(String) = { };

void _RTOS_CLI_SETUP_ () {
 command_line_interface[844] = (_NEO_FETCH_);
}

String _RTOS_CORE_EXECUTE_ (String _cmd_) {
 int hsum = 0;
 for(int i = 0; i < _cmd_.length(); i++){
    hsum += _cmd_[i];
 }
 if(_DEBUG_MODE_ == 1){
    Serial.println("{SYSTEM} >> command: " + _cmd_ + " fetched " + hsum);
 }
 if(command_line_interface[hsum] != NULL){
    return command_line_interface[hsum]("");
 }else{
    return "error command not found";
 }
} 