#include "stdio.h"

#include "application.h"

using namespace std;

using namespace Omnerra;

int main(int argc, char* argv[])
{
	Application* app = new Application();

	app->run();

	return 0;
}
