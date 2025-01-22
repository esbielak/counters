CXX         = /opt/llvm/19.1.4/bin/clang++
CXXFLAGS    = -std=c++20 -O2 -Wall -Wextra -Wno-experimental-header-units 
PCHFLAGS    = -Wno-pragma-system-header-outside-header -xc++-system-header --precompile
PCMFLAGS    = -fprebuilt-module-path=. --precompile
CMFLAGS     = -fprebuilt-module-path=. -c
HEADERS     =compare cstdint functional iostream limits memory queue regex stdexcept string vector unordered_map utility  
MODULES     =CounterModules.pcm GenericCounter.pcm ModuloCounter.pcm Event.pcm CountersProcessor.pcm FibonacciCounter.pcm GeometricCounter.pcm counters.pcm
TARGET      = counters

PRECOMPILED_HEADERS = $(addsuffix .pch, $(HEADERS))

SRCS = $(wildcard *.cppm *.cpp)
OBJS := $(patsubst %, %, $(patsubst %.cppm, %.o, $(patsubst %.cpp, %.o, $(SRCS))))

all: $(TARGET)

%.pch:
	$(CXX) $(CXXFLAGS) $(PCHFLAGS) $* -o $@

%.pcm: %.cppm $(PRECOMPILED_HEADERS)
	$(CXX) $(CXXFLAGS) $(PCMFLAGS) $(addprefix -fmodule-file=, $(PRECOMPILED_HEADERS)) $< -o $@

%.o: %.pcm
	$(CXX) $(CXXFLAGS) $(CMFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

# Module dependencies
CounterModules.pcm: GenericCounter.pcm ModuloCounter.pcm FibonacciCounter.pcm GeometricCounter.pcm $(PRECOMPILED_HEADERS)
GenericCounter.pcm: Event.pcm $(PRECOMPILED_HEADERS)
ModuloCounter.pcm: GenericCounter.pcm Event.pcm $(PRECOMPILED_HEADERS)
FibonacciCounter.pcm: GenericCounter.pcm Event.pcm $(PRECOMPILED_HEADERS)
GeometricCounter.pcm: GenericCounter.pcm Event.pcm $(PRECOMPILED_HEADERS)
CountersProcessor.pcm: CounterModules.pcm Event.pcm $(PRECOMPILED_HEADERS)
counters.pcm: CountersProcessor.pcm $(PRECOMPILED_HEADERS)

clean:
	rm -rf $(TARGET) *.pch *.pcm *.o

.PHONY: all clean
