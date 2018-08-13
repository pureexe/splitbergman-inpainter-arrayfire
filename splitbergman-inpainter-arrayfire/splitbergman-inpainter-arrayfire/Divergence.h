#pragma once
#include "stdafx.h"

array Divergence(array T) {
	int total_height = T.dims(0);
	int height = total_height / 2;
	array T1 = T.rows(0, height-1);
	array T2 = T.rows(height, total_height-1);
	array Tx = join(0, T1.row(0), diff1(T1, 0));
	array Ty = join(1,T2.col(0),diff1(T2, 1));
	return Tx + Ty;
}