#ifndef __CHARACTERSELECTSCREEN_H
#define __CHARACTERSELECTSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

using namespace SDLFramework;

class CharacterSelectScreen :public GameEntity {
private:
	InputManager* mInput;
	AudioManager* mAudio;

	Texture* mBackground;
	
	//Character icons
	Texture* mRaccoon;
	Texture* mRaccoonSelected;

	Texture* mRabbit;
	Texture* mRabbitSelected;

	Texture* mBear;
	Texture* mBearSelected;

	//Character select entities
	GameEntity* mChoice;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;

public:
	CharacterSelectScreen();
	~CharacterSelectScreen();

	void Update() override;
	void Render() override;

	static int SelectedCharacter();

	void ChangeSelectedCharacter(int change);

	static int mSelectedCharacter;
};



#endif