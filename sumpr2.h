#pragma once    

//#define INT32_MIN (-INT32_MAX-1)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

int strtoi(const char* str, char** p, int* ret);
int strLen(char* str);
void checkStrtoi();

int my_itoa(char* buf, int bufSize, int value, int p);
int count_digits(int value,int p);
void checkItoa();

void menu();

