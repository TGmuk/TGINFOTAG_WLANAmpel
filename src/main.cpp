#include "mbed.h"
#include "ESP8266Webserver.h"
#include "LCD.h"
#include <string>

#define BLINKING_RATE     750ms

lcd myLCD;
ESP8266Webserver myWebserver;
PortOut ledsampel(PortC, 0xFF);//PC_0=AR, PC_1=AG, PC_2=AGR, PC_3=FR, PC_4=FR
char tab1[16] = {0x0c, 0x0c, 0x0a, 0x0a, 0x0a, 0x09, 0x09, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x09, 0x0b,
                 0x0b};//1-aktive LEDs
char tab2[16] = {0xF3, 0xF3, 0xF5, 0xF5, 0xF5, 0xF6, 0xF6, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xF6, 0xF4,
                 0xF4};//0-aktive LEDs

uint8_t ampelPhase = 0;
Timeout ampelTimeout;
bool nextAmplePhaseFlag = false;


string getRootPage() {
    string webpage;
    webpage = "<!DOCTYPE html>";
    //HTML
    webpage += "<html>";
    webpage += "<head>";
    webpage += "<title>STM32 HTTP</title>";
    webpage += "</head>";
    webpage += "<body>";
    webpage += "<div style=\"position: absolute; top:0; bottom: 0; left: 0; right: 0; margin: auto; text-align: center;\">";
    webpage += "<h1 style=\"font-family: Arial,Helvetica,sans-serif;\">Ampel mit WLAN</h1>\n";
    webpage += "<h3 style=\"font-family: Arial,Helvetica,sans-serif;\">Einfach mal druecken</h3>\n";
    webpage += "<a href=\"ampelAn\"><button style=\"height:90%; width:90%; font-family: Arial,Helvetica,sans-serif; font-size: 40px;\">Fussgaenger Taste</button></a>\n";
    webpage += "</div>";
    webpage += "</body>";
    webpage += "</html>";
    return webpage;
}

string getPhasePage() {
    string webpage;
    webpage = "<!DOCTYPE html>";
    //HTML
    webpage += "<html>";
    webpage += "<head>";
    webpage += "<title>STM32 HTTP</title>";

    webpage += "<meta http-equiv=\"refresh\" content=\""; // Redirect after x amount of time back to root page
    webpage += to_string(750*16/1000);
    webpage += "; URL=/\">";

    webpage += "</head>";
    webpage += "<body>";
    webpage += "<div style=\"position: absolute; top:0; bottom: 0; left: 0; right: 0; margin: auto; text-align: center;\">";
    webpage += "<h1 style=\"font-family: Arial,Helvetica,sans-serif;\">Ampel macht gerade amplische Sachen :)</h1>\n";
    webpage += "<h3 style=\"font-family: Arial,Helvetica,sans-serif;\">Bitte kurz warten</h3>\n";
    webpage += "</div>";
    webpage += "</body>";
    webpage += "</html>";
    return webpage;
}

void setAmplePhaseFlag(){
    nextAmplePhaseFlag = true;
}

void nextAmpelPhase(){
    ledsampel = tab1[ampelPhase];
    ampelPhase++;
    nextAmplePhaseFlag = false;

    if(ampelPhase >= 16){
        ampelPhase = 0;
        ledsampel = 0x0c;//1-aktive LEDs
        myWebserver.send(200, "text/html", getRootPage());
    }else{
        ampelTimeout.attach(setAmplePhaseFlag, BLINKING_RATE);

    }

}


//Fussgängertaste betätigen -> Ampelausgabe
void webAmpelPage() {
    printf("Ampel\n");
    myWebserver.send(200, "text/html", getPhasePage());
    setAmplePhaseFlag();
}

//Startseite anzeigen
void webRootPage() {
    myWebserver.send(200, "text/html", getRootPage());
}

int main() {
    myWebserver.on("ampelAn", &webAmpelPage);
    myWebserver.on("/", &webRootPage);
    myWebserver.begin();
    myLCD.clear();
    myLCD.cursorpos(0);
    myLCD.printf("%s", myWebserver.gibIP());
    myLCD.cursorpos(40);
    myLCD.printf("FussgaengerAmpel");

    //ledsampel=0xF3;//0-aktive LEDs
    ledsampel = 0x0C;//1-aktive LEDs


    while (1) {
        myWebserver.handleClient();
        if(nextAmplePhaseFlag){
            nextAmpelPhase();
        }
    }
}
