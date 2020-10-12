include prorab.mk

this_out_dir := build

this_name := agg

this_soname := $(shell cat $(d)soname.txt)

this_srcs += $(patsubst $(d)%,%,$(wildcard $(d)code/src/*.cpp))

this_cxxflags += -I $(d)code/include
this_cxxflags += -fPIC

$(eval $(prorab-build-lib))
