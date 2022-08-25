
/* Overall kode transmite & receive sama, hanya beda di siapa yang transmit dulu
  dan siapa yang receive dulu. Hanya butuh reset di Transmitter saja, Receiver ndak perlu.

  update : Maljum 05 Agustus 2022
  1. ganti library dari VirtualWire >>>>> Radiohead lagi untuk simplifikasi code (VW lebih banyak sintak, mumet).
  2. sudah bisa baca dan kirim data String (String to char while transmit, then char to String after receive data)

  note : 
  1. karena sistemnya bukan client server, pengalamatan receiver menggunkana flag b21 = rxUnitIndex; (1, 2, 3 ..dst)
  
  @Harun Ar Rasyid.
*/


#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

int variable = 1;
int condition = 1;
String myString, b20, b21, data;
void setup() {
  // put your setup code here, to run once:

  //   Serial.begin(9600);    // Debugging only
  Serial.println("setup");

  Serial.begin(9600);    // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{
  rfCom(); // komunikasi half duplex rf
//  rxStatus(); // status unit receiver nano
}

void rfCom() {
  uint8_t buf[20];
  uint8_t buflen = buf;


  if ( variable == condition ) // KIRIM
  {
    const char *msg = "nuwun sewu";

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(200);
    variable = 0;

  }

  if ( variable == 0 ) // TERIMA
  {
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      Serial.print("Got: ");
      data = (char*)buf;
      Serial.println(data);
      delay(200);
      variable = 1;
    }
  }
}
