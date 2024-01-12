#include "sumpr2.h"

int strLen(char *str)
{
	int res = 0;
	for (res = 0; str[res] != '\0'; res++) continue;
	return res;
}

int strtoi(const char *str, char **p, int *ret)
{
	int base = 10;
	int count = 0, len = strlen(str);
	int ident = 0, identbase = 0;
	int checksymb = 0;
	bool negative = false;
	bool positive = false;

	if (str[count] == '-')
	{
		negative = true;
		if (str[count + 2] != 'x') //
		{
			str++; // если система счисления 10 - ная, чтоб не нарушились остальные проверки..
				   //...так как все завязано на str;
		}
		else
			count++;
	}

	if (str[count] == '+')
	{
		positive = true;
		if (str[count + 2] != 'x')
			str++;

		else
			count++;
	}
	//  if (positive || negative){
	// 	if(str[count] >= 48 && str[count] <= 57 && str[count+1] != 'x'){
	// 		str++;
	// 		count = 0;
	// 	}
	//  }

	if (str[count] >= '0' && str[count] <= '1' && str[count + 1] == 'x')
	{
		printf("Недопустимая система счисления\n");
		*p = (char *)&str[count];
		*ret = str[count];
		return 1;
	}

	if (str[count] >= '0' && str[count] <= '9' && str[count + 1] != 'x')
	{
		for (int i = 1; i < len - 2; i++) //-2 потому что без Y x
		{
			if (str[count] >= '0' && str[count] <= '9')
			{
				if (identbase == 0) base = base; // можно и просто continue
				identbase = 1;
				count++;
			}
			else
			{
				*p = (char *)&str[count];
				*ret = str[count]; // возвращает код символа из таблицы аски,который не проходит проверку return 1;
				return 1;
			}
		}
	}
	else if (str[count] >= '2' && str[count] <= '9')
	{
		for (int i = 0; i < len - 2; i++)
		{
			if (str[count] >= '0' && str[count] <= '9')
			{

				if (identbase == 0)
				{ // для определения системы счисления
					base = str[count] - '0';
				}
				identbase = 1;
				if (str[count] > (base + '0') && ident == 1)
				{
					*p = (char *)&str[count];
					*ret = str[count];
					return 1;
				}
				// str++;
				count++;
				if (checksymb == 0)
				{
					if (str[count] == 'x')
					{
						if (negative || positive)
						{
							str += 3; // перепрыгиваю на 3, для того, чтобы пропусти 1.знак 2.Систему счисления и 3.X
							count = 0;
						}
						else
						{
							str += 2; // перепрыгиваю на 2, если нет знака, пропуская Yx
							count = 0;
						}
						checksymb = 1;
					}
					else
					{
						return 1;
					}
					ident = 1; // это на проверку того, что значения после Yx не больше, чем система счисления
				}
			}
			else
			{
				*p = (char *)&str[count];
				*ret = str[count];
				return 1;
			}
		}
	}
	else if (str[count] >= 'A' && str[count] <= 'Z')
	{
		for (int i = 0; i < len - 2; i++)
		{

			if (str[count] >= 'A' && str[count] <= 'Z')
			{
				if (identbase == 0)
				{
					base = (str[count] - 'A' + 10); //+ 1
				}
				identbase = 1;
				if (str[count] > (base + 'A' - 10) && ident == 1)
				{
					*p = (char *)&str[count];
					*ret = str[count];
					return 1;
				}
				// str++;
				count++;

				if (checksymb == 0)
				{
					if (str[count] == 'x')
					{
						if (negative || positive)
						{
							str += 3;
							count = 0;
						}
						else
						{
							str += 2;
							count = 0;
						}
						checksymb = 1;
					}
					else
					{
						return 1;
					}
					ident = 1;
				}
			}
			else if (str[count] >= 48 && str[count] <= 57)
			{
				// str++;
				count++;
			}
			else
			{
				*p = (char *)&str[count];
				*ret = str[count];
				return 1;
			}
		}
	}
	else if (str[count] >= 'a' && str[count] <= 'z')
	{
		for (int i = 0; i < len - 2; i++) // было без -2
		{
			if (str[count] >= 'a' && str[count] <= 'z')
			{

				if (identbase == 0)
				{
					base = str[count] - 'a' + 36;
				}
				if (str[count] > (base + 'a' - 36) && ident == 1)
				{
					*p = (char *)&str[count];
					*ret = str[count];
				}
				// str++;
				count++;

				if (checksymb == 0)
				{
					if (str[count] == 'x')
					{
						if (negative || positive)
						{
							str += 3;
							count = 0;
						}
						else
						{
							str += 2;
							count = 0;
						}
						checksymb = 1;
					}
					else
					{
						return 1;
					}
					ident = 1;
				}
			}
			else if (str[count] >= 48 && str[count] <= 57)
			{
				// str++;
				count++;
			}
			else
			{
				*p = (char *)&str[count];
				*ret = str[count];
				return 1;
			}
		}
	}
	else if (str[count] == '!')
	{
		for (int i = 0; i < len - 2; i++)
		{
			if (((str[count] >= 'A') && (str[count] <= 'Z')) || (str[count] >= '0' && str[count] <= '9') || (str[count] >= 'a' && str[count] <= 'z') || (str[count] == 33) || (str[count] == 32))
			{
				base = 62;
				// str++;
				count++;

				if (checksymb == 0)
				{
					if (str[count] == 'x')
					{
						if (negative || positive)
						{
							str += 3;
							count = 0;
						}
						else
						{
							str += 2;
							count = 0;
						}
						checksymb = 1;
					}
					else
					{
						return 1;
					}
				}
			}
			else
			{
				*p = (char *)&str[count];
				*ret = str[count];
				return 1;
			}
		}
	}

	else
	{
		*p = (char *)&str[count];
		*ret = str[count];
		return 1;
	}

	int result = 0;

	count = 0;
	// if (base != 10) {
	//     for (int j = 0; j < len - 2; j++) // -2 т.к Yx
	//             str--;
	// }
	int space = 0;
	// после проверки на значения, переходим к    переводу из Y-системы счисления
	while (str[count] != '\0')
	{

		int digit = str[count];
		if (digit >= '0' && digit <= '9')
		{
			digit -= '0';
		}
		else if (digit >= 'A' && digit <= 'Z')
		{
			digit -= 'A' - 10;
		}
		else if (digit >= 'a' && digit <= 'z')
		{
			digit -= 'a' - 36;
		}
		else if (digit == 32)
		{
			space++;
			count++;
			continue;
		}
		else
		{
			*p = (char *)&str[count];
			*ret = str[count];

			return 1;
		}

		if (digit >= base) // проверяю здесь еще раз,для того,чтобы было все нормально,если вводить без X,те например просто 123;
		{

			*p = (char *)&str[count];
			*ret = str[count];

			return 1;
		}
		//result = result * base + digit;

		if (result < 0 && result == INT32_MIN)
		{
			if (!negative)
			{
				*ret = 0;
				return 2;
			}
			else
			{
				*p = 0;
				*ret = result;
				return 0;
			}
		}
		// заходим для того,чтобы посмотреть число за шаг до максимального
		if (result > (INT32_MAX) / base || (result == (INT32_MAX) / base && digit > (INT32_MAX) % base)) // сравниваем сначала как положительное число
		{

			if (negative == 1)
			{
				if ((result > (INT32_MAX) / base && digit > (INT32_MAX) % base))
				{
					*p = (char *)&str[count];
					*ret = str[count];

					return 2;
				}
				
			}
			else
			{
				
				*p = (char *)&str[count];
				*ret = str[count];
				return 2;
			}
		}
		result = result * base + digit;

		// result = result * base + digit;
		if (space == 1)
		{
			count++;
			continue;
		}
		else
			count++;
	}
	if (negative)
		result *= -1;

	*ret = result;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////// I T O A

int count_digits(int value, int p)
{
	int digits = 0;
	while (value != 0)
	{
		value /= p;
		digits++;
	}
	return digits;
}

int my_itoa(char *buf, int bufSize, int value, int p)
{
	if (buf == NULL)
	{
		// подсчитать необходимый размер буфера и вернуть его
		return 0;
	}
	if (bufSize == 0)
	{
		return 0;
	}
	int digits = count_digits(value, p);
	if (digits > bufSize)
	{
		// размера буфера не хватает
		return 0;
	}

	if (value == 0)
	{
		buf[0] = '0';
		return 1;
	}

	int i = digits - 1; // т.к идем по массиву,поэтому -1;
	while (value != 0)
	{
		int digit = value % p;
		if (digit < 10)
		{
			buf[i] = digit + '0';
		}
		else if (digit >= 10 && digit <= 35)
		{
			buf[i] = digit + 'A' - 10; // используем заглавные буквы для символов A-F
		}
		else if (digit >= 36 && digit <= 61)
		{
			buf[i] = digit + 'a' - 36;
		}
		else
		{
			printf("error\n");
			return 0;
		}
		value /= p;
		i--;
	}

	return digits;
}

////////////////////////////////////////////////////////////////////////////////////////C H E C K

void checkStrtoi()
{
	char *p0;
	int ret0;
	const char *str0 = "-Gx180000000" ;
	int i0 = strtoi(str0, &p0, &ret0);
	printf("p = %p\n %s error = %d\nret = %d\n\n", p0, str0, i0, ret0);

	char *p;
	int ret;
	const char *str = "2x010101201";
	int i = strtoi(str, &p, &ret);

	printf("p = %p\n %s error = %d\nret = %d\n\n", p, str, i, ret);

	char *p1;
	int ret1;
	const char *str1 = "Gx10F";
	int i1 = strtoi(str1, &p1, &ret1);

	printf("p = %p\n %s error = %d\nret = %d\n\n", p1, str1, i1, ret1);

	char *p2_1;
	int ret2_1;
	const char *str2_1 = "+123456";
	int i2_1 = strtoi(str2_1, &p2_1, &ret2_1);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p2_1, str2_1, i2_1, ret2_1);

	char *p2;
	int ret2;
	const char *str2 = "123456";
	int i2 = strtoi(str2, &p2, &ret2);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p2, str2, i2, ret2);
	char *p2_2;
	int ret2_2;
	const char *str2_2 = "-123456";
	int i2_2 = strtoi(str2_2, &p2_2, &ret2_2);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p2_2, str2_2, i2_2, ret2_2);

	char *p3;
	int ret3;
	const char *str3 = "-Fx56777AAAAAAA777";
	int i3 = strtoi(str3, &p3, &ret3);

	printf("p = %p\n %s error = %d\nret = %d\n\n", p3, str3, i3, ret3);

	char *p4;
	int ret4;
	const char *str4 = "!x1";
	int i4 = strtoi(str4, &p4, &ret4);

	printf("p = %p\n %s error = %d\nret = %d\n\n", p4, str4, i4, ret4);

	char *p5;
	int ret5;
	const char *str5 = "!x123";
	int i5 = strtoi(str5, &p5, &ret5);

	printf("p = %p\n %s error = %d\nret = %d\n\n", p5, str5, i5, ret5);

	char *p6;
	int ret6;
	const char *str6 = "=x1";
	int i6 = strtoi(str6, &p6, &ret6);

	printf("p = %p\n %s error = %d\nret = %d\n\n", p6, str6, i6, ret6);

	char *p7;
	int ret7;
	const char *str7 = "=5671";
	int i7 = strtoi(str7, &p7, &ret7);

	printf("p = %p\n %s error = %d\nret = %d\n\n", p7, str7, i7, ret7);

	char *p8;
	int ret8;
	const char *str8 = "!x12321";
	int i8 = strtoi(str8, &p8, &ret8);

	printf("p = %p\n %s error = %d\nret = %d\n\n", p8, str8, i8, ret8);

	char *p9;
	int ret9;
	const char *str9 = "54A7";
	int i9 = strtoi(str9, &p9, &ret9);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p9, str9, i9, ret9);

	char *p10;
	int ret10;
	const char *str10 = "-5x47";
	int i10 = strtoi(str10, &p10, &ret10);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p10, str10, i10, ret10);

	char *p11;
	int ret11;
	const char *str11 = "-5x41";
	int i11 = strtoi(str11, &p11, &ret11);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p11, str11, i11, ret11);

	char *p12;
	int ret12;
	const char *str12 = "-x41";
	int i12 = strtoi(str12, &p12, &ret12);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p12, str12, i12, ret12);

	char *p13;
	int ret13;
	const char *str13 = "!x123qweASD";
	int i13 = strtoi(str13, &p13, &ret13);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p13, str13, i13, ret13);

	char *p14;
	int ret14;
	const char *str14 = "-xx5";
	int i14 = strtoi(str14, &p14, &ret14);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p14, str14, i14, ret14);

	char *p15;
	int ret15;
	const char *str15 = "!x10";
	int i15 = strtoi(str15, &p15, &ret15);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p15, str15, i15, ret15);

	char *p16;
	int ret16;
	const char *str16 = "!x10    !x10";
	int i16 = strtoi(str16, &p16, &ret16);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p16, str16, i16, ret16);

	char *p17;
	int ret17;
	const char *str17 = "!x10 ";
	int i17 = strtoi(str17, &p17, &ret17);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p17, str17, i17, ret17);

	char *p18;
	int ret18;
	const char *str18 = "!x10 !x10";
	int i18 = strtoi(str18, &p18, &ret18);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p18, str18, i18, ret18);

	char *p19;
	int ret19;
	const char *str19 = "AAAx10";
	int i19 = strtoi(str19, &p19, &ret19);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p19, str19, i19, ret19);

	char *p20;
	int ret20;
	const char *str20 = "-Gx80000000";
	int i20 = strtoi(str20, &p20, &ret20);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p20, str20, i20, ret20);

	char *p21;
	int ret21;
	const char *str21 = "-Gx8000000";
	int i21 = strtoi(str21, &p21, &ret21);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p21, str21, i21, ret21);

	char *p22;
	int ret22;
	const char *str22 = "-2147483648";
	int i22 = strtoi(str22, &p22, &ret22);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p22, str22, i22, ret22);

	char *p23;
	int ret23;
	const char *str23 = "-2147483647";
	int i23 = strtoi(str23, &p23, &ret23);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p23, str23, i23, ret23);

	char *p24;
	int ret24;
	const char *str24 = "1000000000000000000000000000000000000000000000000000000000000000000000";
	int i24 = strtoi(str24, &p24, &ret24);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p24, str24, i24, ret24);

	char *p25;
	int ret25;
	const char *str25 = "2147483649";
	int i25 = strtoi(str25, &p25, &ret25);

	printf("p = %p\n%s error = %d\nret = %d\n\n", p25, str25, i25, ret25);
}
// 10 - A 11 -B 12 -C 13 -D 14 -E 15 -F 16 -G

