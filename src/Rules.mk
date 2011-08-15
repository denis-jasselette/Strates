.PHONY: src_all src_clean src_distclean

SUFFIXES += .d

SUBDIRS := $(DIR) $(DIR)/JSON
src_EXEC := $(DIR)/a.out
src_SRCS := $(foreach D,$(SUBDIRS),$(wildcard $D/*.cpp))
src_HDRS := $(foreach D,$(SUBDIRS),$(wildcard $D/*.h))
src_OBJS := $(src_SRCS:.cpp=.o)
src_DEPS := $(src_SRCS:.cpp=.d)

-include $(src_DEPS)

src_all: $(src_EXEC)

$(src_EXEC): $(src_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(src_OBJS) -o $(src_EXEC)

%.d: %.cpp
	@echo Building dependency file for $<
	@$(SHELL) -ec '$(CXX) -MM $< \
	              | sed '\''s#\.o[ :]*#.o $@ : #g'\'' > $@; \
	              [ -s $@ ] || rm -f $@'

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src_clean:
	rm -rf $(src_OBJS) $(src_DEPS)

src_distclean: src_clean
	rm -rf $(src_EXEC)

$(DOC): $(src_HDRS) $(src_SRCS)
