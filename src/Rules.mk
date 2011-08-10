.PHONY: src_all src_clean src_distclean

SUFFIXES += .d

SUBDIRS := $(DIR) $(DIR)/JSON
src_EXEC := $(DIR)/a.out
src_SRCS := $(foreach D,$(SUBDIRS),$(wildcard $D/*.cpp))
src_OBJS := $(src_SRCS:.cpp=.o)
src_DEPS := $(src_SRCS:.cpp=.d)

-include $(src_DEPS)

src_all: $(src_EXEC) res_all

$(src_EXEC): $(src_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(src_OBJS) -o $(src_EXEC)

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -MM -MT '$(patsubst %.cpp,%.o,$<)' $< >$@

%.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

src_clean:
	rm -rf $(src_OBJS) $(src_DEPS)

src_distclean: src_clean
	rm -rf $(src_EXEC)
