/*
 * ----------------------------------------------------------------------------
 * This sketch uses the MFRC522 library ; see https://github.com/miguelbalboa/rfid
 * for further details and other examples.
 * 
 * NOTE: The library file MFRC522.h has a lot of useful info. Please read it.
 * 
 * This sketch show a simple locking mechanism using the RC522 RFID module.
 * ----------------------------------------------------------------------------
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           
#define SS_PIN          10          

MFRC522 mfrc522(SS_PIN, RST_PIN);   
int b = Serial.available();
String read_rfid; 
String a = read_rfid;                 
String ok_rfid_1="8374c318";        //Change the address accordingly.
String ok_rfid_2="fa7c6824";        
int lock = 8;                       
int lock2 = 8; 
int LED1 = 5; //Power On
int LED2 = 6; //RFID active
int LED3 = 7; //RFID Reading 
int LED4 = 8; //RFID Error

  
void setup() {
    Serial.begin(9600);         // Initialize serial communications with the PC
    while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();                // Init SPI bus
    mfrc522.PCD_Init();         // Init MFRC522 card

    pinMode(lock, OUTPUT);
    pinMode(lock2, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    
    digitalWrite(5,HIGH);
    delay(3000);
    digitalWrite(5,LOW);
    
        if(a == read_rfid){
          digitalWrite(6,HIGH);
          delay(3000);
          digitalWrite(6,LOW);
          } 

          if(b != Serial.available()){
            digitalWrite(8,HIGH);
            delay(3000);
            digitalWrite(8,LOW);
            }


    
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    read_rfid="";
    for (byte i = 0; i < bufferSize; i++) {
        read_rfid=read_rfid + String(buffer[i], HEX);
    }
}

void open_lock() {
  //Use this routine when working with Relays and Solenoids etc.
  digitalWrite(lock,HIGH);
  delay(5000);
  digitalWrite(lock,LOW);
}


void close_lock2() {          // You can also just use the card to shutdown your PC. This is just for those moments that you really need to shut it down quickly. 
  //Use this routine when working with Relays and Solenoids etc.
  digitalWrite(lock2, HIGH);
  delay(5000);                
  digitalWrite(lock2,LOW);
}


void loop() {
  
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    if ( ! mfrc522.PICC_ReadCardSerial())
        return;


    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println(read_rfid);

    if (read_rfid==ok_rfid_1) {
      //ok, open the door.
      open_lock();
      Serial.println("Door opened by rfid_1");
    }

    Serial.println(read_rfid);
    if (read_rfid==ok_rfid_2) {
      Serial.println("Door opened by rfid_1");
      
      close_lock2();
    }
}
