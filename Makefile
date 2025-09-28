CXX = g++
CXXFLAGS = -Wall -std=c++17

abj_vcs: main.o custom_classes_implementation.o
	$(CXX) $(CXXFLAGS) main.o custom_classes_implementation.o -o abj_vcs

main.o: main.cpp custom_classes.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# 4. Rule to build MyClass.o from MyClass.cpp
custom_classes_implementation.o: custom_classes_implementation.cpp custom_classes.hpp
	$(CXX) $(CXXFLAGS) -c custom_classes_implementation.cpp

clean:
	rm -f *.o abj_vcs
