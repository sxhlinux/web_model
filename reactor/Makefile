SRCS = main.cpp

OBJS = $(addprefix $(DIST_DIR),$(SRCS:.cpp=.o))
DEPS = $(addprefix $(DIST_DIR),$(SRCS:.cpp=.d))

TAR = reactor

${TAR}: ${OBJS}
	g++ $^ -o $@ ${LDFLAGS} 

$(DIST_DIR)%.o:%.cpp
	@test -d $(DIST_DIR) || mkdir -p $(DIST_DIR)
	g++ ${CXXFLAGS} -c $< -o $@

#可自动展开为 %d:%c 的关系
-include $(DEPS)
