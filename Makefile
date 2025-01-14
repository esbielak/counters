CXX         = /opt/llvm/19.1.4/bin/clang++
CXXFLAGS    = -std=c++20 -O2 -Wall -Wextra
PCHFLAGS    = -Wno-experimental-header-units -Wno-pragma-system-header-outside-header -xc++-system-header --precompile
PCMFLAGS    = -Wno-experimental-header-units -fprebuilt-module-path=. --precompile -fmodule-file=
CMFLAGS     = -fprebuilt-module-path. -c
HEADERS     = iostream
MODULES     = GenericCounter.o
TARGET      = counters

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

