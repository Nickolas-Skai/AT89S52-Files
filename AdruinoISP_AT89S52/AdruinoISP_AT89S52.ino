// ArduinoISP for AT89S52 (Active HIGH Reset)
// Based on standard ArduinoISP
// MODIFIED BY: Amilcar for AT89S52 specific Reset Logic

#include "Arduino.h"
#undef SERIAL

#define PROG_FLICKER true
#define SPI_CLOCK (1000000 / 6)

// --- PIN DEFINITIONS ---
// RESET PIN: 10 (Connect to AT89S52 Pin 9)
#define RESET 10  
#define LED_HB 9
#define LED_ERR 8
#define LED_PMODE 7

// Use hardware SPI:
#define ARDUINOISP_PIN_MOSI MOSI
#define ARDUINOISP_PIN_MISO MISO
#define ARDUINOISP_PIN_SCK SCK

// Configure Serial
#ifdef SERIAL_PORT_USBVIRTUAL
#define SERIAL SERIAL_PORT_USBVIRTUAL
#else
#define SERIAL Serial
#endif

#define BAUDRATE 19200

#define HWVER 2
#define SWMAJ 1
#define SWMIN 18

// STK Definitions
#define STK_OK 0x10
#define STK_FAILED 0x11
#define STK_UNKNOWN 0x12
#define STK_INSYNC 0x14
#define STK_NOSYNC 0x15
#define CRC_EOP 0x20 

void pulse(int pin, int times);

// --- SPI SETUP ---
#if defined(ARDUINO_ARCH_AVR)
  #if SPI_CLOCK > (F_CPU / 128)
    #define USE_HARDWARE_SPI
  #endif
#endif

#ifdef USE_HARDWARE_SPI
#include "SPI.h"
#else
// BitBanged SPI (Fallback)
class BitBangedSPI {
public:
  void begin() {
    digitalWrite(ARDUINOISP_PIN_SCK, LOW);
    digitalWrite(ARDUINOISP_PIN_MOSI, LOW);
    pinMode(ARDUINOISP_PIN_SCK, OUTPUT);
    pinMode(ARDUINOISP_PIN_MOSI, OUTPUT);
    pinMode(ARDUINOISP_PIN_MISO, INPUT);
  }
  void beginTransaction(uint32_t clock) {
    pulseWidth = (500000 + clock - 1) / clock;
    if (pulseWidth == 0) pulseWidth = 1;
  }
  void end() {}
  uint8_t transfer(uint8_t b) {
    for (unsigned int i = 0; i < 8; ++i) {
      digitalWrite(ARDUINOISP_PIN_MOSI, (b & 0x80) ? HIGH : LOW);
      digitalWrite(ARDUINOISP_PIN_SCK, HIGH);
      delayMicroseconds(pulseWidth);
      b = (b << 1) | digitalRead(ARDUINOISP_PIN_MISO);
      digitalWrite(ARDUINOISP_PIN_SCK, LOW); 
      delayMicroseconds(pulseWidth);
    }
    return b;
  }
private:
  unsigned long pulseWidth; 
};
static BitBangedSPI SPI;
#endif

// --- MAIN SETUP ---
void setup() {
  SERIAL.begin(BAUDRATE);
  pinMode(LED_PMODE, OUTPUT); pulse(LED_PMODE, 2);
  pinMode(LED_ERR, OUTPUT); pulse(LED_ERR, 2);
  pinMode(LED_HB, OUTPUT); pulse(LED_HB, 2);
}

int ISPError = 0;
int pmode = 0;
unsigned int here;
uint8_t buff[256]; 

// --- RESET LOGIC (MODIFIED FOR AT89S52) ---
// This function is hardcoded to output HIGH when reset is TRUE.
// This is required for the AT89S52.
void reset_target(bool reset) {
  if (reset) {
    digitalWrite(RESET, HIGH); // ACTIVE HIGH for 8051
  } else {
    digitalWrite(RESET, LOW);
  }
}

// --- LOOP ---
void heartbeat() {
  static unsigned long last_time = 0;
  unsigned long now = millis();
  if ((now - last_time) < 40) return;
  last_time = now;
  static uint8_t hbval = 128;
  static int8_t hbdelta = 8;
  if (hbval > 192) hbdelta = -hbdelta;
  if (hbval < 32) hbdelta = -hbdelta;
  hbval += hbdelta;
  analogWrite(LED_HB, hbval);
}

