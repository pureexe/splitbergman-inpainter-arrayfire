// splitbergman-inpainter-arrayfire.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SplitBergmanSolver.h"

#include "Gradient.h"
#include "Divergence.h"
#include "uSolver.h"
#include "Signum.h"

void application();
void TaskTest();

int main()
{
	application();
    return 0;
	
}

void application()
{
	//defined related variable
	double lambda = 250;
	double theta = 5;
	double tolerant = 1e-6;
	int max_iteration = 10000;


	setBackend(AF_BACKEND_CUDA);

	array toInpaintImage = loadImage("../../images/256x256/case2_toinpaint.png");
	array inpaintDomainImage = loadImage("../../images/256x256/case2_inpaintdomain.png");
	toInpaintImage = toInpaintImage / 255;
	array lambdaDomain = ((inpaintDomainImage < 1) * lambda) / 1.0;
	timer::start();
	array resultImage = SplitBergmanSolver(toInpaintImage, lambdaDomain, theta, tolerant, max_iteration);
	printf("Inpainting time %g seconds\n", timer::stop());
	resultImage *= 255;
	Window resultWindows(256, 256, "ResultImage");
	do {
		resultWindows.image(resultImage.as(u8));
	} while (!resultWindows.close());
}

array wSolverTest(array u, array b, double theta) {
	int height = u.dims(0);
	int width = u.dims(1);
	array gradB = Gradient(u) + b;
	array w = abs(gradB) - (1.0 / theta);
	array zeroMatrix = constant(0, height * 2, width, f64);
	w = max(w, zeroMatrix) *Signum(gradB);
	return w;
}

void TaskTest() {
	//Gradient Test
	float Data[] = { 9, 2, 4, 1, 2, 9, 9, 8, 8 };
	float Lambda[] = { 5,5,5,5,0,5,5,5,5 };
	array data(3, 3, Data);
	array lambda(3, 3, Lambda);
	array zero_grad = constant(0, 6, 3,f64);
	/*
	af_print(Divergence(Gradient(data)));
	*/
	//UsolverTest
	//array uResult = uSolver(data, zero_grad, data, zero_grad, lambda, 5);
	//WsolverTest
	array wResult = wSolverTest(data*1.0, zero_grad*1.0, 5.0);
	af_print(wResult);
}