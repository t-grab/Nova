#include "../hpp/nova.hpp"
using Nova::Windows;
using Nova::Window;

// Change Windows to kind of Guard

int main() {
	Windows& windows = Windows::get();
	Window& window = windows.create(640, 480);
	
	window.open();
	window.wait();
		
	return 0;
}