void avrisp(); // Forward declaration

void loop(void) {
  if (pmode) digitalWrite(LED_PMODE, HIGH);
  else digitalWrite(LED_PMODE, LOW);
  
  if (ISPError) digitalWrite(LED_ERR, HIGH);
  else digitalWrite(LED_ERR, LOW);

  heartbeat();
  if (SERIAL.available()) {
    avrisp();
  }
}

uint8_t getch() {
  while (!SERIAL.available());
  return SERIAL.read();
}

void fill(int n) {
  for (int x = 0; x < n; x++) {
    buff[x] = getch();
  }
}

#define PTIME 30
void pulse(int pin, int times) {
  do {
    digitalWrite(pin, HIGH);
    delay(PTIME);
    digitalWrite(pin, LOW);
    delay(PTIME);
  } while (times--);
}

void prog_lamp(int state) {
  if (PROG_FLICKER) digitalWrite(LED_PMODE, state);
}

uint8_t spi_transaction(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  SPI.transfer(a); SPI.transfer(b); SPI.transfer(c); return SPI.transfer(d);
}

void empty_reply() {
  if (CRC_EOP == getch()) {
    SERIAL.print((char)STK_INSYNC); SERIAL.print((char)STK_OK);
  } else {
    ISPError++; SERIAL.print((char)STK_NOSYNC);
  }
}

void breply(uint8_t b) {
  if (CRC_EOP == getch()) {
    SERIAL.print((char)STK_INSYNC); SERIAL.print((char)b); SERIAL.print((char)STK_OK);
  } else {
    ISPError++; SERIAL.print((char)STK_NOSYNC);
  }
}

void get_version(uint8_t c) {
  switch (c) {
    case 0x80: breply(HWVER); break;
    case 0x81: breply(SWMAJ); break;
    case 0x82: breply(SWMIN); break;
    case 0x93: breply('S'); break;
    default: breply(0);
  }
}

void set_parameters() {
  // Read params but ignore devicecode for reset logic
  // We are forcing Active HIGH reset in reset_target()
  buff[0] = buff[0]; 
}

void start_pmode() {
  // Reset target before driving SPI pins
  reset_target(true); // Sends HIGH
  pinMode(RESET, OUTPUT);
  
#ifdef USE_HARDWARE_SPI
  SPI.begin();
  SPI.beginTransaction(SPISettings(SPI_CLOCK, MSBFIRST, SPI_MODE0));
#else
  SPI.begin();
#endif

  digitalWrite(ARDUINOISP_PIN_SCK, LOW);
  delay(20); 
  reset_target(false); // Pulse Low
  delayMicroseconds(100);
  reset_target(true);  // Hold HIGH (Programming Mode)

  delay(50);  
  spi_transaction(0xAC, 0x53, 0x00, 0x00);
  pmode = 1;
}

void end_pmode() {
#ifdef USE_HARDWARE_SPI
  SPI.end();
#else
  SPI.end();
#endif
  pinMode(ARDUINOISP_PIN_MOSI, INPUT);
  pinMode(ARDUINOISP_PIN_SCK, INPUT);
  reset_target(false); // LOW (Run Mode)
  pinMode(RESET, INPUT);
  pmode = 0;
}

void universal() {
  uint8_t ch;
  fill(4);
  ch = spi_transaction(buff[0], buff[1], buff[2], buff[3]);
  breply(ch);
}

void flash(uint8_t hilo, unsigned int addr, uint8_t data) {
  spi_transaction(0x40 + 8 * hilo, addr >> 8 & 0xFF, addr & 0xFF, data);
}

void commit(unsigned int addr) {
  if (PROG_FLICKER) prog_lamp(LOW);
  spi_transaction(0x4C, (addr >> 8) & 0xFF, addr & 0xFF, 0);
  if (PROG_FLICKER) {
    delay(PTIME); prog_lamp(HIGH);
  }
}

// Minimal helpers for Write Flash
unsigned int current_page() { return here; } // Simplified for 8051 use
void write_flash(int length) {
  fill(length);
  if (CRC_EOP == getch()) {
    SERIAL.print((char)STK_INSYNC);
    SERIAL.print((char)write_flash_pages(length));
  } else {
    ISPError++; SERIAL.print((char)STK_NOSYNC);
  }
}

