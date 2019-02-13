#define led 13
#define buzzer 3
#define echoPin A0
#define pingPin 10

int toneCounter = 0;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);

	pinMode(led, OUTPUT);
	pinMode(buzzer, OUTPUT);
	pinMode(pingPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	long dist = msToCm(ping());

	if ( dist < 100.00 ) {
		toneCounter = 0;

		// 1    == min distance in cm
		// 100  == max distance in cm
		// 1500 == max frequency
		// 500  == min frequency
		int pitch = map(dist, 1, 100, 1500, 500);
		tone(buzzer, pitch);

	} else {
		toneCounter++;

		if ( toneCounter == 100 ) {
			toneCounter = 0;
			noTone(buzzer);
		}
	}
}

long ping() {
	long duration;

	digitalWrite(pingPin, LOW);
	delayMicroseconds(2);

	digitalWrite(pingPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(pingPin, LOW);

	duration = pulseIn(echoPin, HIGH);

	return duration;
}

long msToCm(long microseconds) {
	return microseconds * .034 / 2;
}
