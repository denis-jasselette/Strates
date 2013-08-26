CXX := g++

CXXFLAGS := -g -Wall
LDFLAGS := -lm -lsfml-graphics -lsfml-system -lsfml-window

EXEC := a.out
EXPORT := export.tar.gz
DOC := doc
DIST = $(wildcard *)

all: $(EXEC) src_all res_all

clean: src_clean res_clean
	rm -rf $(EXEC)

distclean: clean src_distclean res_distclean
	rm -rf $(DOC)
	rm -rf $(EXPORT)

dist: distclean
	tar czf $(EXPORT) $(DIST)

$(DOC): Doxyfile
	doxygen

DIR := src
include src/Rules.mk
DIR := res
include res/Rules.mk

$(EXEC): $(src_EXEC)
	cp -a $(src_EXEC) $(EXEC)
