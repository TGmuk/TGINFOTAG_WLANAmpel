#include "mbed.h"
#include "string"

/** Der Mikrocontroller kann entweder ein eigenes WLAN aufbauen (Accesspoint)
oder sich bei einem vorhandenen Netzwerk anmelden

Soll der ESP01 als Accesspoint oder Station in einem bestehenden WLAN
betrieben werden?
*/

//#define station true  //true=Station
#define station false   //false=Accesspoint

/** accesspoint
 * #define ip "192.168.5.1"    //IP-Adresse des Webseervers festlegen
 * #define netzmaske "255.255.255.0"  //Netzmaske des Webservers festlegen
 * #define Port 80 //Port des Webservers festlegen. 80: HTTP-Port
*/
#define ip "192.168.5.2"    //IP-Adresse des Webseervers festlegen
#define netzmaske "255.255.255.0"  //Netzmaske des Webservers festlegen
#define Port 80 //Port des Webservers festlegen. 80: HTTP-Port

//station
#define scanAPs false   //mit true kann nach vorhandenen Netzen gesucht werden
                        //die Anzeige erfolgt mit dem Terminal
#define ssid " "   //SSID des WLANs
#define passwort " " //Passwort des Netzwerks

//Diagnose-Meldungen an Terminal senden (nein = false)
#define pDebug false

//Anschluss
#define tx PB_10
#define rx PB_11
#define CH_PD PB_13
#define RST PB_12
#define ESP8266_DEFAULT_BAUD_RATE   115200