#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "Scoreboard.h"
#include "AudioManager.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

private:
	Timer * mTimer;
	InputManager * mInput;
	AudioManager* mAudio;

	//Background
	Texture* mBackground;
	Texture* mPurpleBall;
	//Logo
	Texture* mLogo;
	//Game mode entities
	Texture * mSinglePlayer;
	Texture * mMultiplayer;
	Texture* mTutorial;
	Texture * mDodgeball;

	// Play Mode Entities
	GameEntity * mPlayModes;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;

	// Screen Animation Variables
	bool mDodgeballAnimation;
	bool mBackgroundAnimation;

public:
	StartScreen();
	~StartScreen();

	int SelectedMode();

	void ChangeSelectedMode(int change);

	void Update() override;
	void Render() override;

	int mSelectedMode;

	bool mAnimationDone;

};
#endif