void checkItoa()
{

	int value = 62008, p = 62, bufSize = 0;
	char *buf;
	if (bufSize == 0)
	{
		buf = 0;
	}
	else
	{
		buf = malloc(bufSize);
	}

	int numDigits = my_itoa(buf, bufSize, value, p);
	if (numDigits == 0)
	{
		printf("Размера буфера не хватает.\nРазмер буфера должен быть не менее %d\n\n", count_digits(value, p));
	}
	else
	{
		printf("Число %d в системе счисления %d: ", value, p);
		for (int i = 0; i < numDigits; i++)
		{
			printf("%c", buf[i]);
		}
		printf("\n");
	}
	printf("\n");

	free(buf);

	int value1 = 62008, p1 = 62, bufSize1 = 3;
	char *buf1 = (char *)malloc(bufSize1);

	int numDigits1 = my_itoa(buf1, bufSize1, value1, p1);
	if (numDigits1 == 0)
	{
		printf("Размера буфера не хватает.\nРазмер буфера должен быть не менее %d\n\n", count_digits(value1, p1));
	}
	else
	{
		printf("Число %d в системе счисления %d: ", value1, p1);
		for (int i = 0; i < numDigits1; i++)
		{
			printf("%c", buf1[i]);
		}
		printf("\n");
	}
	printf("\n");

	free(buf1);

	int value2 = 61, p2 = 62, bufSize2 = 2;
	char *buf2 = malloc(bufSize2);

	int numDigits2 = my_itoa(buf2, bufSize2, value2, p2);
	if (numDigits2 == 0)
	{
		printf("Размера буфера не хватает.\nРазмер буфера должен быть не менее %d\n\n", count_digits(value2, p2));
	}
	else
	{
		printf("Число %d в системе счисления %d: ", value2, p2);
		for (int i = 0; i < numDigits2; i++)
		{
			printf("%c", buf2[i]);
		}
		printf("\n");
	}
	printf("\n");

	free(buf2);
}

void menu()
{
	setlocale(LC_ALL, "RUS");

	printf("        Возвращаемые значения : \n"
		   "0 - успех\n"
		   "1 - недопустимые символы в строке(не соответствующие алфавиту)\n"
		   "2 - переполнение int(слишком большое или слишком маленькое число)\n\n\n");
}