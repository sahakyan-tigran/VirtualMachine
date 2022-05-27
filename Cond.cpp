#include "Cond.h"

bool Cond::never(int arg1, int arg2) {
	return false;
}

bool Cond::equal(int arg1, int arg2) {
	return arg1 == arg2;
}

bool Cond::less(int arg1, int arg2) {
	return arg1 < arg2;
}

bool Cond::lessOrEqual(int arg1, int arg2) {
	return arg1 <= arg2;
}

bool Cond::always(int arg1, int arg2) {
	return true;
}

bool Cond::notEqual(int arg1, int arg2) {
	return arg1 != arg2;
}

bool Cond::bigOrEqual(int arg1, int arg2) {
	return arg1 >= arg2;
}

bool Cond::big(int arg1, int arg2) {
	return arg1 > arg2;
}