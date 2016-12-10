
OBJ_SUFFIX=o
PWD=$(shell pwd)
CPPUTEST=$(PWD)/cpputest
CPPFLAGS += -I$(CPPUTEST)/include -I$(PWD)/inc -g -Wall -Werror -o0
CFLAGS += -include $(CPPUTEST)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CXXFLAGS += -include $(CPPUTEST)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

VPATH += src
VPATH += tst

SRC_FILES = $(wildcard $(PWD)/src/*.cpp)
SRC_FILES += $(wildcard $(PWD)/src/*.c)
SRC_FILES += $(wildcard $(PWD)/tst/*.cpp)
SRC_FILES += $(wildcard $(PWD)/tst/*.c)
LD_LIBRARIES = -L$(CPPUTEST)/lib -lCppUTest -lCppUTestExt

objs-files = $(SRC_FILES:%.cpp=%.$(OBJ_SUFFIX)) $(PWD)/cpputest/main.$(OBJ_SUFFIX)

all: cpputest 
	@make test
	@./test

test:$(objs-files) 
	$(CXX) $^ $(LD_LIBRARIES) -o $@ 

clean:
	rm -f test src/*.o tst/*.o
	rm -rf cpputest

release:
	tar cjf CppUTestPrj_$(shell date +%Y-%02m-%02d).tar.bz2 cpputest.tar.bz2 inc src tst Makefile

cpputest:
	tar xjf cpputest.tar.bz2
