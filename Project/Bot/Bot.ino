#include "Bot.h"
#include "microLED.h"
#include <RF24.h>
#include <SPI.h>
#include <Servo.h>
#include <nRF24L01.h>

void setup() {

    Serial.begin(9600);

    steer_servo.attach(STEERING_SERVO_PIN); // Инициализация сервоприводов

    pinMode(S1, OUTPUT); 					// Инициализация моторов
    pinMode(S2, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);

    radio.begin(); 							// Инициализация радиопередатчика
    radio.openReadingPipe(0, 0xF0F0F0F0F0);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();

    strip.setBrightness(60); 				// Инициализация ленты
    strip.fill(mYellow);         			// заливаем жёлтым
    strip.show();                        	// выводим изменения
}

void loop() {

    if (radio.available()) {
        radio.read(&msg, sizeof(msg));
        Serial.println("Recieve: (" + String(msg.x_) + ", " + String(msg.y_) + ")");
    }

    X = map(msg.x_, 0, 1023, 150, 30); 		// переводим значение X в новый диапазон
    Y = map(msg.y_, 0, 1023, 450, 60); 		// переводим значение Y в новый диапазон

    if (X < 50 || X > 130) {
        if (Y > 300)
            Y = 400;
        else if (Y < 210)
            Y = 110;
    }

    steer_servo.write(X); 					// поворачиваем сервопривод от джойстика

    if (Y > 255) {
        if (X > 130) {
            analogWrite(S2, map(Y - 255, 0, 255, 0, 155));
        } else {
            analogWrite(S2, Y - 255);
        }
        digitalWrite(D2, LOW);
    } else {
        analogWrite(S2, 255 - Y);
        digitalWrite(D2, HIGH);
    }

    if (Y > 255) {
        if (X < 50) {
            analogWrite(S1, map(Y - 255, 0, 255, 0, 155));
        } else {
            analogWrite(S1, Y - 255);
        }
        digitalWrite(D1, HIGH);
    } else {
        analogWrite(S1, 255 - Y);
        digitalWrite(D1, LOW);
    }
}