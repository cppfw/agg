include prorab.mk

this_out_dir := build

this_name := $(shell cat $(d)name.txt)

this_soname := $(shell cat $(d)soname.txt)

this_headers_dir := code/include/

this_install_cxx_hdrs := $(patsubst $(d)%,%,$(wildcard $(d)code/include/*.h))

# exclude gpc.h dependent functionality from the library
this_install_cxx_hdrs := $(filter-out %agg_conv_gpc.h,$(this_install_cxx_hdrs))

this_headers_install_dir := agg # TODO: make it $(this_name) when library is renamed to agg

this_srcs += $(patsubst $(d)%,%,$(wildcard $(d)code/src/*.cpp))

this_cxxflags += -I $(d)code/include
this_cxxflags += -fPIC

$(eval $(prorab-build-lib))


$(eval $(call prorab-include, pkg-config/makefile))
