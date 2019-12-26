//To Control Irrigation Solenoid valuve at Farm

//Open button (V10) and close button (V11) to trigger relays forcing solednoid valve to open/close


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//char auth[] = "LOqZjYCKeTz6zUa0qnT2_Jqn0Qi5ZC92";
//char ssid[] = "Atthow Ave TC";
//char pass[] = "512maidstone";

char auth[] = "yDUFQQKZy2Iy8bafwuz9uc0vTYQoifRm"; //Dads Blynk code
char ssid[] = "iinetD90925";
char pass[] = "HE4MECJQHCWHMEC";


BlynkTimer timer;

int value;
int relaypin1 = 4;  // digital pin for relay 1
int relaypin2 = 5;  // digital pin for relay 2
String displaywifi;
int wifisignal;

void setup()
{
  // Debug console
  Serial.begin(115200);
  digitalWrite(relaypin1, HIGH);
  digitalWrite(relaypin2,HIGH);
  pinMode(relaypin1,OUTPUT);
  pinMode(relaypin2,OUTPUT);

  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(1000000L, sendwifi);
    
}

BLYNK_WRITE(V10)
{
  value = param.asInt(); // Get State of Virtual Button
  
  Serial.print("V10 button value is: ");
  Serial.println(value);
  
  if (value ==1){
    digitalWrite(relaypin1,LOW);
  }
  else{
    digitalWrite(relaypin1, HIGH);
  }
}

BLYNK_WRITE(V11)
{
  value = param.asInt(); // Get State of Virtual Button
  
  Serial.print("V10 button value is: ");
  Serial.println(value);
  
  if (value ==1){
    digitalWrite(relaypin2, LOW);
  }
  else{
    digitalWrite(relaypin2,HIGH);
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendwifi()
{
  wifisignal = map(WiFi.RSSI(), -105, -40, 0, 100);
  displaywifi = String("           Wifi: ") + wifisignal +String("%");
    
  Blynk.setProperty(V10, "label", displaywifi);
  Blynk.setProperty(V11, "label", displaywifi);
  
}

BLYNK_APP_CONNECTED(){
  Blynk.syncAll();
  
}
