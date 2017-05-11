/* Вычисление значения функции косинус с помощью рядов Тейлора */
/*Авторы: Владимир Яковлев, Дарья Королёва, Наталия Плюскова */
/* Наш код на GitHub: https://github.com/robotmel/arduino/blob/master/trig/cos.c */

#include <stdio.h>
#include <math.h>
int main()
{
    long double x;
    long double next_term;
    long double sumcos=0;
    long double cosinus;
    long double relerr, abserr;
    int next_div_fac=2;
    int i, k;

    printf("**************************************************************** \n");
    printf("Вычисление значения функции косинус с помощью рядов Тейлора \n");
    printf("**************************************************************** \n");
    printf("Введите величину угла в радианах: ");
    scanf("%Lf",&x);
    printf("Введите необходимое число членов ряда Тейлора: ");
    scanf("%d",&k);

    next_term = 1;
    for( i=0; i<k; ++i )
    {
        sumcos += next_term;
        next_term *= -1*x*x/(next_div_fac*(next_div_fac-1));
        next_div_fac += 2;
    }
    cosinus = cos(x);
    abserr = fabs(cosinus-sumcos);
    relerr = abserr/fabs(cosinus)*100;

    printf("**************************************************************** \n");
    printf("Приближённое значение косинуса: %.15Lf \n", sumcos);
    printf("Точное значение косинуса: %.15Lf \n", cosinus);
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
