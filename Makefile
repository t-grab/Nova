# includes
glew_inc = D:/dev/lib/glew/src/include
glfw_inc = D:/dev/lib/glfw/src/include
glm_inc = D:/dev/lib/glm/
boost_inc = /mingw64/include/

# libs
glfw_lib = D:/dev/lib/glfw/glfw-mingw/src
glew_lib = D:/dev/lib/glew/glew-mingw/lib/
boost_lib = /mingw64/lib

# compiler
CXX = g++
CXXFLAGS = -std=c++11
AR = ar

# objects
objects = bin/window.o bin/shader.o
testobjects = tests/test.o

# Rules
static: $(objects)
	$(AR) rcs lib/libnova.a $(objects)
	
dynamic: $(objects)
	$(CXX) -shared -o lib/libnova.so $(addprefix bin/, $(objects))

tests: static $(testobjects)
	$(CXX) -o tests $(testobjects) -Llib -L$(glew_lib) -L$(glfw_lib) -L$(boost_lib) -lnova -lboost_thread-mt -lboost_system-mt -lglew32 -lglfw3 -lgdi32 -lopengl32

# Patterns
bin/%.o :: src/%.cpp
	$(CXX) $(CXXFLAGS) -Wall -o $@ -c $< -I$(glew_inc) -I$(glfw_inc) -I$(glm_inc) -I$(boost_inc) -Iinclude

tests/%.o :: tests/%.cpp
	$(CXX) $(CXXFLAGS) -Wall -o $@ -c $< -I$(glew_inc) -I$(glfw_inc) -I$(glm_inc) -I$(boost_inc) -Iinclude
