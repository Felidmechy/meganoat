#include "ofMain.h"
#include "meganoat.h"

meganoat* g_pmeganoat;

//========================================================================
int main( ){

	ofSetupOpenGL(512,512,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetWindowTitle("meganoat");
	g_pmeganoat = new meganoat();
	ofRunApp(g_pmeganoat);

}
