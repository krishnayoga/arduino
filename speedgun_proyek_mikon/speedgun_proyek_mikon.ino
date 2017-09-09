//For RTC module
#include <virtuabotixRTC.h> 
virtuabotixRTC myRTC(6, 7, 8);  //pin digital 6, 7, dan 8

//For datalogger module
#include <SPI.h>
#include <SD.h>
const int chipSelect = 10; //pin digital 10

//For addon
#define LED_PIN 2 //pin digital 2, untuk menyalakan LED
#define TRIG_PIN 3 //pin digital 3, untuk mentrigger shutter camera

//For doppler sensor
#define PIN_NUMBER 4
#define AVERAGE 2
unsigned int doppler_div = 19;
unsigned int samples[AVERAGE];
unsigned int x;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_NUMBER, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  
  //set RTC module
  myRTC.setDS1302Time(00, 30, 14, 2, 15, 8, 2017);
  
  //set SD Card module
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  myRTC.updateTime();  
  
  noInterrupts();
  pulseIn(PIN_NUMBER, HIGH);
  unsigned int pulse_length = 0;
  for (x = 0; x < AVERAGE; x++)
  {
    pulse_length = pulseIn(PIN_NUMBER, HIGH);
    pulse_length += pulseIn(PIN_NUMBER, LOW);
    samples[x] = pulse_length;
  }
  interrupts();
  bool samples_ok = true;
  unsigned int nbPulsesTime = samples[0];
  for (x = 1; x < AVERAGE; x++)
  {
    nbPulsesTime += samples[x];
    if ((samples[x] > samples[0] * 2) || (samples[x] < samples[0] / 2))
    {
      samples_ok = false;
    }
  }
  if (samples_ok)
  {
    unsigned int Ttime = nbPulsesTime / AVERAGE;
    unsigned int Freq = 1000000 / Ttime;
    #ifdef PYTHON_OUTPUT
    Serial.write(Freq/doppler_div);
    #else
    if (Freq/doppler_div > 5 && Freq/doppler_div < 100){                                                             
      Serial.print(myRTC.dayofmonth);                                                                     
      Serial.print("/");                                                                                   
      Serial.print(myRTC.month);                                                                          
      Serial.print("/");                                                                                  
      Serial.print(myRTC.year);                                                                            
      Serial.print("  ");                                                                                    
      Serial.print(myRTC.hours);                                                                           
      Serial.print(":");                                                                                   
      Serial.print(myRTC.minutes);                                                                          
      Serial.print(":");                                                                                   
      Serial.print(myRTC.seconds);           
      Serial.print(" Frekuensi: ");
      Serial.print(Freq);
      Serial.print("Hz Kecepatan: ");
      Serial.print(Freq/doppler_div);
      Serial.print("km/h\r\n");
      digitalWrite(LED_PIN,LOW);
      digitalWrite(TRIG_PIN, LOW);
      
      File dataFile = SD.open("logdata.txt", FILE_WRITE);
    if (dataFile) {                                                             
      dataFile.print(myRTC.dayofmonth);                                                                     
      dataFile.print("/");                                                                                   
      dataFile.print(myRTC.month);                                                                          
      dataFile.print("/");                                                                                  
      dataFile.print(myRTC.year);                                                                            
      dataFile.print("  ");                                                                                    
      dataFile.print(myRTC.hours);                                                                           
      dataFile.print(":");                                                                                   
      dataFile.print(myRTC.minutes);                                                                          
      dataFile.print(":");                                                                                   
      dataFile.print(myRTC.seconds);           
      dataFile.print(" Frekuensi: ");
      dataFile.print(Freq);
      dataFile.print("Hz Kecepatan: ");
      dataFile.print("    ");
      dataFile.print(Freq/doppler_div);
      dataFile.print("km/h\r\n");
      dataFile.close();
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening log_kecepatan.txt");
    }
    }
  
    else if (Freq/doppler_div > 100 && Freq/doppler_div < 300){                                                              
      Serial.print(myRTC.dayofmonth);                                                                       
      Serial.print("/");                                                                                  
      Serial.print(myRTC.month);                                                                           
      Serial.print("/");                                                                                   
      Serial.print(myRTC.year);                                                                           
      Serial.print("  ");                                                                                   
      Serial.print(myRTC.hours);                                                                          
      Serial.print(":");                                                                                    
      Serial.print(myRTC.minutes);                                                                           
      Serial.print(":");                                                                                   
      Serial.print(myRTC.seconds);           
      Serial.print(" Frekuensi: ");
      Serial.print(Freq);
      Serial.print("Hz Kecepatan: ");
      Serial.print(Freq/doppler_div);
      Serial.print("km/h\r\n");
      digitalWrite(LED_PIN,HIGH);
      digitalWrite(TRIG_PIN, HIGH);

      File dataFile = SD.open("logdata.txt", FILE_WRITE);
    if (dataFile) {                                                             
      dataFile.print(myRTC.dayofmonth);                                                                     
      dataFile.print("/");                                                                                   
      dataFile.print(myRTC.month);                                                                          
      dataFile.print("/");                                                                                  
      dataFile.print(myRTC.year);                                                                            
      dataFile.print("  ");                                                                                    
      dataFile.print(myRTC.hours);                                                                           
      dataFile.print(":");                                                                                   
      dataFile.print(myRTC.minutes);                                                                          
      dataFile.print(":");                                                                                   
      dataFile.print(myRTC.seconds);           
      dataFile.print(" Frekuensi: ");
      dataFile.print(Freq);
      dataFile.print("Hz Kecepatan: ");
      dataFile.print("    ");
      dataFile.print(Freq/doppler_div);
      dataFile.print("km/h\r\n");
      dataFile.close();
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening log_kecepatan.txt");
    }
    }
   #endif
   delay(200);
  }
  else
  {
    #ifndef PYTHON_OUTPUT
    Serial.print(".");
    digitalWrite(LED_PIN,LOW);
    digitalWrite(TRIG_PIN, LOW);
    #endif
  }
}
