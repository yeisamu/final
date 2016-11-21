

// include the library code:
#include <SoftwareSerial.h> //Librería que permite establecer comunicación serie en otros pins
#include <LiquidCrystal.h>
#include <DHT11.h>
const int sensorPin= A0;
const int sensorventi = 6;
const int controlagua = 10;
char cadena[255]; //Creamos un array de caracteres de 256 cposiciones
int i=0; //Tamaño actual del array
//Sensor Humedad
char state; // Variable lectrura serial
int pin=7;
DHT11 dht11(pin);
SoftwareSerial    bt(0,1); //10 RX, 11 TX.
//Leds
int led_1 = 22;
int led_2 = 23;
int led_3 = 24;
byte grado[8] =
 {
    0b00001100,     // Los definimos como binarios 0bxxxxxxx
    0b00010010,
    0b00010010,
    0b00001100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
 };
 byte porcen[8] =
 {
    0b00011000,     // Los definimos como binarios 0bxxxxxxx
    0b00011000,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00000011,
    0b00000011
 };
  int varblue=0; 
 int hume = 0;
//Servo motor;
// Iniciar la libreria con los pins de la interfaz de la libreria
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 int mintemp=20,limh=80,limmh=100;
void setup() {

  pinMode(sensorventi, OUTPUT);

  lcd.begin(16,2); //Decimos que la pantalla tiene 16 caracteres y dos líneas
  lcd.createChar(1, grado);
  lcd.createChar(2, porcen);
  lcd.setCursor(0,0); //Ponemos el cursor en la primer línea y el primer caracter
  lcd.print("Temp & RH"); //Se escribe el mensaje en la primer línea
  lcd.setCursor(0,1); //Movemos el cursor al primer caracter y segunda línea 
  lcd.print("Monitor"); //Escribimos el mensaje
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  
  pinMode(controlagua, OUTPUT);//motor.attach(6);
   
   Serial.begin(9600);
     bt.begin(9600); //Velocidad del puerto del módulo Bluetooth
 // 
  delay(2000); //Esperamos dos segundos
  lcd.clear();
 
}

void loop() {
  
/*
   digitalWrite(led_1, LOW);
   digitalWrite(led_2, LOW);
   digitalWrite(led_3, LOW);*/
    if(Serial.available() > 0){
       state = Serial.read();
  } // esta parte del código es para solo 1 Carácter o Unidad.  esta parte del código es para solo 1 Carácter o Unidad. 

  if (state == 't') {
    varblue=0;
    //digitalWrite(led_2, HIGH);
    //lcd.println("on");
     mintemp=20;
     limh=60;
     limmh=100;
    
    delay(100);
 }

  if (state == 'p') {
    varblue=0;
    //digitalWrite(led_1, HIGH);
    //lcd.println("on");
     mintemp=25;
     limh=55;
     limmh=70;   
    delay(100);
 }

   if (state == 'm') {
    varblue=0;
    //digitalWrite(led_3, HIGH);
    lcd.println("on");
     mintemp=30;
     limh=70;
     limmh=80;   
    delay(100);
 }

   if (state == 'v') {
    varblue=1;
    //digitalWrite(led_3, HIGH);
    digitalWrite(sensorventi, HIGH);
    delay(100);
 }

    if (state == 'f') {
    varblue=0;
    //digitalWrite(led_3, LOW);
    digitalWrite(sensorventi, LOW);
    delay(100);
 }

     if (state == 'w') {
    varblue=1;
   // digitalWrite(led_3, LOW);
    digitalWrite(controlagua, LOW);
    delay(100);
 }

    if (state == 'o') {
    varblue=0;
   // digitalWrite(led_3, HIGH);
    digitalWrite(controlagua, HIGH);
    delay(100);
 }
  int humedad = analogRead(sensorPin);
   if(humedad <= 500)
   {
       //activar agua
       // digitalWrite(sensorventi, LOW);
       lcd.setCursor(0, 0);
       lcd.print(humedad);
       lcd.print(" Tierra Muy mojada"); 
       if(varblue==0){ 
       digitalWrite(led_1, LOW);
       digitalWrite(led_2, LOW);
       digitalWrite(led_3, HIGH);
       digitalWrite(controlagua, HIGH);
       }
       // motor.write(360);
       //delay(1000);
      // lcd.clear();
   }
   
   if(humedad > 500 && humedad <= 700){
      //activar agua
      lcd.setCursor(0, 0);
       lcd.print(humedad);
       lcd.print(" Tierra humeda");  
       if(varblue==0){
         digitalWrite(led_1, LOW);
         digitalWrite(led_2, HIGH);
         digitalWrite(led_3, LOW);
         // motor.write(360);
         digitalWrite(controlagua, LOW);
           //delay(1000);
       }   
   }
   
   if(humedad > 700){
       lcd.setCursor(0, 0);
       lcd.print(humedad);
       lcd.print(" Tierra seca");  
       if(varblue==0){
         digitalWrite(led_1, HIGH);
         digitalWrite(led_2, LOW);
         digitalWrite(led_3, LOW);
         digitalWrite(controlagua, LOW);
         // motor.write(90);
       // delay(1000);
       } 
   }
  
    delay(2000);
    int err, humen;
    float temp, hum;
     lcd.clear();
   if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
    {

      if(hum >= limh && hum <=limmh){  
          humen=1;
           lcd.setCursor(0, 0);    
           digitalWrite(sensorventi, HIGH);
           lcd.print("  HR : ");
           lcd.print(hum,0);
           lcd.write(2); 
      }else{
        humen=0;
        lcd.setCursor(0, 0);
        digitalWrite(sensorventi, LOW);
        lcd.print("  HR: ");
        lcd.print(hum,0);
        lcd.write(2); 
      }
      //lcd.clear();
      if(temp >= mintemp){ 
          lcd.setCursor(0,1); 
        /*  for ( int n = 0 ; n < 255 ; n++)
           {
                digitalWrite(sensorventi, HIGH);
               delay(15) ;
           }    
         */
         if(humen==1){
          digitalWrite(sensorventi, HIGH);
         }else{
           digitalWrite(sensorventi, LOW);
         }
          
           lcd.print("  Temp: ");
           lcd.print(temp,0);
           lcd.write(1); 
      }else{
        lcd.setCursor(0,1); 
        if(humen==1){
          digitalWrite(sensorventi, HIGH);
         }else{
           digitalWrite(sensorventi, LOW);
         }
        //digitalWrite(sensorventi, LOW);
         lcd.print("  Temp : ");
         lcd.print(temp,0);
          lcd.write(1); 
      }
              
   }
   else
   {
            // Serial.println();
            lcd.print("Error Temperatura :");
             lcd.print(err);
             lcd.println();
   }

if(varblue==1){
  delay(100);
}else{
  delay(500);
}
     // 

}


