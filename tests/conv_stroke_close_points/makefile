include prorab.mk

this_name := tests

this_srcs := main.cpp

this_no_install := true

this_agg_name := $(shell cat $(d)../../name.txt)

this_ldflags += -L $(d)../../src/build
this_ldlibs += -l$(this_agg_name)

this_ldlibs += -lstdc++

$(eval $(prorab-build-app))

$(prorab_this_name): $(abspath $(d)../../src/build/lib$(this_agg_name)$(dot_so))

include $(d)../test_target.mk

$(eval $(call prorab-include, ../../src/makefile))
