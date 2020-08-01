
////////////////////////////////////////////////////////////
//                                                        //
//    HomeSpan: A HomeKit implementation for the ESP32    //
//    ------------------------------------------------    //
//                                                        //
// Example 6: One working on/off LEDs and one working     //
//            dimmable LED, both based on the LightBulb   //
//            Service                                     //
//                                                        //
////////////////////////////////////////////////////////////


#include "HomeSpan.h" 
#include "DEV_LED.h"          

void setup() {

  // Example 6 changes Example 5 so that LED #2 is now dimmable, instead of just on/off.  This requires us to create a new
  // derived Service we will name "DEV_DimmableLED"  Instead of creating a new file to store this definition, we will simply
  // tack it on to the end of the DEV_LED.h file that includes the code we created in Example 5 to control an on/off LED.
  // Grouping similar-style Services in one ".h" file makes it easier to organize your custom devices.

  // As usual, all previous comments have been deleted and only new changes from the previous example are shown.

  // NOTE: The Arduino/ESP32 code base does not include the function analogWrite() which is typically used to create a PWM
  // output to drive the brightness of an LED.  The ESP32 code base itself includes a set of functions to create PWM output
  // and the ESP32 chip has built-in PWM functionality specifically for this purpose.  There are numerous libraries
  // you can download that mimics or reproduces analogWrite() in some form or another.  HomeSpan conveniently comes with
  // it own version of a wrapper around the ESP32 PWM classes that make it very easy to define PWM "channel," attach a pin,
  // and set the PWM level (or duty cycle) from 0-100%.  These functions are encapsualted in the PwmPin class, as defined in
  // extras/PwmPin.h.  We will include this file in our updated DEV_LED.h for use with DEV_DimmableLED.
  
  Serial.begin(115200);

  homeSpan.begin(Category::Lighting,"HomeSpan LEDs");
  
  new SpanAccessory(); 
  
    new Service::AccessoryInformation(); 
      new Characteristic::Name("LED #1"); 
      new Characteristic::Manufacturer("HomeSpan"); 
      new Characteristic::SerialNumber("123-ABC"); 
      new Characteristic::Model("20mA LED"); 
      new Characteristic::FirmwareRevision("0.9"); 
      new Characteristic::Identify();            
      
    new Service::HAPProtocolInformation();      
      new Characteristic::Version("1.1.0");     

    new DEV_LED(16);                // create an on/off LED attached to pin 16 (same as in Example 5)

  new SpanAccessory(); 
  
    new Service::AccessoryInformation();    
      new Characteristic::Name("LED #2");    
      new Characteristic::Manufacturer("HomeSpan"); 
      new Characteristic::SerialNumber("123-ABC");  
      new Characteristic::Model("20mA LED");   
      new Characteristic::FirmwareRevision("0.9");  
      new Characteristic::Identify();               
      
    new Service::HAPProtocolInformation();          
      new Characteristic::Version("1.1.0");         
  
    new DEV_DimmableLED(0,17);        // NEW! create a dimmable LED attached to pin 17 using PWM channel 0.  See new code at end of DEV_LED.h

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();
  
} // end of loop()