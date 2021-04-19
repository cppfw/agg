#include <iostream>

#include <agg/agg_trans_affine.h>

int main(int argc, const char** argv){
	agg::trans_affine a1, a2;

	a1.multiply(a2);

	std::cout << "Hello AGG!" << '\n';
}
