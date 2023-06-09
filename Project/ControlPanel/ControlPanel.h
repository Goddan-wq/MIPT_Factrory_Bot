#pragma once

#include <RF24.h>

const int8_t Xaxis  = A0;                 // Определяем номер вывода, к которому подключен контакт оси Х джойстика
const int8_t Yaxis  = A1;                 // Определяем номер вывода, к которому подключен контакт оси У джойстика

RF24 radio(9, 10);                        // CE, CSN

// Структура сообщения, передаваемая радиосигналом

struct {

  uint16_t x_;
  uint16_t y_;

} msg;