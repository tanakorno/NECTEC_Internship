#include "True_NB_bc95.h"
#include "AltSoftSerial.h"

AltSoftSerial Serial2;
True_NB_bc95 modem;

String userid = "002651";                         /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key    = "df1uen82rhgm";                   /*IoTtweet registered device key in "MY IOT Garage"*/

String private_tweet = "TRUE NB-IoT";             /*Your private tweet meassage to dashboard*/
String public_tweet = "Data from DHT22 sensor";   /*Your public tweet message to dashboard*/

long start = 0;
char sock[] = "0\0";

#define LEDPIN 5

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  delay(3000);

  Serial.println("Starting...");

  modem.init(Serial2);
  modem.initModem();

  Serial.println( "IMEI = " + modem.getIMEI() );
  Serial.println( "IMSI = " + modem.getIMSI() );

  while (!modem.register_network());
  delay(1000);

  Serial.println( modem.check_ipaddr() );
  modem.create_UDP_socket(4700, sock);

  setupGPS();
}

void loop() {
  if (millis() - start > 5000) {
    start = millis();

    Serial.println("Interval");

    readData();

    digitalWrite(LEDPIN, !getSat());

    modem.WriteDashboardIoTtweet(userid, key, getLat(), getLng(), getSat(), random(100.00), private_tweet, public_tweet);
  }
}
