SrcDir :=
SourceFiles := $(wildcard *.cpp)
ObjectFiles := $(SourceFiles:%.cpp=%.o)
# DependFiles := $(SourceFiles:%.cpp=%.d)
ExecuteFile := ./uct.out

Compiler := g++
Linker := g++

CompileOption := -std=c++11
LinkOption :=

.PHONY: all clean

all : $(ExecuteFile)

$(ExecuteFile) : $(ObjectFiles)
	$(EchoTarget)
	$(At) $(Linker) $(LinkOption) $(ObjectFiles) -o $(ExecuteFile)

%.o : %.cpp Makefile
	$(At) $(EchoTarget)
	$(At) $(Compiler) $(CompileOption) -c $< -o $@

clean :
	$(EchoTarget)
	$(At) rm -fv $(ExecuteFile) $(ObjectFiles) $(ExecuteFile).stackdump
