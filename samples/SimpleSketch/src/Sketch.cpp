#include "Sketch.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void Sketch::setup()
{
	texture = TextureHelper::loadTexture("bulbo1.jpg"); // ON MSW, PLACE THE FILE IN A resources FOLDER ALONGSIDE THE EXECUTABLE

	// ---

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
}

void Sketch::shutdown()
{}

void Sketch::start(int flags)
{
#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
    enableAccelerometer(30);
#endif
}

void Sketch::stop(int flags)
{
#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
    disableAccelerometer();
#endif
}

void Sketch::resize(ResizeEvent event)
{
    gl::setMatricesWindow(event.getSize(), true);
}

void Sketch::update()
{}

void Sketch::draw()
{
    glClearColor(1, 0, 0, 1); 
    glClear(GL_COLOR_BUFFER_BIT); 
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// ---

	glColor4f(1, 1, 1, 1);
	gl::translate(getWindowSize() / 2);

	TextureHelper::beginTexture(texture);
	TextureHelper::drawTextureFromCenter(texture);
	TextureHelper::endTexture();
}

#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
void Sketch::accelerated(AccelEvent event)
{
    console() <<  event << endl;
}
#endif