#include <iostream>
#include <iomanip>
#include <cassert>

#include "../../src/agg/include/agg_path_storage.h"
#include "../../src/agg/include/agg_conv_stroke.h"

int main(int argc, const char** argv){

	agg::path_storage path;

	path.move_to(130, 20);
	path.line_to(170, 20);
	path.line_to(169.99999868865830877, 20.000000000000014211);

	path.rewind(0);
	std::cout << "print path:" << std::endl;
	{
		double x, y;
		for(auto cmd = path.vertex(&x, &y); cmd != agg::path_cmd_stop; cmd = path.vertex(&x, &y)){
			std::cout << std::setprecision(20) << "cmd = " << cmd << ", xy = (" << x << ", " << y << ")" << std::endl;
		}
	}

	agg::conv_stroke<decltype(path)> stroke(path);
	stroke.width(10);
	stroke.line_join(agg::line_join_e::miter_join);
	stroke.line_cap(agg::line_cap_e::butt_cap);

	stroke.rewind(0);

	std::cout << "print stroke:" << std::endl;
	{
		double x, y;
		for(auto cmd = stroke.vertex(&x, &y); cmd != agg::path_cmd_stop; cmd = stroke.vertex(&x, &y)){
			std::cout << std::setprecision(20) << "cmd = " << cmd << ", xy = (" << x << ", " << y << ")" << std::endl;
		}
	}

	return 0;
}
