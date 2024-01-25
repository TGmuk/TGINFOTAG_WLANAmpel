/** My ESP8266Webserver class.
 *  Used for Webserver on Microcontroller.
 *  Grundeinstellungen und Definitionen: Siehe Einstellungen.h
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "ESP8266Webserver.h"
 * #include "LCD.h"

 * lcd myLCD;
 * ESP8266Webserver myWebserver;
 * AnalogIn poti(PA_0);
 * DigitalOut myled(PC_0);
 * string getRootPage()
 * {
 *       string webpage;
 *       webpage="<!DOCTYPE html>";
 *       //HTML
 *       webpage+="<html>";
 *       webpage+="<head>";
 *       webpage+="<title>STM32 HTTP</title>";
 *       webpage+="</head>";
 *       webpage+="<body>";
 *       webpage+="<h1>WIFI mit STM32 ESP01</h1>\n";
 *       webpage+="<p>Poti:"+to_string(poti)+"</p>\n"; 
 *       webpage+="<a href=\"ledAn\"><button>ON</button></a>\n";      
 *       webpage+="<a href=\"ledAus\"><button>OFF</button></a>\n";
 *       webpage+="</body>";
 *       webpage+="</html>";
 *       return webpage;
 * }
 * void testfunc()
 * {
 *     myWebserver.send(200,"text/html",getRootPage());
 * }
 * void testfunc2()
 * {
 *     myled=0;
 *     myWebserver.send(200,"text/html",getRootPage());
 * }
 * void testfunc3()
 * {
 *     myled=1;
 *     myWebserver.send(200,"text/html",getRootPage());
 * }
 * int main() {  
 *     myWebserver.on("ledAus",&testfunc2);
 *     myWebserver.on("ledAn",&testfunc3);
 *     myWebserver.on("/",&testfunc);
 *     myWebserver.begin();    
 *     myLCD.clear();
 *     myLCD.cursorpos(0);
 *     myLCD.printf("%s",myWebserver.gibIP());
 *     while(1)  {
 *          myWebserver.handleClient();
 *     }
 * }
 * @endcode
 */
#include "mbed.h"
//#include "string"
#include "Einstellungen.h"


class ESP8266Webserver
{   
    private:   

    int hs_count=0;
    Callback< void()> cbs[10];
    char hs[10][20];
    char recbuf[1000];
    bool beinhaltet(char* suchstring);
    int port=80;
    bool dbg;
    int clientID[10]={0,0,0,0,0,0,0,0,0,0};
    int clientIdx=0;
    char sendstring[1000];
    BufferedSerial *_serial;
    char ipadr[100];
    ATCmdParser *_parser;

    bool gefunden;
    string ipad=ip;
    
    

    public:
    char suchergebnis[20];
/** Aufrufzähler (öffentliches Attribut)
*/ 
    int Aufrufe=0;
    
/** Create Webserver instance
*/        
    ESP8266Webserver();
    
/** Legt die Callback-Operationen fest
 *
 * @param handlestring Suchtext im Request des Clients
 * @param func Callback-Operation falls der handlestring im Request gefunden wurde
 * @returns
 *   0 on success,
 *   -1 on error
*/
    int on(const char* handlestring,Callback< void()> func);

/** Startet den Webserver
 * @returns
 *   0 on success,
 *   -1 on error
*/
    int begin(void);

/** Prüft in der Endlosschleife zyklisch, ob neue Anfragen (Requests) vorliegen
 *
 * @returns
 *   0 on success,
 *   -1 on error
*/
    int handleClient(void);

/** Schickt eine Antwort (response) zum Client
 *
 * @param HTTPStatus Statuscode (200 = alles in Ordnung)
 * @param Mimetype z.B. "text/html"
 * @param webseite String (const char*) der die Webseite enthält
 * @returns
 *   0 on success,
 *   -1 on error
*/
    int send(int HTTPStatus,const char* Mimetype, const char* webseite);
    int send(int HTTPStatus,const char* Mimetype, const char* webseite,int length);

/** Schickt eine Antwort (response) zum Client
 *
 * @param HTTPStatus Statuscode (200 = alles in Ordnung)
 * @param Mimetype z.B. "text/html"
 * @param webseite String der die Webseite enthält
 * @returns
 *   0 on success,
 *   -1 on error
*/
    int send(int HTTPStatus,const char* Mimetype, std::string webseite);
    
/** Findet einen Wert-String zu dem Suchstring in dem Request
 * Damit können Inputs in Formularen (Textfelder, Slider, Textboxen usw.) 
 * ausgewertet werden
 * @param suchstring nach diesem String wird gesucht
 * @returns
 *   Wertstring
*/
    const char* gibWert(const char* suchstring);
    
/** Findet einen Wert-String zu dem Suchstring in dem Request
 * Damit können Inputs in Formularen (Textfelder, Slider, Textboxen usw.) 
 * ausgewertet werden
 * @param suchstring nach diesem String wird gesucht
 * @returns
 *   Wertstring
*/
    const char* gibWert(std::string suchstring);
    void debugOn(bool pD);
    void listAPs();
    
/** Gibt die IP-Adresse des Servers als String zurück
 *
 * @returns
 *   Wertstring
*/
    char* gibIP();


};