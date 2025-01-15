CXX         = /opt/llvm/19.1.4/bin/clang++
CXXFLAGS    = -std=c++20 -O2 -Wall -Wextra
PCHFLAGS    = -Wno-experimental-header-units -Wno-pragma-system-header-outside-header -xc++-system-header --precompile
PCMFLAGS    = -Wno-experimental-header-units -fprebuilt-module-path=. --precompile -fmodule-file=
CMFLAGS     = -fprebuilt-module-path. -c
HEADERS     = compare cstdint functional iostream limits memory queue regex stdexcept string vector unordered_map utility 
MODULES     = GenericCounter.o
TARGET      = counters

all: counters

iostream.pch: iostream
	$(CXX) $(CXXFLAGS) $(PCHFLAGS) $< -o $@

%.pcm: %.cppm $(HEADERS)
	$(CXX) $(CXXFLAGS) $(PCMFLAGS) $(HEADERS) $< -o $@

%.o: %.pcm
	$(CXX) $(CXXFLAGS) $(CMFLAGS) $< -o $@

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(TARGET).o $(MODULES) $(HEADERS)
	$(CXX) $< $(MODULES) -o $@

CounterModules.pcm: GenericCounter.pcm ModuloCounter.pcm
GenericCounter.pcm: Event.pcm
ModuloCounter.pcm: GenericCounter.pcm
CounterProcessor.pcm: CounterModules.pcm Event.pcm

counters:
	# TODO:

clean:
	rm -rf counters *.pch *.pcm *.o

.PHONY: all clean