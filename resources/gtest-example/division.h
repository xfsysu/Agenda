//division.h


#ifndef DIVISION_H
#define DIVISION_H

#include <stdexcept>

namespace myns {
	float divide(float dividend, float divisor) throw(std::domain_error);
}

#endif /* DIVISION_H */