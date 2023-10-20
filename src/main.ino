posData gpsPacket;
sensorData sensorPacket;
void setup() {
  gps.begin(9600);
  gps.stopListening();
  gsm.begin(9600);
  gsm.stopListening();
  pinMode(BATT_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  wdt_enable(WDTO_4S);
  bmp.init();
  beginRadio();
  getPos(&gpsPacket);
  getSensor(&sensorPacket);
  radio.write(&gpsPacket, sizeof(posData));
  radio.write(&sensorPacket, sizeof(sensorData));
  if(bmp.calcAltitude(sensorPacket.alt) < 2500) {
    sendGSM(&gpsPacket, &sensorPacket);
  } else {
    gsm.println(F("AT+CFUN=0"));
  }
  gsm.flush();
  wdt_disable();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_ON);  
}
