#include <SoftwareSerial.h>
#include <RF24.h>
#include <LowPower.h>
#include <Seeed_BMP280.h>
#include <avr/wdt.h>
#define CE_PIN A1
#define CS_PIN A0
#define GPS_RX 6
#define GPS_TX 7
#define GSM_RX 8
#define GSM_TX 9
#define CHANNEL 82
#define BATT_PIN A2
const uint8_t addr[] = "abcde"; 
BMP280 bmp;
RF24 radio(CE_PIN, CS_PIN, 1000000);
SoftwareSerial gps(GPS_RX, GPS_TX);
SoftwareSerial gsm(GSM_RX, GSM_TX);
typedef struct {
  uint16_t header;
  uint8_t cls;
  uint8_t id;
  uint16_t len;
  uint32_t time;
  int32_t lon;
  int32_t lat;
  int32_t height;
  int32_t hMSL;
  uint32_t hAcc;
  uint32_t vAcc;
} __attribute__((packed)) UBXMsg;

typedef union {
  uint8_t buf[34];
  UBXMsg msg;
} __attribute__((packed)) UBX;

typedef struct {
  uint8_t id = 0;
  uint32_t time;
  int32_t lon;
  int32_t lat;
  int32_t height;
  int32_t hMSL;
  uint32_t hAcc;
  uint32_t vAcc;
} __attribute__((packed)) posData;

typedef struct {
  uint8_t id = 1;
  float temp;
  uint32_t alt;
  int batt;
} __attribute__((packed)) sensorData;

bool beginRadio();
bool recvUBX(UBX *buffer);
void getPos(posData *gpsPacket);
void getSensor(sensorData *sensorPacket);
void sendGSM(posData *gpsPacket, sensorData *sensorPacket);
