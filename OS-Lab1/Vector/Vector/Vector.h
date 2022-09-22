#pragma once

#ifdef VECTORDLL_EXPORTS
#define VECTORDLL __declspec(dllexport)
#else
#define VECTORDLL __declspec(dllimport)
#endif

#include<Number.h>
#include<cmath>
using namespace number;

namespace vector {
	class VECTORDLL Vector {
	public:
		Vector(Number x, Number y);
		Number getR();
		Number getFi();
		Vector operator+ (const Vector& secondVector);
	private:
		Number x;
		Number y;
	};
	 
	const Vector ZERO = Vector(0, 0);
	const Vector ONE = Vector(1, 1);
}

