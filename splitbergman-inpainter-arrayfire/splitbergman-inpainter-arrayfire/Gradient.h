#pragma once
#include "stdafx.h"

//using ArrayFire built-in grad
array Gradient(array u)
{
	array ux, uy;
	grad(ux, uy, u);
	return join(0, ux, uy);
}