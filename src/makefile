include prorab.mk

this_out_dir := build

this_name := $(shell cat $(d)../name.txt)

this_soname := $(shell cat $(d)../soname.txt)

this_headers_dir := agg/include

this_install_cxx_hdrs := $(patsubst $(d)%,%,$(wildcard $(d)$(this_headers_dir)/*.h))

# exclude gpc.h dependent functionality from the library
this_install_cxx_hdrs := $(filter-out %agg_conv_gpc.h,$(this_install_cxx_hdrs))

this_headers_install_dir := agg # TODO: make it $(this_name) when library is renamed to agg

this_srcs += $(patsubst $(d)%,%,$(wildcard $(d)agg/src/*.cpp))

this_cxxflags += -I $(d)agg/include
this_cxxflags += -fPIC

this_ldlibs += -lstdc++

$(eval $(prorab-build-lib))
