// rf69 demo tx rx.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client
// with the RH_RF69 class. RH_RF69 class does not provide for addressing
// or reliability, so you should only use RH_RF69 if you do not need the
// higher level messaging abilities.
// It is designed to work with the other example RadioHead69_RawDemo_RX.
// Demonstrates the use of AES encryption, setting the frequency and
// modem configuration.

#include <SPI.h>
#include <RH_RF69.h>
#include "main.h"
#include "Arduino.h"

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 434.0

// Custom wiring
#define RFM69_CS     TELE_CS  // "B"
#define RFM69_INT    TELE_INT  // "C"
#define RFM69_RST    TELE_RST  // "A"
#define RFM69_IRQN   digitalPinToInterrupt(RFM69_INT)


// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

void lora_init(void);
void lora_transmit(void);
