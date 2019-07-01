/*LRD-BASED LIGHTING CONTROL SYSTEM
 * BY : COLLINS K. MUTAI
 * EC/1029/17
 * BEng(Electrical & Electronics)
 * ECE 590 : ENGINEERING PROJECT II
 * FINAL YEAR PROJECT
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // LCD I2C Library

LiquidCrystal_I2C lcd(0x3F,20,4); // Setting up the LCD

const int ldr1_led = A1;  //LDR that controls the LED in an ANALOG form allowing DIMMING (Situated inside the building)
const int ldr2_bulb = A2; //LDR that controls the BULB in digital form allowing it to be either ON/OFF.
const int led = 7; // LED that represents all lighting inside the building that requires dimming
const int bulb_relay = 53; // BULB that is connected using RELAY 
                           //: This makes it possible to control 240V AC using 5VDC

float ldr1_Value = 0;   
float ldr2_Value = 0;     
float ldr1_Output = 0;        // value output to the PWM (analog out)
float ldr2_Output = 0;

float bulb_brightPercent;
float led_brightPercent;

void setup() {
  Serial.begin(9600);

  lcd.init();    // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" LIGHTING CONTROL ");
  lcd.setCursor(0,1);
  lcd.print("      SYSTEM      ");
  lcd.setCursor(8,2);
  lcd.print("BY");
  lcd.setCursor(0,3);
  lcd.print("   COLLINS MUTAI   ");

  pinMode(led, OUTPUT);
  pinMode(bulb_relay, OUTPUT);

  delay(5000);
}

void loop() {
  /*
  LDR 1 && LED
  */
  ldr1_Value = analogRead(ldr1_led);
  ldr1_Output = map(ldr1_Value, 1023, 0, 0, 255); // Setting the LDR Values to fit the Min - Max
  analogWrite(led, ldr1_Output); // ACTUAL DIMMING
  led_brightPercent = (ldr1_Value / 1024) * 100;
  /*
  Serial.print("LDR1 = ");
  Serial.print(ldr1_Value);
  Serial.print("\t LEDoutput = ");
  Serial.println(ldr1_Output);
  Serial.print("\t Percentage = ");
  Serial.print(led_brightPercent);
  Serial.println(" %");
  */

  dispPercent();

  /*
  LDR2 & BULB
  */
  ldr2_Value = analogRead(ldr2_bulb);
  ldr2_Output = map(ldr2_Value, 1023, 0, 0, 255);
  bulb_brightPercent = (ldr2_Value / 1024) * 100;
  /*
  Serial.print("LDR2 = ");
  Serial.print(ldr2_Value);
  Serial.print("\t Percentage = ");
  Serial.print(bulb_brightPercent);
  Serial.println(" %");
  */

  if (bulb_brightPercent < 10) {
    digitalWrite(bulb_relay, LOW);
    dispPercent();
    lcd.setCursor(3,2);
    lcd.print("** Bulb ON **");
  } else {
    digitalWrite(bulb_relay, HIGH);
    dispPercent();
    lcd.setCursor(3,2);
    lcd.print("** Bulb OFF **");
  }
  delay(500);
}

void dispPercent(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Room Luminous=");
    lcd.print(led_brightPercent);
    lcd.print("%");

    lcd.setCursor(0,1);
    lcd.print("Out Luminous= ");
    lcd.print(bulb_brightPercent);
    lcd.print("%");

    lcd.setCursor(0,3);
    lcd.print("SaveEnergy&Resources");
  }

  /*LRD-BASED LIGHTING CONTROL SYSTEM
 * BY : COLLINS K. MUTAI
 * EC/1029/17
 * BEng(Electrical & Electronics)
 * ECE 590 : ENGINEERING PROJECT II
 * FINAL YEAR PROJECT
*/
