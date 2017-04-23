FILES = suli_files/main.cpp

LINUX: $(FILES) makefile
	g++ $(FILES) -std=c++11 -lGL -lglut -o LINUX/GSIM

WINDOWS: $(FILES) makefile
	g++ $(FILES) -std=c++11 -LWindowsCompile/ x-lglut  -IWindowsCompile/include/ -o WINDOWS/GSIM.exe