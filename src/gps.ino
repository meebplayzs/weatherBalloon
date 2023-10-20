bool recvUBX(UBX *buffer) {
  uint8_t c = 0;
  unsigned long currentMillis = millis();
  gps.listen();
  while(c != 0xB5) {
    while(gps.available() == 0) {
      if(millis() - currentMillis > 1500) {
        return false;
      }
    }
    c = gps.read();
  }
  for(uint8_t i = 0; i < sizeof(buffer->buf); i++) {
    currentMillis = millis();
    buffer->buf[i] = c;
    while(gps.available() == 0) {
      if(millis() - currentMillis > 1500) {
        return false;
      }
    }
    c = gps.read();
  }
  gps.stopListening();
  return true;
}
