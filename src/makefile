include prorab.mk

this_out_dir := build

this_name := $(shell cat $(d)../name.txt)

this_soname := $(shell cat $(d)../soname.txt)

this_headers_dir := agg/include/agg

this_install_cxx_hdrs := $(patsubst $(d)%,%,$(wildcard $(d)$(this_headers_dir)/*.h))

# exclude gpc.h dependent functionality from the library
this_install_cxx_hdrs := $(filter-out %agg_conv_gpc.h,$(this_install_cxx_hdrs))

this_headers_install_dir := agg # TODO: make it $(this_name) when library is renamed to agg

this_srcs += $(patsubst $(d)%,%,$(wildcard $(d)agg/src/*.cpp))

this_cxxflags += -I $(d)agg/include/agg
this_cxxflags += -fstrict-aliasing # in order to comply with the c++ standard more strictly
this_cxxflags += -fPIC

# On CI build fails with:
#   error: argument unused during compilation: '-fstack-clash-protection' [clang-diagnostic-unused-command-line-argument,-warnings-as-errors]
# Disable the warning.
this_cxxflags += -Wno-unused-command-line-argument

this_ldlibs += -lstdc++

# Run lint only on Debian, because Ubuntu's version can be unstable
ifeq ($(os),linux)
    ifeq ($(shell lsb_release --short --id),Debian)
        this_lint_cmd = $(prorab_lint_cmd_clang_tidy)
    endif
endif

$(eval $(prorab-build-lib))
