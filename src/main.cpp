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
*/

// Range of raw ADC values accross the touch screen area
#define XMIN 69
#define XMAX 954
#define YMIN 102
#define YMAX 913

#define ARRAY_SIZE 5

// Physical properties of the touch screen
#define WIDTH 212.2
#define HEIGHT 159.4
#define VOFFSET -14
#define HOFFSET 19

#define MOUSE_EN PIND0
#define RANGE 12
#define MOUSE_DELAY 5

#define FINGERED_UP !(PINF & (1<<PINF5))
#define FINGERED_LO !(PINF & (1<<PINF4))

#define LED_L 7

int xvals[ARRAY_SIZE] {0};
int yvals[ARRAY_SIZE] {0};
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
  DDRF = 0x00;                                  // all pins as input
  PORTF = 0x00;                                 // all pins no pull-up / LOW

  // Pre-configuring ADC
  ADMUX |= (1<<REFS0) | (1<<MUX2) | (1<<MUX0);  // Set VRef to Vcc and connect ADC5 to ADC (p. 313)
  ADCSRA |= (1<<ADEN);

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

uint16_t getADC(){
  uint16_t val = ADCL;
  val |= (ADCH<<8);
  return val;
}

bool isTouched(void){
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

  // Sequence 1, check quadrant UL
  DDRF = 0x80;                                  // Set PF7 as output, others as input
  PORTF = 0x20;                                 // Activate pull-up on PF5

  if (FINGERED_UP) {
    return true;
  } else {
    // Sequence 2, check quadrant UR
    DDRF = 0x40;                                // Set PF7 as input, PF6 as output

    if (FINGERED_UP) {
      return true;
    } else {
      // Sequence 3, check quadrant LR
      DDRF = 0x00;                              // Turn off pull-up on PF5

      if (FINGERED_LO) {
        return true;
      } else {
        // Sequence 4, check quadrant LL
        DDRF = 0x80;// Set PF7 as output

        if (FINGERED_LO) {
          return true;
        } else {
          // No finger present
          Serial.println("NOT TOUCHED!");
          return false;
        }
      }
    }
  }
}

int xRead(void) {
  /*
  ADC7  x_le    HIGH
  ADC6  x_ri    LOW
  ADC5  y_up    ADC
  ADC4  y_lo    Hi Z
  */

  // Setting up pin modes
  DDRF = 0xC0;                                  // Setting PF7 and PF6 as output
  PORTF = 0x40;                                 // Setting PF6 HIGH
  ADMUX &= ~(1<<MUX1);                          // Making sure ADC5 is connected to ADC
  ADCSRA |= (1<<ADSC);                          // Start conversion
  delay(10);

  while ((ADCSRA & (1<<ADSC))){
    // do nothing
  }
  // getADC();
  return getADC();
}

int axRead(char ax) {
  /*
  Reading X             | Reading Y
  ------------------------------------------
  ADC7  x_le    HIGH    | ADC7  x_le    ADC
  ADC6  x_ri    LOW     | ADC6  x_ri    Hi Z
  ADC5  y_up    ADC     | ADC5  y_up    HIGH
  ADC4  y_lo    Hi Z    | ADC4  y_lo    LOW
  */

  if ((ax == 'x') | (ax == 'X')) {
    // Setting up pin modes
    DDRF = 0xC0;                                  // Setting PF7 and PF6 as output
    PORTF = 0x40;                                 // Setting PF6 HIGH
    ADMUX &= ~(1<<MUX1);                          // Making sure ADC5 is connected to ADC
    ADCSRA |= (1<<ADSC);                          // Start conversion
    delay(10);

    while ((ADCSRA & (1<<ADSC))){
      // do nothing
    }
    // getADC();
    return getADC();
  } else if ((ax == 'y') | (ax == 'Y')) {
    // Setting up pin modes
    DDRF = 0x30;                                  // Setting PF5 and PF4 as output
    PORTF = 0x20;                                 // Setting PF5 HIGH
    ADMUX |= (1<<MUX1);                           // Connecting ADC7 to ADC
    ADCSRA |= (1<<ADSC);                          // Start conversion
    delay(10);

    while ((ADCSRA & (1<<ADSC))){
      // do nothing
    }
    // getADC();
    return getADC();
  }
}

int yRead(void) {
  /*
  ADC7  x_le    ADC
  ADC6  x_ri    Hi Z
  ADC5  y_up    HIGH
  ADC4  y_lo    LOW
  */

  // Setting up pin modes
  DDRF = 0x30;                                  // Setting PF5 and PF4 as output
  PORTF = 0x20;                                 // Setting PF5 HIGH
  ADMUX |= (1<<MUX1);                           // Connecting ADC7 to ADC
  ADCSRA |= (1<<ADSC);                          // Start conversion
  delay(10);

  while ((ADCSRA & (1<<ADSC))){
    // do nothing
  }
  // getADC();
  return getADC();
}

int doTheMath(int vals[ARRAY_SIZE]) {
  int avrg = 0;
  for (int i = 0; i < ARRAY_SIZE-1; i++) {
    avrg += vals[i];
  }
  return avrg / ARRAY_SIZE;
}

void loop() {
  if (Serial){
    int xval = 0;
    int yval = 0;
    for (int i = 0; i < ARRAY_SIZE-1; i++) {
      if (isTouched()) {
        xvals[i] = axRead('x');
        if (isTouched()) {
          yvals[i] = axRead('y');

          xval = doTheMath(xvals);
          yval = doTheMath(yvals);
        }
      }

      // Mouse control values are only send if MOUSE_EN (PIND6) is pulled LOW,
      // else positional vales are sent over serial
      if (!(PIND & (1<<MOUSE_EN))){
        // PORTC |= (1<<LED_L);
        xval = map(xval, XMIN+HOFFSET, XMAX+HOFFSET, -RANGE, RANGE);
        xval = constrain(xval, -RANGE, RANGE);
        yval = map(yval, YMIN+VOFFSET, YMAX+VOFFSET, RANGE, -RANGE);
        yval = constrain(yval, -RANGE, RANGE);
        Mouse.move(xval, yval, 0);
        Serial.print(xval);Serial.print("\t");Serial.println(yval);
        delay(MOUSE_DELAY);
      } else {
        // PORTC &= ~(1<<LED_L);
        xval = map(xval, XMIN, XMAX, -0.5*WIDTH, 0.5*WIDTH);
        xval = constrain(xval, -0.5*WIDTH, 0.5*WIDTH);
        yval = map(yval, YMIN, YMAX, -0.5*HEIGHT, 0.5*HEIGHT);
        yval = constrain(yval, -0.5*HEIGHT, 0.5*HEIGHT);
        Serial.print(xval);Serial.print("\t");Serial.println(yval);
      }
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