/*
  EmonTx CT123 Voltage Serial Only example
  
  Part of the openenergymonitor.org project
  Licence: GNU GPL V3
  
  Author: Trystan Lea
*/

#include "EmonLib.h"

// Create  instances for each CT channel
EnergyMonitor ct1,ct2,ct3, ct4;

// On-board emonTx LED
const int LEDpin = 9;                                                    

void setup() 
{
  Serial.begin(9600);
  // while (!Serial) {}
  // wait for serial port to connect. Needed for Leonardo only
  
  Serial.println("emonTX Shield CT123 Voltage Serial Only example"); 
  Serial.println("OpenEnergyMonitor.org");
  
  // Calibration factor = CT ratio / burden resistance = (100A / 0.05A) / 33 Ohms = 60.606
  ct1.current(1, 15.491); //Solar 16.949 //Done
  ct2.current(2, 29.18); //Powerpoint  29.411   //Done                               
  ct3.current(3, 20.07); //heat 22.727 //done
  ct4.current(4, 51.4545); //total 60.606 //Done
  
  // (ADC input, calibration, phase_shift)
  ct1.voltage(5, 259.7, 1.7);                                
  ct2.voltage(5, 259.7, 1.7);                                
  ct3.voltage(5, 259.7, 1.7);
  ct4.voltage(5, 259.7, 1.7);
  
  // Setup indicator LED
  pinMode(LEDpin, OUTPUT);                                              
  digitalWrite(LEDpin, HIGH);                                                                                  
}

void loop() 
{ 
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
  // Print power 
  Serial.print(ct1.realPower);     
  Serial.print(" "); 
    Serial.print(ct1.Vrms); 
  Serial.print(" "); 
      Serial.println(ct1.Irms); 
  
  Serial.print(ct2.realPower);
    Serial.print(" "); 
  Serial.print(ct2.Vrms); 
    Serial.print(" "); 
      Serial.println(ct2.Irms); 
  
  Serial.print(ct3.realPower);
  Serial.print(" "); 
    Serial.print(ct3.Vrms); 
      Serial.print(" "); 
      Serial.println(ct3.Irms); 

  Serial.print(ct4.realPower);
  Serial.print(" ");   
    Serial.print(ct4.Vrms); 
      Serial.print(" "); 
      Serial.println(ct4.Irms); 

//  Serial.print(ct1.Vrms);
  Serial.println();
    
  // Available properties: ct1.realPower, ct1.apparentPower, ct1.powerFactor, ct1.Irms and ct1.Vrms

  delay(5000);
}
