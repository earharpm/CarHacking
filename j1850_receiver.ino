#define inPin     1
#define T1_START  34286 // TODO: Calc start value (and prescaler) to give 1uS interrupt

volatile int count = 0;
volatile int riseTime = 0;
volatile int highTime = 0;
volatile bool _hasBit = false;


void setup() 
{
	pinMode(inPin, INPUT);

	// Initialize input pin interrupts
	attachInterrupy(digitalPinToInterrupt(inPin), inputRiseISR, RISING);
	attachInterrupy(digitalPinToInterrupt(inPin), inputFallISR, FALLING);

	// Initialize timer1
	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;

	TCNT1 = T1_START;
	TCCR1B |= (1 << CS12);  // 256 prescaler
	T1MSK1 |= (1 << TOIE1); // Timer1 overflow intr enable
	interrupts();
}

void loop()
{
	bool hasBit = false;
	int bitLength = -1;

	noInterrupts();
	if (_hasBit){
		hasBit = _hasBit;
		bitLength = highTime;
	}
	interrupts();

	if (hasBit) {
		decodeBit(bitLength);
	}
}

void inputHighISR() 
{
	riseTime = count;
	hasBit = false;
}

void inputFallISR()
{
	highTime = count - riseTime;
	hasBit = true;
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = T1_START;
	count++;
}

void decodeBit(int bitLength, Message* message)
{
	if (bitLength < 12) {

		} else if (bitLength < 20) {

		}
}