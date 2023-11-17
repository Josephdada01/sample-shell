#include <stdio.h>

/**
 * add_numbers - Adds two numbers and returns the result
 * @a: The first number to be added
 * @b: The second number to be added
 *
 * Return: The sum of the two numbers
 */
int add_numbers(int a, int b)
{
	int sum;

	sum = a + b;
	return sum;
}

/**
 * main - Entry point of the program
 *
 * Return: Always 0
 */
int main(void)
{
	int num1 = 10;
	int num2 = 20;
	int result;

	result = add_numbers(num1, num2);
	printf("The sum of %d and %d is: %d\n", num1, num2, result);

	return 0;
}

