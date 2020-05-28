
#include <LiquidCrystal.h>

int ledPin = 11;               
int PIRpin = 8;            
int pirState = LOW;            
int val = 0;                    
// photocell circuit
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
float photocellReading;     // the analog reading from the sensor divider         
int pinSpeaker = 10;  // must be a pwm pin (9, 10 or 11)
float illuminance = 0.;
float ADC_val = 5./1024.;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);                        


void setup() {  

  pinMode(ledPin, OUTPUT);       
  pinMode(PIRpin, INPUT);     
  pinMode(photocellPin, INPUT);
  pinMode(pinSpeaker, OUTPUT);
    
  Serial.begin(9600);
  lcd.begin(16, 2); 
  lcd.setCursor(2, 0); 
  lcd.print("P.I.R Motion ");
  lcd.setCursor(0, 1); 
  lcd.print("and Light Sensors");
  delay(2000);
                 
	lcd.clear();                           
	lcd.setCursor(0, 0); 
    lcd.print("Processing Data.");
	playTone(300, 300);
	delay(150);
	playTone(0, 0);
    delay(3000);
    lcd.clear(); 
    lcd.setCursor(3, 0);
    lcd.print("Waiting For");
    lcd.setCursor(3, 1);
    lcd.print("Motion....");    
  
}

void loop(){ 
  val = digitalRead(PIRpin);
  photocellReading = analogRead(photocellPin);
  float Vout = ADC_val*photocellReading;
  illuminance = 500/(10*((5-Vout)/Vout));

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);


    if (pirState == LOW) {
      Serial.println("Motion detected!");
      Serial.println(photocellReading);
	
      lcd.clear() ;
      lcd.setCursor(0, 0);            
      lcd.print("Motion Detected!");   
      lcd.setCursor(0, 1);               
      lcd.print(illuminance);
      lcd.print(" lux");
      playTone(300, 300);
	  delay(150);
	  playTone(0, 0);
	  
      pirState = HIGH;

    }
  } else {
      digitalWrite(ledPin, LOW);
      delay(300);    

	  scrollScreenSaver() ;	 
	  
      if (pirState == HIGH){
		Serial.println("Motion ended!");
        pirState = LOW;
    }
  }
}

void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 100000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
    digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
    digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

void scrollScreenSaver() {
	
	lcd.clear() ;
  	lcd.setCursor(15, 0); 
	lcd.print("No Motion ");   
	lcd.setCursor(15, 1); 
	lcd.print("Waiting !");	
	
    for (int positionCounter = 0; positionCounter < 22; positionCounter++) {
		lcd.scrollDisplayLeft();
		delay(150);
    
	}
}
