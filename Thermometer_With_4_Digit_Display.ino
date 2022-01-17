#include "SevSeg.h"
#include <dht_nonblocking.h>
#define tempsensor_TYPE DHT_TYPE_11
static const int tempsensor_PIN = 22;
DHT_nonblocking tempsensor( tempsensor_PIN, tempsensor_TYPE );
SevSeg sevseg;



void setup() {
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
}
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( tempsensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}
void loop() {
  
  float temperature;
  float humidity;

  
  if( measure_environment( &temperature, &humidity ) == true )
  {
      //Initializes the segment display
  }
  static unsigned long timer = millis(); //Timer for refreshing display 

  if (millis() >= timer) {
    timer += 300;
    int temp = (int)temperature;
    sevseg.setNumber(temp, 0);
   
    
  }

  sevseg.refreshDisplay();

}
