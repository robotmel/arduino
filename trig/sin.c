/* Вычисление значения функции синус с помощью рядов Тейлора */
/*Авторы: Владимир Яковлев, Дарья Королёва, Наталия Плюскова */
/* Наш код на GitHub: https://github.com/robotmel/arduino/blob/master/trig/sin.c */

#include <stdio.h>
#include <math.h>

int main()
{
    long double x;
    long double next_term;
    long double sumsin=0;
    long double sinus;
    long double relerr, abserr;
    int next_div_fac=3;
    int i,k;

    printf("**************************************************************** \n");
    printf("Вычисление значения функции синус с помощью рядов Тейлора \n");
    printf("**************************************************************** \n");
    printf("Введите величину угла в радианах: ");
    scanf("%Lf",&x);
    printf("Введите необходимое число членов ряда Тейлора: ");
    scanf("%d",&k);

    next_term = x;
    for( i=0; i<k; ++i )
    {
        sumsin += next_term;
        next_term *= -1*x*x/(next_div_fac*(next_div_fac-1));
        next_div_fac += 2;
    }
    sinus = sin(x);
    abserr = fabs(sinus-sumsin);
    relerr = abserr/fabs(sinus)*100;

    printf("**************************************************************** \n");
    printf("Приближённое значение синуса: %.15Lf \n", sumsin);
    printf("Точное значение синуса: %.15Lf \n", sinus);
    printf("Абсолютная погрешность: %.15Lf \n", abserr);
    printf("Относительная погрешность: %.5Lf%% \n", relerr);
    printf("**************************************************************** \n");
    printf("Благодарим за использование нашей программы! \n");
    printf("Владимир Яковлев, e-mail: mr.kollc@list.ru \n");
    printf("Дарья Королёва, e-mail: daxa0247@mail.ru \n");
    printf("Наталия Плюскова, e-mail: s52@edux.ml \n");
    printf("**************************************************************** \n");

    return 0;
}
