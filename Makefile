CXX = gcc

CXXFLAGS = -O3 -ffast-math

LDFLAGS=

INCLUDE = -I include

main: src/main.c
	$(CXX) $(CXXFLAGS) $< -o $@ $(INCLUDE) $(LDFLAGS)

clean:
	rm main
