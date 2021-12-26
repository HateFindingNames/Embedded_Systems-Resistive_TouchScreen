#include <Arduino.h>
#include <Mouse.h>

/*
Port mapping: A0 - A3 -> PF7 - PF4
Pin   Port    Color   Position
--------------------------
A0    PF7     blk     x_le
A1    PF6     brn     x_ri
A2    PF5     red     y_up
A3    PF4     ylw     y_lo

ToDo:
[ ] Improve filtering (?)
[ ] Fix touch-release bug
[ ] Output decimals to serial
*/

// Range of raw ADC values accross the touch screen area
#define XMIN 69.0
#define XMAX 954.0
#define YMIN 102.0
#define YMAX 913.0

#define ARRAY_SIZE 10

// Physical properties of the touch screen
#define WIDTH 212.2
#define HEIGHT 159.4
#define VOFFSET -14.0
#define HOFFSET 19.0

#define MOUSE_EN PIND0
#define MOUSE_SPEED 40
#define MOUSE_DELAY 5

#define FINGERED_UP !(PINF & (1<<PINF5))
#define FINGERED_LO !(PINF & (1<<PINF4))

#define LED_L 7

float xvals[ARRAY_SIZE] {0};
float yvals[ARRAY_SIZE] {0};
// uint16_t val = 0;

void setup() {
  cli();
  // Setting unused pins as Input and activate pull-ups
  DDRB = 0x00;
  PORTB = 0xFF;
  DDRC = 0x80;                                  // LED_BUILTIN (PC7) as output
  PORTC = 0x7F;                                 // LED_BUILTIN off
  DDRD = 0x00;
  PORTD = 0xFF;
  DDRE = 0x00;
  PORTE = 0xFF;
  // Panel is connected to PORTF pins PF7:4
  DDRF = 0x80;                                  // All pins as input
  PORTF = 0x20;                                 // All pins no pull-up / LOW

  // Pre-configuring ADC
  ADMUX |= (1<<REFS0) | (1<<MUX2) | (1<<MUX0);  // Set VRef to Vcc and connect ADC5 to ADC (p. 313)
  // ADC enable and ADC-clock prescaler to 128. CPU-Clock / ADC-prescaler = ADC-Clock.
  // At 10bit resolution must not be higher than 200kHz.
  // ADPS2:0 set to 1 prescales by 128 giving an ADC-clock of 125kHz (8us per cycle).
  // See p. 300 ff
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

  /*
  Configuring interrupts (p. 89)
  ISCn1    ISCn0   Description
  0        0       The low level of INTn generates an interrupt request
  0        1       Any edge of INTn generates asynchronously an interrupt request
  1        0       The falling edge of INTn generates asynchronously an interrupt request
  1        1       The rising edge of INTn generates asynchronously an interrupt request
  */
  EICRA |= (1<<ISC00);
  EIMSK |= (1<<INT0);                           // Enable external interrupt on INTO

  sei();
  Serial.begin(115200);
  Mouse.begin();

  delay(300);
}

bool isTouchy(void){
  /*
  1-----------------------------------2------------------------------------
  | PF7  x_le    LOW                  | PF7  x_le    Hi Z                 |
  | PF6  x_ri    Hi Z                 | PF6  x_ri    LOW                  |
  | PF5  y_up    Digital IN, pull-up  | PF5  y_up    Digital IN, pull-up  |
  | PF4  y_lo    Hi Z                 | PF4  y_lo    Hi Z                 |
  4-----------------------------------3------------------------------------
  | PF7  x_le    LOW                  | PF7  x_le    Hi Z                 |
  | PF6  x_ri    Hi Z                 | PF6  x_ri    LOW                  |
  | PF5  y_up    Hi Z                 | PF5  y_up    Hi Z                 |
  | PF4  y_lo    Digital IN, pull-up  | PF4  y_lo    Digital IN, pull-up  |
  -------------------------------------------------------------------------
  */

  ADCSRA &= ~(1<<ADEN);                         // Disable ADC
  // Sequence 1, check quadrant UL
  DDRF = 0x80;                                  // Set PF7 as output, others as input
  PORTF = 0x20;                                 // Activate pull-up on PF5

  if (FINGERED_UP) {
    // Serial.println("UL detected");
    return true;
  } else {
    // Sequence 2, check quadrant UR
    DDRF = 0x40;                                // Set PF7 as input, PF6 as output

    if (FINGERED_UP) {
      // Serial.println("UR detected");
      return true;
    } else {
      // Sequence 3, check quadrant LR
      PORTF = 0x10;                              // Turn off pull-up on PF5, turn on pull-up on PF4

      if (FINGERED_LO) {
        // Serial.println("LR detected");
        return true;
      } else {
        // Sequence 4, check quadrant LL
        DDRF = 0x80;                             // Set PF7 as output, PF6 as input

        if (FINGERED_LO) {
          // Serial.println("LL detected");
          return true;
        } else {
          // No finger present
          // Serial.println("NO NO TOUCHY!");
          return false;
        }
      }
    }
  }
}

