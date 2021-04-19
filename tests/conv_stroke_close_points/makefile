include prorab.mk
include prorab-test.mk

this_name := tests

this_srcs := main.cpp

this_no_install := true

this_agg_name := $(shell cat $(d)../../name.txt)

this_cxxflags += -g
this_cxxflags += -std=c++11

this_ldflags += -L $(d)../../src/build
this_ldlibs += -l$(this_agg_name)

this_ldlibs += -lstdc++

$(eval $(prorab-build-app))

$(prorab_this_name): $(abspath $(d)../../src/build/lib$(this_agg_name)$(dot_so))

this_test_cmd := $(prorab_this_name)
this_test_deps := $(prorab_this_name)
this_test_ld_path := ../../src/build
$(eval $(prorab-test))

$(eval $(call prorab-include, ../../src/makefile))
