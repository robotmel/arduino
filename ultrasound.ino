//Скетч ультразвукового дальномера
//Автор: Татьяна Мельничук http://tmel.ru

const int trigPin = 12; // подключаем trigPin на 12 контакт Arduino
const int echoPin = 13; // подключаем echoPin на 13 контакт Arduino

void setup() {
Serial.begin(9600); // инициируем связь с серийным портом Arduino IDE на скорости 9600 бод/с
Serial.println("Start!"); // выводим в монитор серийного порта сообщение: Start!
pinMode(trigPin, OUTPUT); // настраиваем trigPin на передачу сигнала (отправка ультразвуковой волны)
pinMode(echoPin, INPUT); // настраиваем echoPin на прием сигнала (прием ультразвуковой волны)
}

void loop() {
long duration, distance; // декларируем переменные: duration - продолжительность; distance - расстояние
digitalWrite(trigPin, LOW); // отправляем логический 0 на trigPin
delayMicroseconds(2); // задаем задержку на 2 микросекунды
digitalWrite(trigPin, HIGH); // отправляем логическую 1 на trigPin (отправляем ультразвуковую волну)
delayMicroseconds(10); // задаем время продолжительности ультразвуковой волны на 10 мкс
digitalWrite(trigPin, LOW); // отправляем логический 0 на trigPin
duration = pulseIn(echoPin, HIGH); // присваиваем переменной duration значение времени получения ультразвуковой волны в мкс
distance = (duration/2) / 29.4; // переводим мкс в см и присваиваем полученное значение переменной distance
Serial.print ("Distance is "); //выводим в монитор серийного порта сообщение: Distance is
Serial.print (distance); // выводим в монитор серийного порта значение переменной distance
Serial.print (" cm"); // выводим в монитор серийного порта единицы измерения (сантиметры)
Serial.println(); // отправляем в монитор серийного порта пустую строку-разделитель
delay(100); // задаём задержку 100 миллисекунд
}
