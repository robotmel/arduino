//Скетч автомобиля, избегающего препятствия, в производственном режиме
//Автор: Татьяна Мельничук http://tmel.ru

#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

const int zummer = 3;
const int trigPin = 12; //подключаем trigPin на 12 контакт Arduino
const int echoPin = 13; //подключаем echoPin на 13 контакт Arduino
const int enA = 9; //подключаем ENA модуля L298N к контакту 9 Arduino c ШИМ
const int in1 = 8; //подключаем IN1 модуля L298N к контакту 8 Arduino
const int in2 = 7; //подключаем IN2 модуля L298N к контакту 7 Arduino
const int enB = 10; //подключаем ENB модуля L298N к контакту 10 Arduino c ШИМ
const int in3 = 5; //подключаем IN3 модуля L298N к контакту 6 Arduino
const int in4 = 6; //подключаем IN4 модуля L298N к контакту 5 Arduino

void warning(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0, 20); 
  u8g.print("WARNING! Obstacle detected");
}

void forward(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0, 20); 
  u8g.print("Moving forward!");
}

void setup()
{
   pinMode(zummer, OUTPUT);
   pinMode(trigPin, OUTPUT); //настраиваем trigPin на передачу сигнала (отправка ультразвуковой волны)
   pinMode(echoPin, INPUT); //настраиваем echoPin на прием сигнала (прием ультразвуковой волны)
   pinMode(in1, OUTPUT); //настраиваем контакт in1 на прием сигналов от Arduino
   pinMode(in2, OUTPUT); //настраиваем контакт in2 на прием сигналов от Arduino
   pinMode(in3, OUTPUT); //настраиваем контакт in3 на прием сигналов от Arduino
   pinMode(in4, OUTPUT); //настраиваем контакт in4 на прием сигналов от Arduino
   analogWrite(enA, 130); //устанавливаем скорость вращения двигателя А равную 130
   analogWrite(enB, 130); //устанавливаем скорость вращения двигателя В равную 130
   u8g.setRot180();
}

void loop() {
   long duration, distance; //объявляем переменные: duration - продолжительность; distance - расстояние
   digitalWrite(trigPin, LOW); //отправляем логический 0 на trigPin
   delayMicroseconds(2); //задаем задержку на 2 микросекунды
   digitalWrite(trigPin, HIGH); // отправляем логическую 1 на trigPin (отправляем ультразвуковую волну)
   delayMicroseconds(10); //задаем время продолжительности ультразвуковой волны на 10 мкс
   digitalWrite(trigPin, LOW); //отправляем логический 0 на trigPin
   duration = pulseIn(echoPin, HIGH); //присваиваем переменной duration значение времени получения ультразвуковой волны в мкс
   distance = (duration/2) / 29.4; //переводим мкс в см и присваиваем полученное значение переменной distance
   if (distance < 25) { //задаём последовательность действий в случае обнаружения препятствия ближе 25 см
	analogWrite(zummer, 20);
	u8g.firstPage();  
		do {
			warning();
		} while( u8g.nextPage() );
	digitalWrite(in1, HIGH); //подаём на in1 логическую 1
	digitalWrite(in2, LOW); //подаём на in2 логический 0
	digitalWrite(in3, LOW); //подаём на in3 логический 0
	digitalWrite(in4, HIGH); //подаём на in4 логическую 1
   }
   else { //задаём последовательность действий в случае отсутствия препятствий
	analogWrite(zummer, 0);
	u8g.firstPage();
	do {
		forward();
	} while( u8g.nextPage() );
	digitalWrite(in1, LOW); //подаём на in1 логический 0
	digitalWrite(in2, HIGH); //подаём на in2 логическую 1
	digitalWrite(in3, LOW); //подаём на in3 логический 0
	digitalWrite(in4, HIGH); //подаём на in4 логическую 1
   }
}
