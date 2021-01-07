//=========2021.01.07=====FeenLin==============
//=========DHT & LED & SoftwareSerial==========
#include "DHT.h"
#include "Adafruit_NeoPixel.h"
#include <SoftwareSerial.h>
#define DHTPIN 3      
#define DHTTYPE DHT22
#define Humidifier 4   // Humidifier open/close button
SoftwareSerial co2Serial(2,11);  // RX, TX
DHT dht(DHTPIN, DHTTYPE);
int i,j,k;
int color;
int add;
static unsigned int co2 = 0;
static unsigned int ucRxBuffer[10];
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(15,7,NEO_GRB + NEO_KHZ800); 
//======== WIFI & MCS & UDP===========
#include <LWiFi.h>
#include "MCS.h"
#include <Wire.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;

char _lwifi_ssid[] = "******";           //WIFI NAME
char _lwifi_pass[] = "******";       //WIFI PASSWORD
MCSDevice mcs("*******", "***********"); //MCS  (Deviceld / Devicekey)
MCSDisplayFloat Temp("Temp");
MCSDisplayFloat Humi("Humi");
MCSDisplayFloat Co2("Co2");
unsigned int localPort = 2390;      // local port to listen on
char packetBuffer[255]; //buffer to hold incoming packet
String str1;

char receiveData;

IPAddress ip;
WiFiUDP Udp;
void printWifiStatus();
void getAccel_Data();
String UdpR();     
int count=0;


void setup()
{
  Wire.begin();
  Serial.begin(9600);
  delay(500);
  co2Serial.begin(9600);
  mcs.addChannel(Temp);
  mcs.addChannel(Humi);
  mcs.addChannel(Co2);
  Serial.println("WIFI 連線開始");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("WIFI 連線成功");
  Serial.println("MCS 連線開始");
  Serial.println("MCS 連線成功");while(!mcs.connected()) { mcs.connect(); }
    
  pixels.begin();
  pixels.setBrightness(25);
  color = 0;
  add = 1;
  Serial.println(F("DHTxx test!"));
  dht.begin();
  
  printWifiStatus();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println("\nStarting connection to server...");
  Udp.begin(localPort);
  pinMode(Humidifier,OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{

   while (!mcs.connected()) {
  mcs.connect();
   if (mcs.connected()) { Serial.println("MCS 已重新連線"); }
    }
  mcs.process(1);

//================ Humidifier開關 ============//
    receiveData=UdpR().charAt(0);//取udp接收資料的第一個字元
    Serial.print("receiveDatareceiveData =");
    Serial.println(receiveData);
    Serial.println("~~~~~~UDP~~~~~~");
      if(receiveData =='O'){
              digitalWrite(Humidifier,HIGH);
              Serial.println("~~~~Humidifier ON ~~~~");
               
             }
      else if(receiveData =='C'){
              digitalWrite(Humidifier,LOW);
              Serial.println("~~~~Humidifier OFF ~~~~");  
             } 
//=================== co2 ==================//
    co2Serial.listen();
      byte request[] = {0x42, 0x4d, 0xe3, 0x00, 0x00, 0x01, 0x72};
      co2Serial.write(request, 7);
      delay(50);
      while (co2Serial.available()){
        for(int i=0; i<12; i=i+1){
          ucRxBuffer[i]=co2Serial.read();
          }
        co2 = ucRxBuffer[4]*256+ucRxBuffer[5];
        //Serial.println(co2); 
        }
      //delay(1000);  
//=================溫溼度 & led =============//
  int h = dht.readHumidity();  
  float t = dht.readTemperature();
  
  Serial.println(t);
  Serial.println(h);
  Serial.println(co2);

  Temp.set(t);
  Humi.set(h);
  Co2.set(co2);
  
//================================================//
  if(t<25){                
    
    for (i = 0; i <= 14; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,color));  // blue
    
      }
    pixels.show();
    color = color + add;
    if (color >= 80) {
    add = -1;
      } 
    else if (color <= 0) {
    add = 1;
      }   
  }
//==========================================//        
  else if((t>=25) && (t<=28)){                

    for (j = 0; j <= 14; j++) {
    pixels.setPixelColor(j, pixels.Color(0,color,0));  // green
    
      }
    pixels.show();
    color = color + add;
    if (color >= 80) {
    add = -1;
      } 
    else if (color <= 0) {
    add = 1;      
     }   
  }
//==========================================// 
  else{                
   
    for (k = 0; k <= 14; k++) {
    pixels.setPixelColor(k, pixels.Color(color,0,0));  // red
    
      }
    pixels.show();
    color = color + add;
    if (color >= 80) {
    add = -1;
      } 
    else if (color <= 0) {
    add = 1;
      }   
  } 
  delay(1);
}

//============== printWifiStatus ===================//
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
//  IPAddress ip;
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

//=============== UdpR ======================//
String UdpR(){
  String str1;
  void flush(); 
// if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp= Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    str1=String(packetBuffer[0]);
    for(int i=1; i<packetSize;i++)
        str1=str1+String(packetBuffer[i]);
    // send a reply, to the IP address and port that sent us the packet we received
    return str1;
  }
}  
//===============================================//
