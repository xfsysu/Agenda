//division.cpp

#include <stdexcept>
#include <iostream>
#include "division.h"
using namespace std;

float myns::divide(float dividend, float divisor) throw(domain_error) {
	if (divisor == 0) {
		throw domain_error("Divisor cannot be 0");
	}
	return dividend / divisor;
}