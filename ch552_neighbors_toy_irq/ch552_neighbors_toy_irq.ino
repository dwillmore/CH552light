#include <WS2812.h>

#define NUM_LEDS 4
#define COLOR_PER_LEDS 3
#define NUM_BYTES (NUM_LEDS*COLOR_PER_LEDS)

#define interval 500

#if NUM_BYTES > 255
#error "NUM_BYTES can not be larger than 255."
#endif

__xdata uint8_t ledData[NUM_BYTES];
uint16_t hue = 0, brightness = 65535;
volatile uint8_t ledState = LOW;
unsigned long previousMillis;

void Timer2Interrupt(void)  __interrupt {
//  if (ledState == LOW) {
//      ledState = HIGH;
//   } else {
//      ledState = LOW;
//    }
//  digitalWrite(30,ledState);
}

uint8_t sq_map(uint16_t x, uint16_t fl, uint16_t fh, uint16_t tl, uint16_t th){
  uint32_t a;
  
  a=map(x, fl, fh, tl, th);
  a=a*a;
  a=a >> 24;
  return a;
}
void set_pixel_for_GRB_LED_color(__xdata uint8_t *base, uint8_t index, uint16_t hue, uint16_t brightness){
  __xdata uint8_t *ptr = (base) + ((index)*3);
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
  pinMode(34, OUTPUT);
  pinMode(30, OUTPUT);
  digitalWrite(30,LOW);
  previousMillis = millis();
//  T2CON &= ~(RCLK | TCLK | C_T2);
//  T2MOD |= bT2_CLK;
//  T2CON &= ~(CP_RL2);
//  ET2 = 1;
//  RCAP2L = 0x20;
//  RCAP2H = 0x4e;
//  TL2 = 0x20;
//  TH2 = 0x4e;
//  TR2 = 1;
//  T2CON |= TF2;
}

void loop() {
  unsigned long currentMillis;

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    set_pixel_for_GRB_LED_color(ledData, i, hue++, brightness);
  }
    neopixel_show_P3_4(ledData, NUM_BYTES);
    if(brightness-- == 0) while(1){};
  //  delay(100);

//  currentMillis = millis();
//  if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
 // }
  digitalWrite(30,ledState);
}