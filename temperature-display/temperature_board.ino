//Download DHT, SevSeg from manage libraries
#include <DHT.h>
#include <SevSeg.h>

#define DHTPIN 12 // Dx not GPIO
#define DHTTYPE DHT22

#define DIGIT1 10
#define DIGIT2 9
#define DIGIT3 7

#define SEGMENTA 13
#define SEGMENTB 8
#define SEGMENTC 5
#define SEGMENTD 3
#define SEGMENTE 2
#define SEGMENTF 11
#define SEGMENTG 6
#define SEGMENTDP 4

DHT dht(DHTPIN, DHTTYPE);
SevSeg sevseg;
int startTime;
float temperature;

void setup() {
  Serial.begin(115200);
  log("SETUP :: Serial complete");

  dht.begin();
  log("SETUP :: DHT Begin Done");

  byte numDigits = 3;
  byte digitPins[] = {DIGIT1, DIGIT2, DIGIT3};
  byte segmentPins[] = {SEGMENTA,SEGMENTB, SEGMENTC, SEGMENTD, SEGMENTE, SEGMENTF, SEGMENTG, SEGMENTDP};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_CATHODE;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  log("SETUP :: Seven Seg Configured");

  startTime = millis();
  log("SETUP :: Start time configured");
  
  log("SETUP :: Setup Complete.");
}


void loop() 
{
  float temp = getTemperature();

  showTemp(temp);
  
}


/*
 * Logs messages
 */
void log(String message)
{
  Serial.println(message);
}


/*
 * Show Temperature on 4-digit 7 segment display
 */
void showTemp(float temperature)
{
  sevseg.setNumberF(temperature,1);
  sevseg.refreshDisplay();
}

/* 
 *  Gets the temperature (handles refreshing)
 */
 float getTemperature()
 {
  int now = millis();

  // Has 0.7 seconds elapsed? (Max read time is 0.7 seconds)
  if (now - startTime > (0.7 * 1000)){
    startTime = now;
    temperature = dht.readTemperature();
    log("Temp = " + String(temperature) + "*C");
  }
  return temperature;
 }
