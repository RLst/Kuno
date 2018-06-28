#include "KunoApp.h"

int main() {
	
	// allocation
	auto app = new KunoApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}



//Behaviour tree

if (GuardBehaviour)
{
	//Idle
	if (Idle)
	{
		wait 30 - 60 seconds;
		move to patrol
	}
	//Patrol
	if (Patrol)


	//

}