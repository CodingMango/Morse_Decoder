//Morse Code ENCODER (13-03-2025)
//for 5wpm speed approx
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define screenWidth 128
#define screenHeight 64
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, OLED_RESET);

const byte pushButton=4;
const byte pushButton2=5;
unsigned long previousTime=0;
unsigned long presentTime=0;
String str;
void morse(String);
void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  Serial.println("Enter Encrypted Message to decode:");

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1.9);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Enter Encrypted msg \nto decode: ");
  display.display();
  display.setCursor(0,28);
}

void loop() {
  if(digitalRead(pushButton)==HIGH){
    previousTime=millis();
    delay(1000);
    if(digitalRead(pushButton)==HIGH){
      delay(1000);
      presentTime=millis();
      if(  2000UL< presentTime - previousTime < 2500UL){
        str+='-';
      }
      goto skip; //to avoid unnecessary printing of dit " . " after the dash is concatenated in the string and the 
    }            //pushButton comes to Low
    if(digitalRead(pushButton)==LOW){
      presentTime=millis();
      if( 1000UL< presentTime - previousTime < 1500UL ){
        str+='.';
      }
    } 
  }
  skip:
  if(digitalRead(pushButton2)==HIGH){
    Serial.println("Decrypted message is: ");
    morse(str);
    Serial.print(str);
    display.display();
    display.print(str);
    display.display();
    display.print(" ");
    display.display();
    str="";
    Serial.println(" ");
    delay(2000);
  }
  //delay(500);
}
void morse(String s) {
  if (s == ".-"){
    Serial.print("A ");
    display.print("A ");
  }  else if (s == "-..."){
    Serial.print("B ");
    display.print("B ");
  }  else if (s == "-.-."){
    Serial.print("C ");
    display.print("C ");
  } else if (s == "-.."){
    Serial.print("D ");
    display.print("D ");
  } else if (s == "."){
    Serial.print("E ");
    display.print("E ");
  } else if (s == "..-."){
    Serial.print("F ");
    display.print("F ");
  } else if (s == "--."){
    Serial.print("G ");
    display.print("G ");
  } else if (s == "...."){
    Serial.print("H ");
    display.print("H ");
  } else if (s == ".."){
    Serial.print("I ");
    display.print("I ");
  } else if (s == ".---"){
    Serial.print("J ");
    display.print("J ");
  } else if (s == "-.-"){
    Serial.print("K ");
    display.print("K ");
  } else if (s == ".-.."){
    Serial.print("L ");
    display.print("L ");
  } else if (s == "--"){
    Serial.print("M ");
    display.print("M ");
  } else if (s == "-."){
    Serial.print("N ");
    display.print("N ");
  } else if (s == "---"){
    Serial.print("O ");
    display.print("O ");
  } else if (s == ".--."){
    Serial.print("P ");
    display.print("P ");
  } else if (s == "--.-"){
    Serial.print("Q ");
    display.print("Q ");
  } else if (s == ".-."){
    Serial.print("R ");
    display.print("R ");
  } else if (s == "..."){
    Serial.print("S ");
    display.print("S ");
  } else if (s == "-"){
    Serial.print("T ");
    display.print("T ");
  } else if (s == "..-"){
    Serial.print("U ");
    display.print("U ");
  } else if (s == "...-"){
    Serial.print("V ");
    display.print("V ");
  } else if (s == ".--"){
    Serial.print("W ");
    display.print("W ");
  } else if (s == "-..-"){
    Serial.println("X ");
    display.print("X ");
  } else if (s == "-.--"){
    Serial.print("Y ");
    display.print("Y ");
  } else if (s == "--.."){
    Serial.print("Z ");
    display.print("Z ");
  } else if (s == ".----"){
    Serial.print("1 ");
    display.print("1 ");
  } else if (s == "..---"){
    Serial.print("2 ");
    display.print("2 ");
  } else if (s == "...--"){
    Serial.print("3 ");
    display.print("3 ");
  } else if (s == "....-"){
    Serial.print("4 ");
    display.print("4 ");
  } else if (s == "....."){
    Serial.print("5 ");
    display.print("5 ");
  } else if (s == "-...."){
    Serial.print("6 ");
    display.print("6 ");
  } else if (s == "--..."){
    Serial.print("7 ");
    display.print("7 ");
  } else if (s == "---.."){
    Serial.print("8 ");
    display.print("8 ");
  } else if (s == "----."){
    Serial.print("9 ");
    display.print("9 ");
  } else if (s == "-----"){
    Serial.print("0 ");
    display.print("0 ");
  }
}