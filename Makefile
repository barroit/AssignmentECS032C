getname = $(patsubst %.c,%,$(firstword $(subst @, ,$(combine))))
getdep = $(word 2, $(subst @, ,$(combine)))

CC := gcc
CFLAGS := -Wall -Werror

SRCDIRS := $(wildcard hw*/)
BUILDDIR := build

ALL_SOURCES := $(foreach subdir,$(SRCDIRS),$(wildcard $(subdir)*.c))
EXCLUDES := $(shell cat exclude_files)
COMBINES := $(shell cat link_files)

SINGLE_INPUT_TARGETS := $(patsubst %.c,$(BUILDDIR)/%,$(filter-out $(EXCLUDES),$(ALL_SOURCES)))

MULTI_INPUT_TARGETS := $(foreach combine,$(COMBINES),$(BUILDDIR)/$(getname))

all: $(SINGLE_INPUT_TARGETS) $(MULTI_INPUT_TARGETS)

define MULTI_INPUT_BUILD_RULE
$(BUILDDIR)/$(1): $(2) $(1).c
	@mkdir -p $$(dir $$@)
	@$$(CC) $$(CFLAGS) $$^ -o $$@
	@echo $$@
endef

$(foreach combine,$(COMBINES),$(eval $(call MULTI_INPUT_BUILD_RULE,$(getname),$(getdep))))

$(BUILDDIR)/%: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $< -o $@
	@echo $@

clean:
	@rm -rf $(BUILDDIR)

.PHONY: all clean