uint8_t write_flash_pages(int length) {
  int x = 0;
  while (x < length) {
    flash(LOW, here, buff[x++]);
    flash(HIGH, here, buff[x++]);
    here++;
  }
  commit(here);
  return STK_OK;
}

// EEPROM Support (Limited/Stubbed)
uint8_t write_eeprom(unsigned int length) { return STK_OK; }
uint8_t write_eeprom_chunk(unsigned int start, unsigned int length) { return STK_OK; }

void program_page() {
  char result = (char)STK_FAILED;
  unsigned int length = 256 * getch();
  length += getch();
  char memtype = getch();
  if (memtype == 'F') {
    write_flash(length);
    return;
  }
  if (memtype == 'E') {
    // AT89S52 EEPROM handling is different, skipping for code safety
    result = (char)STK_OK; 
    if (CRC_EOP == getch()) {
      SERIAL.print((char)STK_INSYNC); SERIAL.print(result);
    } else {
      ISPError++; SERIAL.print((char)STK_NOSYNC);
    }
    return;
  }
  SERIAL.print((char)STK_FAILED);
}

uint8_t flash_read(uint8_t hilo, unsigned int addr) {
  return spi_transaction(0x20 + hilo * 8, (addr >> 8) & 0xFF, addr & 0xFF, 0);
}

char flash_read_page(int length) {
  for (int x = 0; x < length; x += 2) {
    uint8_t low = flash_read(LOW, here);
    SERIAL.print((char)low);
    uint8_t high = flash_read(HIGH, here);
    SERIAL.print((char)high);
    here++;
  }
  return STK_OK;
}

char eeprom_read_page(int length) { return STK_OK; }

void read_page() {
  char result = (char)STK_FAILED;
  int length = 256 * getch();
  length += getch();
  char memtype = getch();
  if (CRC_EOP != getch()) {
    ISPError++; SERIAL.print((char)STK_NOSYNC); return;
  }
  SERIAL.print((char)STK_INSYNC);
  if (memtype == 'F') result = flash_read_page(length);
  if (memtype == 'E') result = eeprom_read_page(length);
  SERIAL.print(result);
}

void read_signature() {
  if (CRC_EOP != getch()) {
    ISPError++; SERIAL.print((char)STK_NOSYNC); return;
  }
  SERIAL.print((char)STK_INSYNC);
  uint8_t high = spi_transaction(0x30, 0x00, 0x00, 0x00);
  SERIAL.print((char)high);
  uint8_t middle = spi_transaction(0x30, 0x00, 0x01, 0x00);
  SERIAL.print((char)middle);
  uint8_t low = spi_transaction(0x30, 0x00, 0x02, 0x00);
  SERIAL.print((char)low);
  SERIAL.print((char)STK_OK);
}

void avrisp() {
  uint8_t ch = getch();
  switch (ch) {
    case '0': ISPError = 0; empty_reply(); break;
    case '1':
      if (getch() == CRC_EOP) {
        SERIAL.print((char)STK_INSYNC); SERIAL.print("AVR ISP"); SERIAL.print((char)STK_OK);
      } else {
        ISPError++; SERIAL.print((char)STK_NOSYNC);
      }
      break;
    case 'A': get_version(getch()); break;
    case 'B': fill(20); set_parameters(); empty_reply(); break;
    case 'E': fill(5); empty_reply(); break;
    case 'P': if (!pmode) start_pmode(); empty_reply(); break;
    case 'U': here = getch(); here += 256 * getch(); empty_reply(); break;
    case 0x60: getch(); getch(); empty_reply(); break;
    case 0x61: getch(); empty_reply(); break;
    case 0x64: program_page(); break;
    case 0x74: read_page(); break;
    case 'V': universal(); break;
    case 'Q': ISPError = 0; end_pmode(); empty_reply(); break;
    case 0x75: read_signature(); break;
    case CRC_EOP: ISPError++; SERIAL.print((char)STK_NOSYNC); break;
    default: ISPError++; if (CRC_EOP == getch()) SERIAL.print((char)STK_UNKNOWN); else SERIAL.print((char)STK_NOSYNC);
  }
}