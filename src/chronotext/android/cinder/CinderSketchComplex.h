#pragma once

#include "cinder/app/AppAndroid.h"

class CinderDelegate;

class CinderSketchComplex
{
protected:
	CinderDelegate *context;

public:
    enum
    {
        FLAG_FOCUS_GAIN,
        FLAG_FOCUS_LOST,
        FLAG_APP_RESUME,
        FLAG_APP_PAUSE,
        FLAG_SCREEN_ENTER,
        FLAG_SCREEN_LEAVE
    };

	CinderSketchComplex(void *context) : context((CinderDelegate*)context) {}
	virtual ~CinderSketchComplex() {}

	virtual void setup(bool renewContext) {}
	virtual void shutdown() {}
	virtual void resize(ci::app::ResizeEvent event) {}
	virtual void update() {}
	virtual void draw() {}

	virtual void start(int flags) {}
	virtual void stop(int flags) {}

	virtual void addTouch(int index, float x, float y) {}
	virtual void updateTouch(int index, float x, float y) {}
	virtual void removeTouch(int index, float x, float y) {}
    
	virtual void accelerated(ci::app::AccelEvent event) {}
    
	void enableAccelerometer(float updateFrequency = 30, float filterFactor = 0.1f);
	void disableAccelerometer();
    
    double getElapsedSeconds() const;
    uint32_t getElapsedFrames() const;
	
	int getWindowWidth();
	int getWindowHeight();
    ci::Vec2f getWindowSize();
    float getWindowAspectRatio();
    ci::Area getWindowBounds() const;
    float getContentScale() const { return 1; }
    
    std::ostream& console();
};