#include <vector>
#include <iostream>
#include <cmath>
#include <functional>

#include "PipeWrapper.h"

void plotGraph(const std::function<double_t(double_t)>& f, const std::vector<double_t>& xPoints) {
	PipeWrapper pipe("C:\\gnuplot\\bin\\gnuplot -persist", "w");

	pipe << "set datafile separator tab" << std::endl;
	pipe << "plot '-' using 1:2 title 'function' with lines" << std::endl;

	for (double_t x : xPoints) {
		double_t y = f(x);
		pipe << x << '\t' << y << std::endl;
	}
	pipe << 'e' << std::endl;

	pipe.close();
}



int main() {
	const uint32_t nPoints = 1000;
	const double_t pi = std::atan2(0, -1);
	const double_t left = -2 * pi;
	const double_t right = 2 * pi;

	std::vector<double_t> xPoints(nPoints);
	double_t x = left;
	double_t step = (right - left) / nPoints;
	for (uint32_t i = 0; i < nPoints; ++i) {
		xPoints[i] = x;
		x += step;
	}

	auto f = [](double_t x) -> double_t {
		return std::sin(x);
	};

	plotGraph(f, xPoints);

	return 0;
}