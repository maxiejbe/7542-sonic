#include "Validator.h"

bool Validator::IntGreaterThanOrEqualToZero(int number)
{
	return IntGreaterThanZero(number) || IntEqualToZero(number);
}

bool Validator::IntGreaterThanZero(int number)
{
	return number > 0;
}

bool Validator::IntEqualToZero(int number)
{
	return number == 0;
}
