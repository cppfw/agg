#include <iostream>
#include <iomanip>
#include <cassert>

#include "../../src/agg/include/agg/agg_path_storage.h"
#include "../../src/agg/include/agg/agg_conv_dash.h"

int main(int argc, const char** argv){

	agg::path_storage path;

	path.move_to(10, 20);
	path.hline_rel(30);
	path.vline_rel(30);
	path.close_polygon();

	agg::conv_dash<decltype(path)> dashed_path(path);

	dashed_path.add_dash(80, 5);

	path.rewind(0);
	std::cout << "print path:" << std::endl;
	{
		double x, y;
		for(auto cmd = path.vertex(&x, &y); cmd != agg::path_cmd_stop; cmd = path.vertex(&x, &y)){
			std::cout << std::setprecision(20) << std::hex << "cmd = 0x" << cmd << std::dec << ", xy = (" << x << ", " << y << ")" << std::endl;
		}
	}

	dashed_path.rewind(0);
	std::cout << "print dashed_path:" << std::endl;
	{
		double x, y;
		for(auto cmd = dashed_path.vertex(&x, &y); cmd != agg::path_cmd_stop; cmd = dashed_path.vertex(&x, &y)){
			std::cout << std::setprecision(20) << std::hex << "cmd = 0x" << cmd << std::dec << ", xy = (" << x << ", " << y << ")" << std::endl;
		}
	}

	return 0;
}
