#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <fenv.h>

char *IEEE754(float number)
{
    union
    {
        float f;
        uint32_t i;
    } converter;
    converter.f = number;
    uint32_t bits = converter.i;
    // alocando espaço na string
    char *binaryString = (char *)malloc(33 * sizeof(char));
    // shifts na string
    for (int i = 31; i >= 0; i--)
    {
        binaryString[31 - i] = (bits & (1 << i)) ? '1' : '0';
    }
    // fim da string
    binaryString[32] = '\0';
    return binaryString;
}

float calc(float num1, float num2, char op)
{
    float res;

    if(op == '+') res = num1 + num2;
    else if(op == '-') res = num1 - num2;
    else if(op == 'x' || op == 'X' || op == '.') res = num1 * num2;
    else if(op == '/') res = num1 / num2;
    else {
        printf("Inserido um operador errado para calculo\n"); 
        exit(0);
    } 

    return res;
}

void printActualFlags()
{
    printf("\nFE_INEXACT: %d\n", fetestexcept(FE_INEXACT) != 0 ? 1 : 0);
    printf("FE_DIVBYZERO: %d\n", fetestexcept(FE_DIVBYZERO) != 0 ? 1 : 0);
    printf("FE_UNDERFLOW: %d\n", fetestexcept(FE_UNDERFLOW) != 0 ? 1 : 0);
    printf("FE_OVERFLOW: %d\n", fetestexcept(FE_OVERFLOW) != 0 ? 1 : 0);
    printf("FE_INVALID: %d\n", fetestexcept(FE_INVALID) != 0 ? 1 : 0);
}

void printIEEE(float num, char *string)
{
    char *valIEEE754 = IEEE754(num);
    printf("\n%s %c ", string, valIEEE754[0]);
    fwrite(valIEEE754 + 1, sizeof(char), 8, stdout);
    printf(" ");
    fwrite(valIEEE754 + 9, sizeof(char), 31, stdout);
    printf(" = %.22f", num);
}

int main(int argc, char *argv[])
{
    float num1 = strtof(argv[1], NULL);
    float num2 = strtof(argv[3], NULL);
    char op = argv[2][0]; // Pega o primeiro caractere do operador
    feclearexcept(FE_ALL_EXCEPT);
    float res = calc(num1, num2, op);
    printActualFlags();
    printIEEE(num1, "Valor 1: ");
    printIEEE(num2, "Valor 2: ");
    printIEEE(res, "Resultado: ");
    printf("\n%f %c %f = %f\n", num1, op, num2, res);
}