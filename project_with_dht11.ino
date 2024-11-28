#include<IRremote.h>
#include<dht.h>
#include<LiquidCrystal.h>
int receiver = 10;
dht DHT;
String Humidity;
String Temperature;
 

IRrecv irrecv(receiver);          
decode_results results; 
LiquidCrystal lcd(2,3,4,5,6,7);
/*-----( Declare Variables )-----*/
float temp;
int fan = 8;
int A=100; 
int fspeed = 100;// fan speed, the defualt speed is 100
int B=0;
 
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(fan,OUTPUT);
  digitalWrite(fan,LOW);
  Serial.println("IR Receiver Raw Data + Button Decode Test");
  irrecv.enableIRIn(); // Start the receiver
 
 
}/*--(end setup )---*/
 
 
void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?
 
  {
    switch(results.value){
      case 0xFFB04F:
      B=1;
    DHT.read11(12);
    Temperature=DHT.temperature;
    Serial.print("The temperature is:");
    lcd.print("Temperature:");
    lcd.print(Temperature);
    //Serial.println(temp);
    if(DHT.temperature<=22.00){
      analogWrite(fan,0);
      lcd.setCursor(0,1);
      lcd.print("Fanspeed:0");
      delay(3000);
    }
    if((DHT.temperature >22.00) && (DHT.temperature <= 25.00)) 
   {  
       analogWrite(fan, 100); 
        lcd.setCursor(0,1);
        lcd.print("Fanspeed:Low");
        delay(3000);
   } 
   if((DHT.temperature > 25.00) && (DHT.temperature <= 28.00)) 
   {  
       analogWrite(fan, 180);
       lcd.setCursor(0,1);
        lcd.print("Fanspeed:Medium");
       delay(3000);
   }
   if((DHT.temperature >28.00)) 
   {  
       analogWrite(fan, 250);  
       lcd.setCursor(0,1);
       lcd.print("Fanspeed:High");
       delay(3000);
   } 
   delay(1000);
   lcd.clear();
    break;
    default:
    B=2;
    translateIR();
    }
    irrecv.resume(); // receive the next value 
  }
  if(B==1){
  lcd.print("Auto Mode");
  delay(2000);
  lcd.clear();
  Auto(); 
  }
  if(B==2){
    lcd.print("Manual mode");
  DHT.read11(12);
  Temperature=DHT.temperature;
  lcd.setCursor(0,1);
  lcd.print("Temperature:");
  lcd.print(Temperature);
  delay(2000);
  lcd.clear();  
  }
}/* --(end main loop )-- */
 
/*-----( Declare User-written Functions )-----*/
void translateIR() // takes action based on IR code received
 
 
{
 
  switch(results.value)
 
  {
 
  case 0xFF6897:  
     analogWrite(fan, 0);
     lcd.print("Manual mode");
     lcd.setCursor(0,1);
     lcd.print("Fanspeed:0");
     Serial.println(fspeed); 
     delay(1000);
     break;
 
  case 0xFF9867:  
 
     analogWrite(fan,100);
     lcd.print("Manual mode");
     lcd.setCursor(0,1);
     lcd.print("Fanspeed:");
     lcd.print(fspeed);
     Serial.println(fspeed);
     delay(1000);
    break;

   case 0xFF18E7:
      A+=50;
      if (A>= 255){
        A=250;
      }
      analogWrite(fan,A);
      lcd.print("Manual mode");
     lcd.setCursor(0,1);
     lcd.print("Fanspeed:");
     lcd.print(A);
      Serial.println(A);
      break;

    case 0xFF4AB5:

      A-=50;
      if(A<=20){
        A=50;
      }
      analogWrite(fan,A);
      lcd.print("Manual mode");
     lcd.setCursor(0,1);
     lcd.print("Fanspeed:");
     lcd.print(A);
      Serial.println(A);
      break;
  default: 
    Serial.println(" other button   ");
 
  }
  delay(1000);
   lcd.clear();
 
  delay(500);
}
void Auto(){
  DHT.read11(12);
  Temperature=DHT.temperature;
  lcd.print("Temperature:");
    lcd.print(Temperature);
    Serial.println(temp);
    if(DHT.temperature<=22.00){
      analogWrite(fan,0);
      lcd.setCursor(0,1);
      lcd.print("Fanspeed:0");
      delay(3000);
    }
    if((DHT.temperature > 23.00) && (DHT.temperature <= 25.00)) 
   {  
       analogWrite(fan, 100); 
        lcd.setCursor(0,1);
        lcd.print("Fanspeed:Low");
        delay(3000);
   } 
   if((DHT.temperature > 25.00) && (DHT.temperature <= 28.00)) 
   {  
       analogWrite(fan, 180);
       lcd.setCursor(0,1);
        lcd.print("Fanspeed:Medium");
       delay(3000);
   }
   if((DHT.temperature > 28)) 
   {  
       analogWrite(fan, 250);  
       lcd.setCursor(0,1);
       lcd.print("Fanspeed:High");
       delay(3000);
   } 
   delay(1000);
   lcd.clear();
}
