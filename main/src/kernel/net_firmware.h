#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class socket_manager {
    public:
    /*
       ---------------------------------------------------------
       - THESE ARE THE VARIABLES TO CREATE A REMOTE CONNECTION -
       ---------------------------------------------------------
    */
    void net_bonyx_define_cred(String _ssid, String _psk);
    void net_bonyx_interface_c();
    void net_bonyx_pacman_dwl (String _PACKET_NAME_);

};

void net_bonyx_define_cred(String _ssid, String _psk){
    wifi_ssid = _ssid;
    wifi_pass = _psk;
}

void net_bonyx_interface_c (){
    WiFi.begin(wifi_ssid, wifi_pass);

    while(WiFi.status() !=  WL_CONNECTED && timeout < 10){
        delay(1000);
        Serial.println("connecting. . . ");
        timeout++;
    }

    if(timeout >= 10){
        Serial.println("{Error}: could not connect to network");
    }
}

void net_bonyx_pacman_dwl (String _PACKET_NAME_){
    if(WiFi.status() == WL_CONNECTED){
        HTTPClient http;
        String req = "http://phoenix.slpmx.com/repos/pacman.php?packet=" + _PACKET_NAME_;
        http.begin(req.c_str());
        int httpcode = http.GET();
        if(httpcode > 0){
            Serial.println(httpcode);
            if(httpcode != 404){
                String script = http.getString();
            }else{
                Serial.begin("[ERROR]: pacman could not locate your packet");
            }
        }
    }else{
        Serial.println("You are not connected to internet...");
    }
}