//Тестирование контроллера L298N для двух двигателей на постоянной скорости
//Автор: Татьяна Мельничук http://tmel.ru

const int enA = 9; //подключаем ENA модуля L298N к контакту 9 Arduino c ШИМ
const int in1 = 8; //подключаем IN1 модуля L298N к контакту 8 Arduino
const int in2 = 7; //подключаем IN2 модуля L298N к контакту 7 Arduino
const int enB = 10; //подключаем ENB модуля L298N к контакту 10 Arduino c ШИМ
const int in3 = 5; //подключаем IN3 модуля L298N к контакту 6 Arduino
const int in4 = 6; //подключаем IN4 модуля L298N к контакту 5 Arduino

void setup()
{
  pinMode(enA, OUTPUT); //настраиваем контакт enA на прием сигналов от Arduino
  pinMode(enB, OUTPUT); //настраиваем контакт enB на прием сигналов от Arduino
  pinMode(in1, OUTPUT); //настраиваем контакт in1 на прием сигналов от Arduino
  pinMode(in2, OUTPUT); //настраиваем контакт in2 на прием сигналов от Arduino
  pinMode(in3, OUTPUT); //настраиваем контакт in3 на прием сигналов от Arduino
  pinMode(in4, OUTPUT); //настраиваем контакт in4 на прием сигналов от Arduino
  analogWrite(enA, 255); //устанавливаем скорость вращения двигателя А на максимальную
  analogWrite(enB, 255); //устанавливаем скорость вращения двигателя В на максимальную
}
void loop()
{
  digitalWrite(in1, LOW); //подаем на in1 логический 0 (напряжение 0 В)
  digitalWrite(in2, HIGH); //подаем на in2 логическую 1 (напряжение 5 В)
  digitalWrite(in3, LOW); //подаем на in3 логический 0 (напряжение 0 В)
  digitalWrite(in4, HIGH); //подаем на in4 логическую 1 (напряжение 5 В)
  delay(5000); //задержка 5 секунд
  digitalWrite(in1, LOW); //подаем на in1 логический 0 (напряжение 0 В)
  digitalWrite(in2, LOW); //подаем на in2 логический 0 (напряжение 0 В)
  digitalWrite(in3, LOW); //подаем на in3 логический 0 (напряжение 0 В)
  digitalWrite(in4, LOW); //подаем на in4 логический 0 (напряжение 0 В)
  delay(5000); //задержка 5 секунд
  digitalWrite(in1, HIGH); //подаем на in1 логическую 1 (напряжение 5 В)
  digitalWrite(in2, LOW); //подаем на in2 логический 0 (напряжение 0 В)
  digitalWrite(in3, HIGH); //подаем на in3 логическую 1 (напряжение 5 В)
  digitalWrite(in4, LOW); //подаем на in4 логический 0 (напряжение 0 В)
  delay(5000); //задержка 5 секунд
  digitalWrite(in1, HIGH); //подаем на in1 логическую 1 (напряжение 5 В)
  digitalWrite(in2, LOW); //подаем на in2 логический 0 (напряжение 0 В)
  digitalWrite(in3, LOW); //подаем на in3 логический 0 (напряжение 0 В)
  digitalWrite(in4, HIGH); //подаем на in4 логическую 1 (напряжение 5 В)
  delay(5000); //задержка 5 секунд
}
