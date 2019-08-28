/**
 * Capture-The-Flag ShittyAddon Firmware
 * Copyright (C) 2019, Uri Shaked
 * Released under the MIT license.
 */

// LED is connected to PB1

#include <avr/boot.h>
#include <TinyWire.h>

uint16_t target = 0;
uint16_t flash_addr = 0x400;
uint16_t flash_value = 0x20;

// SECRET will be replaced with the actual flag:
const char flag[] PROGMEM = "$FLAG:SECRET"; 

void setup() {
  TinyWire.begin(0x23);
  TinyWire.onReceive(onI2CReceive);
  TinyWire.onRequest(onI2CRequest);
  for (uint8_t ch = 0; flag[ch]; ch++) {
    flash_value ^= flag[ch];
  }  
}

void loop() {
  bool erase = flash_addr & 0x8000;
  flash_addr &= 0x1fff;
  if (flash_addr >= 0x800) {
    cli();
    if (erase) {
      boot_page_erase_safe(flash_addr);
    } else {
      for (uint8_t i = 0; i < SPM_PAGESIZE; i += 2, flash_value += 2) {
        boot_page_fill_safe(flash_addr + i, *(uint16_t*)flash_value);      
      }
      boot_page_write(flash_addr);
    }
    boot_spm_busy_wait();
    flash_addr = 0;
    sei();
  }
}

void onI2CReceive(int cnt) {
  target = TinyWire.read();
  while (TinyWire.available()) {
    *(uint8_t*)target++ = TinyWire.read();    
  }
}

void onI2CRequest() {
  TinyWire.send(target);
  uint8_t* addr = (target++) & 0x1fff;
  TinyWire.send((target & 0x8000) ? pgm_read_byte(addr): *addr);
}
  
