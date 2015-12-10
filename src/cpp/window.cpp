#include "../hpp/nova.hpp"
using namespace Nova;

/*
 * 	PUBLIC MEMBERS
 */

Window::Window(int w, int h) : handle(0), shader(), thread(), initializing(), running(), width(w), height(h) {}

Window::~Window() {
	close();
	wait();	
}

void Window::open() {	
	// NICHT THREADSAFE!
	if (thread.joinable())
		return;
	
	std::condition_variable initialized;
	
	thread = std::thread([&] (Window& window) {
		// Protect valid initialization
		{
			lock_guard lock(window.initializing);			
			window.init();
		}
		
		lock_guard lock(window.running);			
		initialized.notify_one();
		
		// Execute main loop
		window.main();
		
		// Clean up
		glfwDestroyWindow(handle);		
		handle = 0;	
	}, std::ref(*this));
	
	std::unique_lock<std::mutex> lock(initializing);
	initialized.wait(lock);
}

void Window::close() {
	lock_guard lock(initializing);
	
	if (handle != 0 && !glfwWindowShouldClose(handle))
		glfwSetWindowShouldClose(handle, GL_TRUE);
}

void Window::wait() {
	lock_guard lock(running);
	
	if (thread.joinable() && std::this_thread::get_id() != thread.get_id())
		thread.join();
}

/*
 *	PRIVATE MEMBERS
 */

void Window::init() {
	handle = glfwCreateWindow(width, height, "", NULL, NULL);
	if (!handle)
		throw std::runtime_error("Window::Window(): Could not create window!");	
		
	glfwMakeContextCurrent(handle);	
	glewInit();
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);	
		
	shader = Windows::get().create_default_shader();	
	
	glfwSwapInterval(1);
	glfwSetKeyCallback(handle, key);
}

void Window::main() {	
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
	
	while (!glfwWindowShouldClose(handle)) {		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(handle);
		glfwPollEvents();
	}
}
