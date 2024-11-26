#include <agg/agg_trans_affine.h>

#include <iostream>

int main(int argc, const char** argv){
    agg::trans_affine t(10, 20, 30, 40, 50, 60);

    t.reset();

    std::cout << "t = " << t.sx << ", " << t.sy << ", " << t.tx << ", " << t.ty << ", " << t.shx << ", " << t.shy << std::endl;

    return 0;
}
