
#include <Wire.h>
#include <DS3231.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 8;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

DS3231 clock;
RTCDateTime dt;


void setup( )
{
  Serial.begin( 9600);

  Serial.println("Initialize DS3231");

  clock.begin();

  clock.setDateTime(__DATE__, __TIME__);
}




static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if ( millis( ) - measurement_timestamp > 3000ul )
  {
    if ( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return ( true );
    }
  }

  return ( false );
}



void loop( )
{
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */


  dt = clock.getDateTime();
  Serial.print( "T = " );
  Serial.print( temperature, 1 );
  Serial.print( " deg. C, H = " );
  Serial.print( humidity, 1 );
  Serial.println( "%" );
  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  delay(1000);
}
