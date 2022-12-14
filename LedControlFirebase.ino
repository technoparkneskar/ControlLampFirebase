#include <FirebaseESP8266.h>
#include <WiFiManager.h>

//****** Harap Sesuaikan Programnya *******
#define FIREBASE_HOST "https://areauji-default-rtdb.firebaseio.com" //Sesuaikan dengan link firebase database kalian, tanpa menggunakan "http:" , "\" and "/"
#define FIREBASE_AUTH "Bn7LhCTiP8VphRn53K2WmcqlHvV6WnexeRj7vKLa3ns" //Sesuaikan dengan firebase database secret code kalian
#define NamaHotspot "ControlLampFirebase" // Nama hotspot di esp8266
//Ubah di bagian dalam " <> " 
//****** Harap Sesuaikan Programnya *******


FirebaseData firebaseData;

#define lamp D8 //D1
String val1;

String zero = "0" , one = "1";

void setup(){
  WiFiManager wm;
    wm.resetSettings();
    bool res;
    res = wm.autoConnect("NamaHotspot");
    if(!res) {
     Serial.println("Failed to connect");
     // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
     
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
  
 pinMode(lamp,OUTPUT);
 digitalWrite(lamp,LOW);

  Serial.print('\n');
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to firebase
 Firebase.reconnectWiFi(true);
  Firebase.setString(firebaseData, "S2","0");
 delay(100);
}

void loop(){
      Firebase.getString(firebaseData, "S2");
 val1 = firebaseData.stringData(); Serial.print('\n');

 Serial.print("Value 1 ");Serial.println(val1);

    if(val1==one) // If, the Status is 1, turn on the Relay1
     { digitalWrite(lamp,LOW); Serial.println("light 2 OFF"); } 
    else if(val1==zero) // If, the Status is 0, turn Off the Relay1
     { digitalWrite(lamp,HIGH); Serial.println("light 2 ON"); }
}
