#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define SS_PIN 10
#define RST_PIN 9
Adafruit_SSD1306 display(OLED_RESET);
MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp;
unsigned long CardUIDeEPROMread[] =
	{
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,
	30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49
	};

int ARRAYindexUIDcard;
int EEPROMstartAddr;
int LockSwitch;
int PiezoPin = 14;
int RelayPin = 2;
int carState = 0;

void setup(){   
  // Serial.begin(9600); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(PiezoPin, OUTPUT);
  pinMode(RelayPin, OUTPUT);
  digitalWrite(PiezoPin, HIGH),delay(100),digitalWrite(PiezoPin, LOW);
  DisplayWAiT_CARD();
  EEPROMreadUIDcard();
}

void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec*256+uidDecTemp;  
  }  

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);

  if (uidDec == 2363141153 || LockSwitch > 0)EEPROMwriteUIDcard();

  if (LockSwitch == 0)
  {
    for(ARRAYindexUIDcard = 0; ARRAYindexUIDcard <= 49; ARRAYindexUIDcard++) 
    {
      if (CardUIDeEPROMread[ARRAYindexUIDcard] > 0)
      {
        if (CardUIDeEPROMread[ARRAYindexUIDcard] == uidDec)
        {
          CommandsCARD();
          break;
        }
      }
    }   
    if (ARRAYindexUIDcard == 50)display.println("NOT  Found CARD-UID"),display.println(uidDec),display.display();
    delay(2000);    
    ARRAYindexUIDcard = 0;
    DisplayWAiT_CARD();
  }
} 

void EEPROMwriteUIDcard() {

  if (LockSwitch == 0)
  {
    display.println("   START    RECORD   Card UID   CLIENT"); 
    display.display(); 
    for(int i = 0; i <= 2; i++)delay(500),digitalWrite(PiezoPin, HIGH),delay(500),digitalWrite(PiezoPin, LOW);
  } 

  if (LockSwitch > 0)
  {
    if (uidDec == 2363141153)
    {
      display.println("   SKIP     RECORD   "); 
      display.setTextSize(3);
      display.setCursor(40,40);
      display.println(EEPROMstartAddr/5);
      display.display();

      EEPROMstartAddr += 5;

      digitalWrite(PiezoPin, HIGH),delay(200),digitalWrite(PiezoPin, LOW);
    }
    else
    {
      EEPROM.write(EEPROMstartAddr, uidDec & 0xFF); 
      EEPROM.write(EEPROMstartAddr + 1, (uidDec & 0xFF00) >> 8); 
      EEPROM.write(EEPROMstartAddr + 2, (uidDec & 0xFF0000) >> 16); 
      EEPROM.write(EEPROMstartAddr + 3, (uidDec & 0xFF000000) >> 24);

      delay(10);

      display.println("RECORD OK! IN MEMORY "); 
      display.setTextSize(3);
      display.setCursor(50,40);
      display.println(EEPROMstartAddr/5);
      display.display();

      EEPROMstartAddr += 5;
      for(int i = 0; i <= 40; i++)delay(5),digitalWrite(PiezoPin, HIGH),delay(5),digitalWrite(PiezoPin, LOW);
    }   
  }

  LockSwitch++;

  if (EEPROMstartAddr/5 == 50)
  {
    delay(2000);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(3);
    display.setCursor(0,0); 
    display.println("RECORD FINISH"); 
    display.display();


    digitalWrite(PiezoPin, HIGH),delay(3000),digitalWrite(PiezoPin, LOW);

    EEPROMstartAddr = 0;   
    uidDec = 0;
    ARRAYindexUIDcard = 0;

    EEPROMreadUIDcard();
  } 
}

void EEPROMreadUIDcard()
{
  for(int i = 0; i <= 49; i++)
  {
    byte val = EEPROM.read(EEPROMstartAddr+3);   
    CardUIDeEPROMread[ARRAYindexUIDcard] = (CardUIDeEPROMread[ARRAYindexUIDcard] << 8) | val; 
    val = EEPROM.read(EEPROMstartAddr+2); 
    CardUIDeEPROMread[ARRAYindexUIDcard] = (CardUIDeEPROMread[ARRAYindexUIDcard] << 8) | val; 
    val = EEPROM.read(EEPROMstartAddr+1);
    CardUIDeEPROMread[ARRAYindexUIDcard] = (CardUIDeEPROMread[ARRAYindexUIDcard] << 8) | val; 
    val = EEPROM.read(EEPROMstartAddr); 
    CardUIDeEPROMread[ARRAYindexUIDcard] = (CardUIDeEPROMread[ARRAYindexUIDcard] << 8) | val;

    ARRAYindexUIDcard++;
    EEPROMstartAddr +=5;
  }

  ARRAYindexUIDcard = 0;
  EEPROMstartAddr = 0; 
  uidDec = 0;
  LockSwitch = 0;
  DisplayWAiT_CARD();        
}

void DisplayWAiT_CARD()
{
  display.clearDisplay();
  display.setRotation(2);
  display.setTextColor(WHITE);
  display.setTextSize(4);
  display.setCursor(0,0);
  display.println("MAN");
  display.setCursor(25,35);
  display.println("GUST");
  display.display();
}

void CommandsCARD()
{
  display.print("Hi ");

  if (ARRAYindexUIDcard == 0 && carState == 0)
  {
	display.println("Owner");
	digitalWrite(RelayPin, HIGH);
	carState = 1;
  }

  else if (ARRAYindexUIDcard == 0 && carState == 1)
  {
	display.println("Owner");
	digitalWrite(RelayPin, LOW);
	carState = 0;
  }

  else if (ARRAYindexUIDcard == 1 && carState == 0)
  {
	display.println("Owner");
	digitalWrite(RelayPin, HIGH);
	carState = 1;
  }

  else if (ARRAYindexUIDcard == 1 && carState == 1)
  {
	display.println("Owner");
	digitalWrite(RelayPin, LOW);
	carState = 0;
  }

  else if (ARRAYindexUIDcard == 2 && carState == 0)
  {
	display.println("Owner");
	digitalWrite(RelayPin, HIGH);
	carState = 1;
  }

  else if (ARRAYindexUIDcard == 2 && carState == 1)
  {
	display.println("Owner");
	digitalWrite(RelayPin, LOW);
	carState = 0;
  }

  else if (ARRAYindexUIDcard == 3 && carState == 0)
  {
	display.println("Owner");
	digitalWrite(RelayPin, HIGH);
	carState = 1;
  }

  else if (ARRAYindexUIDcard == 3 && carState == 1)
  {
	display.println("Owner");
	digitalWrite(RelayPin, LOW);
	carState = 0;
  }

  display.setCursor(0,20);
  display.println(CardUIDeEPROMread[ARRAYindexUIDcard]);
  display.setCursor(40,40);
  display.setTextSize(3);
  display.println(ARRAYindexUIDcard);
  display.display();

  for(int i = 0; i <= ARRAYindexUIDcard; i++)delay(20),digitalWrite(PiezoPin, HIGH),delay(20),digitalWrite(PiezoPin, LOW);
  delay(1);
}

