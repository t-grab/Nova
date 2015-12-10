#include "../hpp/nova.hpp"
using namespace Nova;

/*
 *	PUBLIC MEMBERS
 */

Windows::~Windows() {	
	for (uint i = 0U; i < windows.size(); ++i)
		windows.at(i)->close();
	for (uint i = 0U; i < windows.size(); ++i)
		windows.at(i)->wait();
	
	for (uint i = 0U; i < windows.size(); ++i)
		delete windows.at(i);
		
	glfwTerminate();
}

Windows& Windows::get() {
	static Windows instance;
	return instance;
}
 
Window& Windows::create(int width, int height) {
	Window* window = new Window(width, height);
	windows.push_back(window);
	
	return *window;
}

void Windows::wait() {
	for (uint i = 0U; i < windows.size(); ++i)
		windows.at(i)->thread.join();
}

GLuint Windows::create_default_shader() {
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &DEFAULT_VERTEX_SHADER_SRC, NULL);
	glCompileShader(vertex);
	
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &DEFAULT_FRAGMENT_SHADER_SRC, NULL);
	glCompileShader(fragment);
	
	GLuint shader = glCreateProgram();
	glAttachShader(shader, fragment);
	glAttachShader(shader, vertex);
	glLinkProgram(shader);
	
	return shader;
}

/*
 *	PRIVATE MEMBERS
 */
 
Windows::Windows() : windows() {
	glfwSetErrorCallback(error);
	
	if (!glfwInit())
		throw std::runtime_error("Nova::Windows::Windows(): Could not initialize GLFW!");
	glewExperimental = GL_TRUE;
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	
	DEFAULT_VERTEX_SHADER_SRC = 
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		"	gl_Position = vec4(vp, 1.0);"	
		"}";
	DEFAULT_FRAGMENT_SHADER_SRC = 
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"	frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";
}

/*
 * 	HELPER FUNCTIONS
 */
 
void Nova::error(int error, const char* description) {
	std::cerr << "GLFW error " << error << ": " << description << std::endl;
} 
 
void Nova::key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
