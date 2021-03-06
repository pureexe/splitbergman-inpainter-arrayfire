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


	//setBackend(AF_BACKEND_CUDA);
	setBackend(AF_BACKEND_OPENCL);

	array toInpaintImage = loadImage("../../images/256x256/case3_toinpaint.png");
	array inpaintDomainImage = loadImage("../../images/256x256/case3_inpaintdomain.png");
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
