.PHONY: src_all src_clean src_distclean

src_EXEC := $(DIR)/a.out
src_SRCS := $(wildcard $(DIR)/*.cpp)
src_OBJS := $(src_SRCS:.cpp=.o)

src_all: $(src_EXEC) res_all

$(src_EXEC): $(src_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(src_OBJS) -o $(src_EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

src_clean:
	rm -rf $(src_OBJS)

src_distclean: src_clean
	rm -rf $(src_EXEC)
