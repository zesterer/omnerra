#ifndef APPLICATION_H
#define APPLICATION_H

#include "renderer.h"

namespace Omnerra
{
	class Application
	{
		public: Renderer* renderer;
		public: bool running;

		public: Application();
		public: void run();
	};
}

#endif
