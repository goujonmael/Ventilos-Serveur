float RT = 50000;// the rated potentiometer value 10k
float R;// the unknown resistance value R

const byte OC1A_PIN = 9;
const byte OC1B_PIN = 10;

const word PWM_FREQ_HZ = 25000; //Adjust this value to adjust the frequency (Frequency in HZ!) (Set currently to 25kHZ)
const word TCNT1_TOP = 16000000/(2*PWM_FREQ_HZ);


int potPin = A0; // potentiometer is connected to analog 0 pin
int potValue; // variable used to store the value coming from the sensor
int percent; // variable used to store the percentage value

void setup() {
Serial.begin(9600); // initialize the serial communication

pinMode(OC1A_PIN, OUTPUT);

  // Clear Timer1 control and count registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // Set Timer1 configuration
  // COM1A(1:0) = 0b10   (Output A clear rising/set falling)
  // COM1B(1:0) = 0b00   (Output B normal operation)
  // WGM(13:10) = 0b1010 (Phase correct PWM)
  // ICNC1      = 0b0    (Input capture noise canceler disabled)
  // ICES1      = 0b0    (Input capture edge select disabled)
  // CS(12:10)  = 0b001  (Input clock select = clock/1)
  
  TCCR1A |= (1 << COM1A1) | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << CS10);
  ICR1 = TCNT1_TOP;
}
void loop() {
  
potValue = analogRead(potPin); // get a reading from the potentiometer, assign the name potValue
percent = map(potValue, 0, 1023, 0, 100); // convert reading to a percentage
float voltage = potValue * (5.0 / 1023.0);  //convert to voltage 
R = ( voltage * RT)/5.0;   // get value of unknown resistance

Serial.print("Analog Reading: "); // print out the analog value from A0
Serial.print(potValue);
Serial.print(", Voltage =");// prints the text "Voltage ="
Serial.print(voltage);
Serial.print("v, Resistance="); //prints the text "Resistance ="
Serial.print(R);
Serial.print(" ohms");
Serial.print(", Percentage: "); // print out the percentage
Serial.print(percent);
Serial.println("%");


setPwmDuty(percent);

delay(500); // wait a second

}


void setPwmDuty(byte duty) {
  OCR1A = (word) (duty*TCNT1_TOP)/100;
}
