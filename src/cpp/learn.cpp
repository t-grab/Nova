#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


void error_callback(int error, const char* description) {
	cerr << "Error " << error << ": " << description << endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
	GLFWwindow* window;
	
	glfwSetErrorCallback(error_callback);
		
	if (!glfwInit())
		return -1;
		
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	
	window = glfwCreateWindow(640, 480, "GLFW - Test", NULL, NULL);
	
	if (!window) {
		glfwTerminate();
		return -2;
	}
		
	glfwSetKeyCallback(window, key_callback);
	
	glfwMakeContextCurrent(window);
	
	glewExperimental = GL_TRUE;
	glewInit();
		
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
		
	const char* vertex_shader =
	"#version 400\n"
	"in vec3 vp;"
	"void main() {"
	"	gl_Position = vec4(vp, 1.0);"	
	"}";
	
	const char* fragment_shader = 
	"#version 400\n"
	"out vec4 frag_colour;"
	"void main() {"
	"	frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
	"}";
	
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, fs);
	glAttachShader(shader_program, vs);
	glLinkProgram(shader_program);

	glfwSwapInterval(1);
	
	float points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f	
	};
	
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
	
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
		
	glfwTerminate();	
	return 0; 
}