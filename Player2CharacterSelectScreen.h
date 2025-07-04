#ifndef __PLAYER2CHARACTERSELECTSCREEN_H
#define __PLAYER2CHARACTERSELECTSCREEN_H
#include "AnimatedGLTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

using namespace SDLFramework;

class Player2CharacterSelectScreen :public GameEntity {
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
	Player2CharacterSelectScreen();
	~Player2CharacterSelectScreen();

	void Update() override;
	void Render() override;

	static int SelectedCharacter();

	void ChangeSelectedCharacter(int change);

	static int mSelectedCharacter;
};


#endif 