# includes
glew_inc = D:/dev/lib/glew/src/include
glfw_inc = D:/dev/lib/glfw/src/include
glm_inc = D:/dev/lib/glm/

# libs
glfw_lib = D:/dev/lib/glfw/glfw-mingw/src
glew_lib = D:/dev/lib/glew/glew-mingw/lib/

# compiler
CXX = g++
CXXFLAGS = -std=c++11 -pthread
AR = ar

# objects
objects = bin/window.o
testobjects = tests/test.o

# Rules
static: $(objects)
	$(AR) rcs lib/libnova.a $(objects)
	
dynamic: $(objects)
	$(CXX) -shared -o lib/libnova.so $(addprefix bin/, $(objects))

tests: static $(testobjects)
	$(CXX) -o tests.exe $(testobjects) -Llib -lnova

# Patterns
bin/%.o :: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< -I$(glew_inc) -I$(glfw_inc) -I$(glm_inc) -Iinclude

tests/%.o :: tests/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< -I$(glew_inc) -I$(glfw_inc) -I$(glm_inc) -Iinclude
