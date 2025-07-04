#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"
#include "PlayScreen.h"
#include "MultiplayerScreen.h"
#include "TutorialScreen.h"
#include "CharacterSelectScreen.h"
#include "Player2CharacterSelectScreen.h"
#include "AudioManager.h"

class ScreenManager {
private:
	static ScreenManager * sInstance;

	enum Screens { Start, Play, Multiplayer, Tutorial, Select, P2Select };
	Screens mCurrentScreen;

	InputManager * mInput;

	StartScreen * mStartScreen;
	PlayScreen * mPlayScreen;
	MultiplayerScreen* mMultiplayerScreen;
	TutorialScreen* mTutorialScreen;
	CharacterSelectScreen* mCharacterSelectScreen;
	Player2CharacterSelectScreen* mPlayer2CharacterSelectScreen;

public:
	static ScreenManager * Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();
};
#endif