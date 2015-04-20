#include "stdio.h"

#include "application.h"
#include "renderer.h"

using namespace std;

namespace Omnerra
{
	Application::Application()
	{
		printf("Starting Application...\n");

		this->renderer = new Renderer();

		this->running = true;
	}

	void Application::run()
	{
		printf("Running Application...\n");

		while (this->running)
		{
			this->running &= this->renderer->run();
		}
	}
}
