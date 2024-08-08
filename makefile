SOURCES = cache_sim.cpp cache_types.cpp cache_hierarchy.cpp
FLAGS = -Wall -Wextra -g
# BINDIR = .
SRCDIR = source
SRC := $(wildcard $(SRCDIR)/*.cpp)

.PHONY: debug
debug: FLAGS += -ggdb -3 -DDEBUG
debug: 


