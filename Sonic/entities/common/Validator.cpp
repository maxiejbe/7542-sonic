#include "Validator.h"

bool Validator::intGreaterThanOrEqualToZero(int number)
{
	return intGreaterThanZero(number) || intEqualToZero(number);
}

bool Validator::intGreaterThanZero(int number)
{
	return number > 0;
}

bool Validator::intEqualToZero(int number)
{
	return number == 0;
}
