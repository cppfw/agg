#include <iostream>
#include <iomanip>
#include <cassert>

#include "../../src/agg/include/agg_path_storage.h"
#include "../../src/agg/include/agg_conv_dash.h"

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

	unsigned last_dashed_path_cmd;

	dashed_path.rewind(0);
	std::cout << "print dashed_path:" << std::endl;
	{
		double x, y;
		for(auto cmd = dashed_path.vertex(&x, &y); cmd != agg::path_cmd_stop; cmd = dashed_path.vertex(&x, &y)){
			std::cout << std::setprecision(20) << std::hex << "cmd = 0x" << cmd << std::dec << ", xy = (" << x << ", " << y << ")" << std::endl;
			last_dashed_path_cmd = cmd;
		}
	}

	std::cout << "last dashed path cmd = 0x" << std::hex << last_dashed_path_cmd << std::endl;

	// the last dashed path command should remain close command
	assert(last_dashed_path_cmd == unsigned(agg::path_cmd_end_poly | agg::path_flags_close));

	return 0;
}