uint16_t getADC(){
  uint16_t val = ADCL;
  val |= (ADCH<<8);
  return val;
}

int axRead(bool ax) {
  /*
  Reading X             | Reading Y
  ------------------------------------------
  ADC7  x_le    HIGH    | ADC7  x_le    ADC
  ADC6  x_ri    LOW     | ADC6  x_ri    Hi Z
  ADC5  y_up    ADC     | ADC5  y_up    HIGH
  ADC4  y_lo    Hi Z    | ADC4  y_lo    LOW
  */

  ADCSRA |= (1<<ADEN);                            // Enable ADC
  if (ax == true) {
    // Setting up pin modes
    DDRF = 0xC0;                                  // Setting PF7 and PF6 as output
    PORTF = 0x40;                                 // Setting PF6 HIGH
    ADMUX &= ~(1<<MUX1);                          // Making sure ADC5 is connected to ADC
    ADCSRA |= (1<<ADSC);                          // Start conversion
    // delay(1);

    while ((ADCSRA & (1<<ADSC))){
      // do nothing
    }
    // DDRF |= (1<<DDF4);                            // PF4 as output
    // PORTF |= (1<<PORTF4);                         // PF4 LOW
    return getADC();

  } else if (ax == false) {
    // Setting up pin modes
    DDRF = 0x30;                                  // Setting PF5 and PF4 as output
    PORTF = 0x20;                                 // Setting PF5 HIGH
    ADMUX |= (1<<MUX1);                           // Connecting ADC7 to ADC
    ADCSRA |= (1<<ADSC);                          // Start conversion
    // delay(1);

    while ((ADCSRA & (1<<ADSC))){
      // do nothing
    }
    return getADC();

  } else {
    return 9999;                                  // Will never be returned. Placed to get rid of compiler warning
  }
}

float doTheMath(float vals[ARRAY_SIZE]) {
  float avrg = 0;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    avrg += vals[i];
  }
  return avrg / ARRAY_SIZE;
}

void loop() {
  float xval = 7777.0;
  float yval = 7777.0;
  // Shifting array elements by 1 to the left dropping the 0th element
  for (int i = 0; i < ARRAY_SIZE-1; i++) {
    xvals[i] = xvals[i+1];
    yvals[i] = yvals[i+1];
  }

  if (isTouchy()) {
    xvals[ARRAY_SIZE-1] = axRead(true);
    if (isTouchy()) {
      yvals[ARRAY_SIZE-1] = axRead(false);
      xval = doTheMath(xvals);
      yval = doTheMath(yvals);
    }
  }

  if ((xval < 7777) & (yval < 7777)) {
    // Mouse control values are only send if MOUSE_EN (PIND6) is pulled LOW,
    // else positional vales are sent over serial
    if (!(PIND & (1<<MOUSE_EN))) {
      xval = map(xval, XMIN, XMAX, -MOUSE_SPEED, MOUSE_SPEED);
      yval = map(yval, YMIN, YMAX, MOUSE_SPEED, -MOUSE_SPEED);
      Mouse.move(xval, yval, 0);
      delay(MOUSE_DELAY);
    } else {
      xval = map(xval, XMIN, XMAX+1.0, -50*WIDTH, 50*WIDTH+1)/100;
      yval = map(yval, YMIN, YMAX+1.0, -50*HEIGHT, 50*HEIGHT+1)/100;
      Serial.print(xval);Serial.print("\t");Serial.println(yval);
    }
  }
}

ISR(INT0_vect){
  // Let LED_L indicate if mouse control is enabled. ON if turned on, OFF otherwise
  if (PIND & (1<<MOUSE_EN)){
    PORTC &= ~(1<<LED_L);                  // LED_L off
  } else {
    PORTC |= (1<<LED_L);                 // LED_L on
  }
}