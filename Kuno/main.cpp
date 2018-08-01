#include "KunoApp.h"

int main() {
	
	//Create master singleton
	auto kuno = KunoApp::Instance();

	//// NOTICE!!! Change to fullscreen when doing release version ////
	//// Window size parameters MUST match with native monitor resolution otherwise there will be
	//// errors with functions converting between viewport to canvas to world coordinates
	//// Suggested resolutions: 1280, 720 | 1440, 900 | 1650, 1050

	// initialise and loop
	kuno->run("Kuno", 640, 480, false);		

	//Destroy master singleton
	KunoApp::resetInstance();

	return 0;
}