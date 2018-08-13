#pragma once
#include "stdafx.h"
#include "Divergence.h"

//	u = (1 ./ (lambda + 4*theta)) .* (lambda .*original_image - theta .* divergence + theta .* lapacian);  % remove h^2 for speed improve   

array uSolver(array u, array w, array original_image, array b, array lambda, double theta) {
	float lapacianFilterMatrix[]  = { 0, 1, 0, 1, 0, 1, 0, 1, 0 };
	array lapacianKernel(3, 3, lapacianFilterMatrix);
	array lapacian;
	array divergence = Divergence(w - b);
	for (int i = 0; i < 10; i++) {
		
		lapacian = convolve2(u, lapacianKernel);
		lapacian.row(0) += u.row(0);
		lapacian.col(0) += u.col(0);
		lapacian.row(end) += u.row(end);
		lapacian.col(end) += u.col(end);


		u = (1 / (lambda + 4 * theta)) * (lambda  * original_image - theta * divergence + theta * lapacian);
	}	
	return u;
}
