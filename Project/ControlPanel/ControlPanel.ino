#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "ControlPanel.h"

void setup() {

    radio.begin();
    radio.openWritingPipe(0xF0F0F0F0F0);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();

}

void loop() {

    msg.x_ = analogRead(Xaxis);               // Считываем значения оси Х
    msg.y_ = analogRead(Yaxis);               // Считываем значения оси У
    radio.write(&msg, sizeof(msg));
    Serial.println("Send: (" + String(msg.x_) + ", " + String(msg.y_) + ")");

}