SRCDIRS := $(wildcard */)
BUILDDIR := build
EXCLUDE := $(shell cat exclude_files)
ALL_SOURCES := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)*.c))
SOURCES := $(filter-out $(EXCLUDE), $(ALL_SOURCES))
TARGETS := $(patsubst %.c, $(BUILDDIR)/%, $(SOURCES))

CC := gcc
CFLAGS := -Wall -Werror

all: $(TARGETS)

$(BUILDDIR)/%: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $< -o $@
	@echo "$<"

clean:
	@rm -rf $(BUILDDIR)

.PHONY: all clean

