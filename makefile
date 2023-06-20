CC = g++
CFLAGS = -Wall -Wextra
LIBS = -L"C:/Users/repti/OneDrive/Desktop/C++/WordNet/WordNet-3.0/lib" -lwordnet
INCLUDE = -I"C:/Users/repti/OneDrive/Desktop/C++/WordNet/WordNet-3.0/include"

Dailywords: dailywords.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o Dailywords dailywords.cpp $(LIBS)