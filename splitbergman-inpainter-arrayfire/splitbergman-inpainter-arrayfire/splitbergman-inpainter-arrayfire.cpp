// splitbergman-inpainter-arrayfire.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SplitBergmanSolver.h"

int main()
{
	//defined related variable
	double lambda = 250;
	double theta = 5;
	double tolerant = 1e-6;
	int max_iteration = 10000;


	setBackend(AF_BACKEND_CUDA);

	array toInpaintImage = loadImage("../../images/256x256/case2_toinpaint.png");
	array inpaintDomainImage = loadImage("../../images/256x256/case2_inpaintdomain.png");
	array originalImage = loadImage("../../images/256x256/case2_original.png");
	toInpaintImage = toInpaintImage / 255;
	originalImage = originalImage / 255;
	array lambdaDomain = ((inpaintDomainImage < 1) * lambda) / 1.0;
	array resultImage = SplitBergmanSolver(toInpaintImage, lambdaDomain, theta, tolerant, max_iteration);
	/*Window resultWindows(256, 256, "ResultImage");
	do {
		resultWindows.image(resultImage);
	} while (!resultWindows.close());*/
	af_print(resultImage);
    return 0;
}

