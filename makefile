CC = g++
CFLAGS = -Wall -Wextra
LIBS = -L"C:/Users/repti/OneDrive/Desktop/C++/WordNet/WordNet-3.0/lib" -lwordnet
INCLUDE = -I"C:/Users/repti/OneDrive/Desktop/C++/WordNet/WordNet-3.0/include"

YourProgram: dailywords.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o YourProgram dailywords.cpp $(LIBS)