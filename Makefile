objects=windows.o window.o

glew_include=D:/Libraries/glew/include/
glew_lib=D:/Libraries/glew/lib/
glfw_include=D:/Libraries/glfw/include/
glfw_lib=D:/Libraries/glfw/src/
glm_include=D:/Libraries/glm/
	
learn: $(objects) learn.o
	g++ $(addprefix bin/,$?) -o learn.exe -L$(glfw_lib) -L$(glew_lib) -lglew32 -lglu32 -lglfw3 -lopengl32 -lgdi32

dynamic: $(objects)
	g++ -shared $(addprefix bin/,$?) -o libnova.so -L$(glfw_lib) -L$(glew_lib) -lglew32 -lglu32 -lglfw3 -lopengl32 -lgdi32
	
static: $(objects)
	copy $(subst /,\\,$(glfw_lib))libglfw3.a libnova.a
	ar rcs libnova.a $(addprefix bin/,$?)

test_dynamic: test.o dynamic
	g++ bin/test.o -o test.exe libnova.so -L$(glfw_lib) -L$(glew_lib) -lglew32 -glu32 -lglfw3 -lopengl32 -lgdi32

test_static: test.o static
	g++ bin/test.o -o test.exe -L$(glew_lib) -L. -lnova -lglew32 -glu32 -lopengl32 -lgdi32

%.o : src/cpp/%.cpp
	g++ -c -std=c++11 -pthread -o bin/$@ $< -I$(glew_include) -I$(glfw_include) -I$(glm_include)