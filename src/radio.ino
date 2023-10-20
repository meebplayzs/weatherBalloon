bool beginRadio() {
  if(!radio.begin()) {
    return false;
  }
  radio.openWritingPipe(addr);
  radio.stopListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(CHANNEL);
  return true;
}

void getPos(posData *gpsPacket) {
  UBX buf;
  recvUBX(&buf);
  gpsPacket->time = buf.msg.time;
  gpsPacket->lon = buf.msg.lon;
  gpsPacket->lat = buf.msg.lat;
  gpsPacket->height = buf.msg.height;
  gpsPacket->hMSL = buf.msg.hMSL;
  gpsPacket->hAcc = buf.msg.hAcc;
  gpsPacket->vAcc = buf.msg.vAcc;
}

void getSensor(sensorData *sensorPacket) {
  sensorPacket->temp = bmp.getTemperature();
  sensorPacket->alt = bmp.getPressure();
  sensorPacket->batt = analogRead(BATT_PIN);
}
