#include "chronotext/ScreenManager.h"

using namespace ci;
using namespace app;
using namespace std;

void ScreenManager::shutdown()
{
    for (list<CinderSketch*>::const_iterator it = screens.begin(); it != screens.end(); ++it)
    {
        CinderSketch *screen = *it;

        screen->shutdown();
        delete screen;
    }
}

void ScreenManager::resize(ResizeEvent event)
{
    size = event.getSize();
    
    if (currentScreen)
    {
        if (size != Vec2i(0, 0))
        {
            currentScreen->resize(ResizeEvent(size));
        }
    }
}

void ScreenManager::update()
{
    if (currentScreen)
    {
        currentScreen->update();
    }
}

void ScreenManager::draw()
{
    if (currentScreen)
    {
        currentScreen->draw();
    }
}

void ScreenManager::start(int flags)
{
    if (currentScreen)
    {
        switch(flags)
        {
            case CinderSketch::FLAG_FOCUS_GAIN:
                if (!focused[currentScreen])
                {
                    focused[currentScreen] = true;
                    currentScreen->start(CinderSketch::FLAG_FOCUS_GAIN);
                }
                break;
                
            case CinderSketch::FLAG_APP_RESUME:
                currentScreen->start(CinderSketch::FLAG_APP_RESUME);
                break;
        }
    }
}

void ScreenManager::stop(int flags)
{
    if (currentScreen)
    {
        switch(flags)
        {
            case CinderSketch::FLAG_FOCUS_LOST:
                focused[currentScreen] = false;
                currentScreen->stop(CinderSketch::FLAG_FOCUS_LOST);
                break;
                
            case CinderSketch::FLAG_APP_PAUSE:
                currentScreen->stop(CinderSketch::FLAG_APP_PAUSE);
                break;
        }
    }
}

void ScreenManager::addTouch(int index, float x, float y)
{
    if (currentScreen) currentScreen->addTouch(index, x, y);
}

void ScreenManager::updateTouch(int index, float x, float y)
{
    if (currentScreen) currentScreen->updateTouch(index, x, y);
}

void ScreenManager::removeTouch(int index, float x, float y)
{
    if (currentScreen) currentScreen->removeTouch(index, x, y);
}

#if defined( CINDER_COCOA_TOUCH )
void ScreenManager::accelerated(AccelEvent event)
{
    if (currentScreen) currentScreen->accelerated(event);
}
#endif

/*
 * WARNING: A VALID GL CONTEXT IS REQUIRED
 * I.E. THIS SHOULD BE CALLED FROM E.G. Sketch.setup()
 */ 
void ScreenManager::addScreen(CinderSketch *screen)
{
    screen->setup();
    
    screens.push_back(screen);
    focused[screen] = false;
}

void ScreenManager::removeScreen(CinderSketch *screen)
{
    screens.remove(screen);
    focused.erase(screen);

    screen->shutdown();
    delete screen;
}

void ScreenManager::setCurrentScreen(CinderSketch *screen)
{
    if (currentScreen)
    {
        currentScreen->stop(CinderSketch::FLAG_SCREEN_LEAVE);
    }

    /*
     * REQUIRED IN ORDER TO AVOID SITUATIONS WHERE A "SCREEN_ENTER"
     * IS FOLLOWED BY SOME UN-NECESSARY "FOCUS_GAIN"
     */
    focused[screen] = true;

    screen->start(CinderSketch::FLAG_SCREEN_ENTER);
    
    if (size != Vec2i(0, 0))
    {
        screen->resize(ResizeEvent(size));
    }
    
    currentScreen = screen;
}