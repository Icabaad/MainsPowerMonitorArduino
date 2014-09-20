/*
 Parts of code and Library from the openenergymonitor.org project
 Licence: GNU GPL V3 Author: Trystan Lea
 */

#include "EmonLib.h"
#include <XBee.h>

//XBEE
XBee xbee = XBee();
// This is the XBee broadcast address.  You can use the address
// of any device you have also.
XBeeAddress64 Broadcast = XBeeAddress64(0x00000000, 0x0000ffff);

// Create  instances for each CT channel
EnergyMonitor ct1,ct2,ct3, ct4;

int interval = 10000;
long previousMillis = 0;

void setup() 
{
  Serial.begin(9600);
  // while (!Serial) {}
  // wait for serial port to connect. Needed for Leonardo only

  //Serial.println("emonTX Shield CT123 Voltage"); 
  //Serial.println("OpenEnergyMonitor.org");

  // Calibration factor = CT ratio / burden resistance = (100A / 0.05A) / 33 Ohms = 60.606
  ct1.current(1, 15.491); //Solar Burden Calculated Value:16.949 //Done
  ct2.current(2, 29.18); //Powerpoint  29.411   //Done                               
  ct3.current(3, 20.07); //heat 22.727 //Done
  ct4.current(4, 51.445); //total 60.606 //Done

  // (ADC input, calibration, phase_shift)
  ct1.voltage(5, 259.7, 1.265);  //done                              
  ct2.voltage(5, 259.7, 1.2);                                
  ct3.voltage(5, 259.7, 1.23); //done
  ct4.voltage(5, 259.7, 1.2); //done
}

void loop() 
{ 
  
    unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 5000) {
  // Calculate all. No.of crossings, time-out 
  ct1.calcVI(20,2000);                                                  
  ct2.calcVI(20,2000);
  ct3.calcVI(20,2000);
  ct4.calcVI(20,2000);
  /*   
   Serial.println("real Power, Apparent Power, RMS Voltage, RMS Current, Power Factor");
   Serial.println( ct1.realpower )
   Serial.println( ct2.realpower )
   Serial.println( ct3.realpower )
   Serial.println( ct4.realpower )
   */
   /*
  // Print power 
  Serial.print(ct1.realPower);     
  Serial.print(" "); 
  Serial.print(ct1.apparentPower);
  Serial.print(" "); 
  Serial.print(ct1.Vrms); 
  Serial.print(" "); 
  Serial.print(ct1.Irms); 
  Serial.print(" "); 
  Serial.println(ct1.powerFactor); 

  Serial.print(ct2.realPower);     
  Serial.print(" "); 
  Serial.print(ct2.apparentPower);
  Serial.print(" "); 
  Serial.print(ct2.Vrms); 
  Serial.print(" "); 
  Serial.print(ct2.Irms); 
  Serial.print(" "); 
  Serial.println(ct1.powerFactor); 

  Serial.print(ct3.realPower);     
  Serial.print(" "); 
  Serial.print(ct3.apparentPower);
  Serial.print(" "); 
  Serial.print(ct3.Vrms); 
  Serial.print(" "); 
  Serial.print(ct3.Irms); 
  Serial.print(" "); 
  Serial.println(ct3.powerFactor); 

  Serial.print(ct4.realPower);     
  Serial.print(" "); 
  Serial.print(ct4.apparentPower);
  Serial.print(" "); 
  Serial.print(ct4.Vrms); 
  Serial.print(" "); 
  Serial.print(ct4.Irms); 
  Serial.print(" "); 
  Serial.println(ct4.powerFactor); 

  Serial.println();
  // Available properties: ct1.realPower, ct1.apparentPower, ct1.powerFactor, ct1.Irms and ct1.Vrms
  */
  }

  if(currentMillis - previousMillis > interval) {
    //     digitalWrite(7, LOW); //wake xbee

    previousMillis = currentMillis;  


  char Buffer[128];
  char Buffer2[80];
  
    dtostrf(ct1.realPower, 7, 2, Buffer);
    strcpy(Buffer2, Buffer);
    strcat(Buffer2, ",");
    strcat(Buffer2, dtostrf(ct2.realPower, 7, 2, Buffer)); 
    strcat(Buffer2, ","); 
    strcat(Buffer2, dtostrf(ct3.realPower, 7, 2, Buffer)); 
    strcat(Buffer2, ","); 
    strcat(Buffer2, dtostrf(ct4.realPower, 7, 2, Buffer)); 
    strcat(Buffer2, ","); 
    strcat(Buffer2, dtostrf(ct1.Irms, 5, 2, Buffer)); 
    strcat(Buffer2, ","); 
    strcat(Buffer2, dtostrf(ct2.Irms, 5, 2, Buffer)); 
    strcat(Buffer2, ","); 
    strcat(Buffer2, dtostrf(ct3.Irms, 5, 2, Buffer)); 
    strcat(Buffer2, ","); 
    strcat(Buffer2, dtostrf(ct4.Irms, 5, 2, Buffer)); 
    strcat(Buffer2, ","); 
    strcat(Buffer2, dtostrf(ct1.Vrms, 5, 2, Buffer)); 
    strcat(Buffer2, "\r"); 
  
    ZBTxRequest zbtx = ZBTxRequest(Broadcast, (uint8_t *)Buffer2, strlen(Buffer2));
    xbee.send(zbtx);
     delay(5);
 /*   
     Serial.println();
      Serial.println(Buffer);
         Serial.println();
         Serial.println(Buffer2);
   */
  }

    //     digitalWrite(7, HIGH); //sleepxbee
  

  delay(5000);
}

