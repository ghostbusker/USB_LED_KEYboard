/*
* Author: ghostbusker 6/28/2019
* Project Name: USB_LED_KEYboard by ghostbusker
* Description: USB keyboard shortcuts for TM1638 module(LED & KEY)
* Thanks to Gavin Lyons for the TM1638Plus library and demo code 
* URL: https://github.com/gavinlyonsrepo/TM1638plus
*/

#include <Keyboard.h>
#include <TM1638plus.h>

// GPIO I/O pins on the Arduino connected to strobe, clock, data, 
// Change these to match your board
#define  STROBE_TM 2
#define  CLOCK_TM 3
#define  DIO_TM 4

//Constructor object
TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM);

void setup() {
   // Test 0 reset test
   tm.setLED(0, 1);
   delay(250);
   tm.reset();
  
   // Setup serial output for debugging
   Serial.begin(9600);  
      
   // Test Brightness and reset
   for (uint8_t brightness = 0; brightness < 8; brightness++)
   {
         tm.brightness(brightness);
         tm.displayText("00000000");
         delay(500);
   }
   tm.reset();

   // restore low brightness
   tm.brightness(0x01);
  
   //Test ASCII display pi
   tm.displayASCIIwDot(0, '3');
   tm.displayASCII(1, '1');
   tm.displayASCII(2, '4');
   tm.displayASCII(3, '1');
   tm.displayASCII(4, '5');
   tm.displayASCII(5, '9');
   tm.displayASCII(6, '2');
   tm.displayASCII(7, '6');
   delay(750);

   // enable USB Keyboard
   Keyboard.begin();

   //initialization complete
   tm.displayText("initDONE");
   
}


void loop() {
   // read buttons
   uint8_t buttons = tm.readButtons();
   
   // turn on led for pressed button
   doLEDs(buttons);
   
   // send keystrokes to USB host for each button press
   if (buttons == 1) {
       Keyboard.press(KEY_LEFT_CTRL);
       delay(150);
       Keyboard.press(KEY_RIGHT_SHIFT);  
       delay(150);
       Keyboard.press(KEY_ESC);  
       delay(150);
       Keyboard.releaseAll();
       tm.displayText("taskN7an");
       delay(750);
   }   
   if (buttons == 2) {
       Keyboard.press(KEY_F1);
       delay(150);
       Keyboard.releaseAll();
       tm.displayText("Func F1 ");
       delay(750);
   }
   if (buttons == 4) {
       Keyboard.press(KEY_LEFT_GUI);
       delay(150);
       Keyboard.press('r');
       delay(150);
       Keyboard.releaseAll();
       delay(150);
       Keyboard.println("http://google.com");
       tm.displayText("Google  ");
       delay(750);  
   }
   if (buttons == 8) {
       Keyboard.press(KEY_LEFT_GUI);
       delay(150);
       Keyboard.press('r');
       delay(150);
       Keyboard.releaseAll();
       delay(150);
       Keyboard.println("http://ghostbusker.com");
       tm.displayText("GHSTBSKR");
       delay(750);  
   }
   if (buttons == 16) {
       Keyboard.press(KEY_LEFT_GUI);
       delay(150);
       Keyboard.press('r');
       delay(150);
       Keyboard.releaseAll();
       delay(150);
       Keyboard.println("http://hackaday.com");
       tm.displayText("HACKADAY");
       delay(750);  
   }
   if (buttons == 32) {
       Keyboard.press(KEY_LEFT_ALT);
       delay(150);
       Keyboard.press(KEY_F4);
       delay(150);
       Keyboard.releaseAll();
       tm.displayText("ALT  F4 ");
       delay(750);  
   }
   if (buttons == 64) {
       Keyboard.press(KEY_PAGE_DOWN);
       delay(150);
       Keyboard.releaseAll();
       tm.displayText("PageDOWN");
       delay(750);  
   }
   if (buttons == 128) {
       Keyboard.press(KEY_PAGE_UP);
       delay(150);
       Keyboard.releaseAll();
       tm.displayText("Page UP ");
       delay(750);  
   }

   //Send button press value to serial for debugging
   if (buttons != 0) {
       Serial.println(buttons); 
   }
   
   // display default message
   tm.displayText("HACK THE");
   delay(750);
   tm.displayText(" PLANET ");
   delay(750);
   
}

// scans the individual bits of value
void doLEDs(uint8_t value) {
  for (uint8_t position = 0; position < 8; position++) {
    tm.setLED(position, value & 1);
    value = value >> 1;
  }
}
