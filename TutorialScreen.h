#ifndef __TUTORIALSCREEN_H
#define __TUTORIALSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

using namespace SDLFramework;

class TutorialScreen:public GameEntity {
private:
	InputManager* mInput;
	AudioManager* mAudio;

public:
	TutorialScreen();
	~TutorialScreen();

	void Update() override;
	void Render() override;
};


#endif


