#include <WS2812.h>

#define NUM_LEDS 4
#define COLORS_PER_LED 3
#define INTERVAL 500

#if (NUM_LEDS*COLORS_PER_LED) > 255
#error "Too many LEDS*COLORS: can not be larger than 255."
#endif

__xdata uint8_t ledData[NUM_LEDS][COLORS_PER_LED];
__xdata uint16_t ledRaw[COLORS_PER_LED];
__xdata uint8_t ledErr[NUM_LEDS][COLORS_PER_LED];
uint16_t hue = 0, brightness = 65535;
uint8_t ledState = LOW;
unsigned long previousMillis;

// This function takes a linear value for brightness and squares it then takes the top 16 bits.
// Effectively this takes the linear falue in fixed 8.8 precision, squares it to get 16.16 and then
// coorects for the moved fractional point with a right shift of 16.
uint16_t sq_map(uint16_t x, uint16_t fl, uint16_t fh, uint16_t tl, uint16_t th){
  uint32_t a;
  
  a = map(x, fl, fh, tl, th);
  a = a * a;
  a = a >> 16;
  return a;
}

// Convert hue and brightness values into a gamma corrected (2.0) set of R, G, and B values.
void set_pixel_for_GRB_LED_color(__xdata uint16_t *ptr, uint16_t hue, uint16_t brightness){
//  __xdata uint16_t *ptr = (base) + ((index)*3);
  if(hue < 21846){
    ptr[0] = sq_map(hue, 0, 21845, brightness, 0);
    ptr[1] = sq_map(hue, 0, 21845, 0, brightness);
    ptr[2] = 0;
  }else{
    if(hue < 43690){
      ptr[0] = 0;
      ptr[1] = sq_map(hue, 21846, 43689, brightness, 0);
      ptr[2] = sq_map(hue, 21846, 43689, 0, brightness);
    }else{
      ptr[0] = sq_map(hue, 43690, 65535, 0, brightness);
      ptr[1] = 0;
      ptr[2] = sq_map(hue, 43690, 65535, brightness, 0);
    }
  }
}

void setup() {
  // Pin 3.4 is the WS2812B output
  pinMode(34, OUTPUT);
  // Pin 3.0 connects to the onboard blue LED on the WeAct studio CH552 board
  // it will serve as a heartbeat indication.  It will stop beating when the
  // light show is over.
  pinMode(30, OUTPUT);
  digitalWrite(30,LOW);
  previousMillis = millis();
}

void loop() {
  unsigned long currentMillis;

  // Loop over the # of LEDs and calculate new brightness values for them
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    set_pixel_for_GRB_LED_color(ledRaw, (hue++ + 4095 * i), brightness);
    // Loop over the colors in each LED and perform dither by adding is the brightness
    // error from the last time it was displayed.  Save the new error for next time.
    for (uint8_t j = 0; j < 3; j++){
      ledRaw[j] += ledErr[i][j];
      ledData[i][j] = ledRaw[j] >> 8;
      ledErr[i][j] = ledRaw[j] & 0x00ff;
    }
  }
    neopixel_show_P3_4(ledData, NUM_LEDS*COLORS_PER_LED);

  // Count down from 1834.980 seconds and slowly decrease the brightness value from 65535 to 0
  // Halt when the time is up.
  currentMillis = millis();
  if(currentMillis < 1834980)
    brightness = 65535 - (currentMillis / 28);
  else
    while(1){};

  // Blink P3.0 until we halt
  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }
  digitalWrite(30,ledState);
}