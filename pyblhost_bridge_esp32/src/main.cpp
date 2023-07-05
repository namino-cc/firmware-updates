//
// Namino ROSSO / ARANCIO : serial bridge
//

#include <Arduino.h>
#include <HardwareSerial.h>

#define BAUD_RATE 115200
// prog pins
#define NM_BOOT_MODE_PIN    47
#define NM_TX_PIN           17
#define NM_RX_PIN           18
#define NM_RESET_PIN        48

HardwareSerial Serial_ISP_NM(2); // UART #2

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  delay(5000);
  Serial.println();
  Serial.println("===============================================");
  Serial.println("##  UPLOAD NAMINO ROSSO / ARANCIO FIRMWARE   ##");
  Serial.println("===============================================");
  Serial.println();
  delay(2000);

  Serial.print("NM_RX_PIN: ");
  Serial.println(NM_RX_PIN);
  Serial.print("NM_TX_PIN: ");
  Serial.println(NM_TX_PIN);
  Serial.print("BRIDGE_BAUD_RATE: ");
  Serial.println(BAUD_RATE);

  Serial_ISP_NM.begin(BAUD_RATE, SERIAL_8N1, NM_RX_PIN, NM_TX_PIN); // RX, TX NAMINO ROSSO / ARANCIO

  Serial.println("upload sequence: start");
  pinMode(NM_BOOT_MODE_PIN, OUTPUT);
  pinMode(NM_RESET_PIN, OUTPUT);
  digitalWrite(NM_BOOT_MODE_PIN, HIGH);
  digitalWrite(NM_RESET_PIN, !HIGH);
  delay(100);
  digitalWrite(NM_BOOT_MODE_PIN, LOW);
  delay(100);
  digitalWrite(NM_RESET_PIN, !LOW);
  delay(100);
  digitalWrite(NM_RESET_PIN, !HIGH);
  Serial.println("upload sequence: wait");
}

// reverse a byte
unsigned char bitrev8_1(unsigned char bits) {
	unsigned char tmp=0;

	// bit reversing, msb to lsb
	tmp |= (bits & 0x80)?0x01:0;
	tmp |= (bits & 0x40)?0x02:0;
	tmp |= (bits & 0x20)?0x04:0;
	tmp |= (bits & 0x10)?0x08:0;
	tmp |= (bits & 0x08)?0x10:0;
	tmp |= (bits & 0x04)?0x20:0;
	tmp |= (bits & 0x02)?0x40:0;
	tmp |= (bits & 0x01)?0x80:0;
	return tmp;
}

// void loop() {
//   //uint8_t buffer[2] = {0xaa, 0xaa};

//   //Serial_ISP_NM.write(0x80);
//   //Serial_ISP_NM.write(0x00);

//   //Serial_ISP_NM.write(buffer, size_t(buffer));

//   uint8_t b0 = bitrev8_1(0x5a);
//   uint8_t b1 = bitrev8_1(0xa6);
//   Serial_ISP_NM.write(b0);
//   Serial_ISP_NM.write(b1);
//   delay(10);
// }

void loop() {
  // put your main code here, to run repeatedaly:
  if (Serial.available() > 0) {
    //u_int8_t c = Serial.read();
    //Serial.println(c);
    Serial_ISP_NM.write(Serial.read());
    //Serial.print("TX: ");
    //Serial.println(c);
  }
  if (Serial_ISP_NM.available() > 0) {
    //u_int8_t c = Serial_ISP_NM.read();
    Serial.write(Serial_ISP_NM.read());
    //Serial.print("RX: ");
    //Serial.println(c);
  }
}