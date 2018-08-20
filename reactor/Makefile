#-MMD 自动生成包含obj文件与源文件、头文件依赖关系的.d后缀文件
#这样就解决了修改头文件不触发make重新编译的问题
CXXFLAGS = -MMD -MP -I./include -I. --std=c++11 -Wall -Werror -fPIC -fsanitize=address -fno-omit-frame-pointer

#-Wl,-rpath与 -L分别是在链接和运行时生效， $$ORIGIN是一个表示当前目录的宏
LDFLAGS = -lpthread -lasan

DIST_DIR = tmp/

SRCS = main.cpp

#替换SRCS中.cpp后缀为.o，并赋值给OBJS
OBJS = $(addprefix $(DIST_DIR),$(SRCS:.cpp=.o))
DEPS = $(addprefix $(DIST_DIR),$(SRCS:.cpp=.d))

TAR = reactor

#默认生成debug文件
debug: CXXFLAGS += -g3 -O0 -fno-inline
debug: cli ${TAR}

opt: CXXFLAGS += -O3 -funroll-loops
opt: cli ${TAR}

${TAR}: ${OBJS}
	g++ $^ -o $@ ${LDFLAGS} 

$(DIST_DIR)%.o:%.cpp
	g++ ${CXXFLAGS} -c $< -o $@

#可自动展开为 %d:%c 的关系
-include $(DEPS)

.PHONY: cli clean
cli:
	@echo -e "\e[1;33m ############`date`############################################\e[0m"
	@test -d $(DIST_DIR) || mkdir -p $(DIST_DIR)

clean:
	@rm -rf ${TAR} *.o *.d tmp
