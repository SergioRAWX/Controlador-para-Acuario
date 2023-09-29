
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ECHO 10
#define TRIG 9
#define ANCHO 128
#define ALTO 64
#define DISPLAY_RESET 4
Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, DISPLAY_RESET);

/*static const unsigned char PROGMEM imagen[]={
  };*/

int duracion, distancia, nivel;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG, LOW);
  duracion=pulseIn(ECHO, HIGH);
  distancia=(duracion/2)/29;
  delay(50);
  Serial.print("DISTANCIA:  ");
  Serial.println(distancia);

  display.clearDisplay();
  display.setCursor(2,2);
  display.print("DISTANCIA: ");
  display.print(distancia);
  display.drawLine(2,12,126,12, WHITE);
  display.setCursor(2,25); 
  display.print("NIVEL DE AGUA: ");
  nivel=100-(100*distancia/60);
  if(nivel<0){
    nivel=0;
  }
  display.print(nivel);
  display.print(" %");
  Serial.print("NIVEL: ");
  Serial.println(nivel);
  Serial.println(" ");
  display.setCursor(2,35);
  display.print("EST:  ");

  
  if(distancia<5){
    display.print("EXCESO");
    }
  if(distancia>=5&&distancia<12){
        display.print("NORMAL");
    }
  if(distancia>=12&&distancia<18){
            display.print("BAJO");
    }
  if(distancia>=18){
      display.print("DEFICIENTE");
    }
    
  delay(100);
  display.display();
  delay(1);


}
