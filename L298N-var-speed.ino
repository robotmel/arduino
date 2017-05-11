//Тестирование контроллера L298N для двух двигателей на переменной скорости
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
}
void loop()
{
  digitalWrite(in1, LOW); //подаем на in1 логический 0 (напряжение 0 В)
  digitalWrite(in2, HIGH); //подаем на in2 логическую 1 (напряжение 5 В)
  digitalWrite(in3, LOW); //подаем на in3 логический 0 (напряжение 0 В)
  digitalWrite(in4, HIGH); //подаем на in4 логическую 1 (напряжение 5 В)
  for (int i = 0; i <= 255; ++i) //плавно увеличиваем напряжение на ENA и ENB c 0 до 5 вольт
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  for (int i = 255; i >= 0; --i) //плавно уменьшаем напряжение на ENA и ENB c 5 до 0 вольт
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  delay(3000); //задержка 3 секунды
  digitalWrite(in1, LOW); //подаем на in1 логический 0 (напряжение 0 В)
  digitalWrite(in2, HIGH); //подаем на in2 логическую 1 (напряжение 5 В)
  digitalWrite(in3, LOW); //подаем на in3 логический 0 (напряжение 0 В)
  digitalWrite(in4, HIGH); //подаем на in4 логическую 1 (напряжение 5 В)
  for (int i = 0; i <= 255; ++i) //плавно увеличиваем напряжение на ENA и ENB c 0 до 5 вольт
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  for (int i = 255; i >= 0; --i) //плавно уменьшаем напряжение на ENA и ENB c 5 до 0 вольт
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  delay(3000); //задержка 3 секунды
}
