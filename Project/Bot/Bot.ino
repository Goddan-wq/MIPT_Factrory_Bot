#include "Servo.h"
#include "AmperkaStepper.h"
#include "Bot.h"

Servo ServoLeft;
Servo ServoRigh;

void setup() {

    ServoLeft.attach(SERVO_LEFT_PIN);        // Инициализация сервоприводов
    ServoRigh.attach(SERVO_RIGH_PIN);

    pinMode(S1, OUTPUT);                     // Инициализация моторов
    pinMode(S2, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);

}

void loop() {
    
    X = analogRead(Xaxis);               // Считываем значения оси Х
    Y = analogRead(Yaxis);               // Считываем значения оси У

    X = map(X, 0, 1023, 0, 180);         // переводим значение X в новый диапазон
    Y = map(Y, 0, 1023, 0, 510);         // переводим значение Y в новый диапазон

    ServoLeft.write(X);                  // поворачиваем сервопривод от джойстика
    ServoRigh.write(X);                  // поворачиваем сервопривод от джойстика

    if (Y > 255) {
        analogWrite(S2, Y - 255);  
        digitalWrite(D2, LOW);
    }
    else {
        analogWrite(S2, 255 - Y);
        digitalWrite(D2, HIGH);
    }

    if (Y > 255) {
        analogWrite(S1, Y - 255);  
        digitalWrite(D1, HIGH);
    }
    else {
        analogWrite(S1, 255 - Y);
        digitalWrite(D1, LOW);
    }

}