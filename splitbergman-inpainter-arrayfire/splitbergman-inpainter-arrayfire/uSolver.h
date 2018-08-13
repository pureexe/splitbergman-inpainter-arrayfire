#pragma once
#include "stdafx.h"
#include "Divergence.h"

array uSolver(array u, array w, array original_image, array b, array lambda, double theta) {
	float lapacianFilterMatrix[]  = { 0, 1, 0, 1, 0, 1, 0, 1, 0 };
	array lapacianKernel(3, 3, lapacianFilterMatrix);
	array lapacian;
	array divergence = Divergence(w - b);
	for (int i = 0; i < 10; i++) {
		lapacian = convolve2(u, lapacianKernel);
		u = (1 / (lambda + 4 * theta)) * (lambda*original_image - theta*divergence + theta*lapacian);
	}	
	return u;
}