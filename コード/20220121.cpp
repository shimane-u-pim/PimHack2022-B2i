/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

 ***************************************************
 This example shows the basic function of library for DFPlayer.

 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)

 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial mySoftwareSerial(8, 2); // RX, TX  //SoftwareSerial
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
const int DIN_PIN = 3;

void setup()
{
  Serial.begin(9600);
  delay(1000);

  Serial.println("start");
  mySoftwareSerial.begin(9600);  //SoftwareSerial

  pinMode(DIN_PIN, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  while (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.  //SoftwareSerial
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(25);  //Set volume value. From 0 to 30
  //myDFPlayer.play(1);  //Play the first mp3
  pinMode(A0,OUTPUT);
}

//フラグが0の時発砲を受け付ける
int flag=0;
void loop()
{
  //static unsigned long timer = millis();

  if(flag == 0)
  {
    if (digitalRead(4) == LOW){
      // 単発
      if ( digitalRead( DIN_PIN ) == LOW )
      {
        Serial.println("trigger");
        digitalWrite(A0,HIGH);
        myDFPlayer.play(1);
        delay(1000);
        flag = 1;
      }
    }
    if (digitalRead(6) == LOW){
      // 3点バースト
      if ( digitalRead( DIN_PIN ) == LOW ){
        for(int i = 1; i < 4; i++){
          Serial.print("trigger");
          Serial.println(i);
          digitalWrite(A0,HIGH);
          myDFPlayer.play(1);
          delay(100);
          digitalWrite(A0,LOW);
          delay(100);
        }
      flag = 1;
      }  
    }
  }

//トリガーを離すと再度発砲を受け付ける
  if ( digitalRead( DIN_PIN ) == HIGH )
  {
    digitalWrite(A0,LOW);
    flag = 0;
  }
    /*
    else
    {
        digitalWrite( LED_PIN, HIGH );
    }
    */

  /*
  if (millis() - timer > 3000)
  {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 every 3 second.
  }
  */

  if (myDFPlayer.available())
  {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value)
{
  switch (type) 
  {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}