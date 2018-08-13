#pragma once
#include "stdafx.h"

array Signum(array input) {
	int height = input.dims(0);
	int width = input.dims(1);
	array positive = (input > 0) * 1.0;
	array negative = (input < 0) * -1.0;
	array result = constant(0,height,width);
	return result + positive + negative;
}
