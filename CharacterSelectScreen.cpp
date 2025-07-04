#include "CharacterSelectScreen.h"

int CharacterSelectScreen::mSelectedCharacter = 0;

CharacterSelectScreen::CharacterSelectScreen() {
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	
	//Background
	mBackground = new GLTexture("Background.png", 0, 0, 1000, 1000);
	mBackground->Parent(this);
	mBackground->Scale(Vector2(5, 5));
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	//Character icons
	mRaccoon = new GLTexture("Character Select.png", 0, 0, 25, 25);
	mRaccoon->Parent(this);
	mRaccoon->Scale(Vector2(15,15));
	mRaccoon->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.5f);

	mRaccoonSelected = new GLTexture("Character Select.png", 0, 27, 25, 25);
	mRaccoonSelected->Parent(this);
	mRaccoonSelected->Scale(Vector2(15, 15));
	mRaccoonSelected->Position(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.5f);

	mRabbit = new GLTexture("Character Select.png", 28, 0, 25, 25);
	mRabbit->Parent(this);
	mRabbit->Scale(Vector2(15, 15));
	mRabbit->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mRabbitSelected = new GLTexture("Character Select.png", 28, 27, 25, 25);
	mRabbitSelected->Parent(this);
	mRabbitSelected->Scale(Vector2(15, 15));
	mRabbitSelected->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mBear = new GLTexture("Character Select.png", 55, 0, 25, 25);
	mBear->Parent(this);
	mBear->Scale(Vector2(15, 15));
	mBear->Position(Graphics::SCREEN_WIDTH * 0.8f, Graphics::SCREEN_HEIGHT * 0.5f);

	mBearSelected = new GLTexture("Character Select.png", 55, 27, 25, 25);
	mBearSelected->Parent(this);
	mBearSelected->Scale(Vector2(15, 15));
	mBearSelected->Position(Graphics::SCREEN_WIDTH * 0.8f, Graphics::SCREEN_HEIGHT * 0.5f);

	mCursorStartPos = mRaccoon->Position(Local);
	mCursorOffset = Vector2(0.0f, 100.0f);
	mSelectedCharacter = 0;

}

CharacterSelectScreen::~CharacterSelectScreen() {
	delete mBackground;
	mBackground = nullptr;

	//Character icons
	delete mRaccoon;
	mRaccoon = nullptr;
	delete mRaccoonSelected;
	mRaccoonSelected = nullptr;

	delete mRabbit;
	mRabbit = nullptr;
	delete mRabbitSelected;
	mRabbitSelected = nullptr;

	delete mBear;
	mBear = nullptr;
	delete mBearSelected;
	mBearSelected = nullptr;
}

void CharacterSelectScreen::Update() {
	if (mInput->KeyPressed(SDL_SCANCODE_D)) {
		ChangeSelectedCharacter(1);
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_A)) {
		ChangeSelectedCharacter(-1);
	}

	if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
		mAudio->PlaySFX("Menu Select.mp3");
	}

}

void CharacterSelectScreen::Render() {
	mBackground->Render();

	mRaccoon->Render();
	if (SelectedCharacter() == 0) {
		mRaccoonSelected->Render();
	}

	mRabbit->Render();
	if (SelectedCharacter() == 1) {
		mRabbitSelected->Render();
	}

	mBear->Render();
	if (SelectedCharacter() == 2) {
		mBearSelected->Render();
	}
}

int CharacterSelectScreen::SelectedCharacter() {
	return mSelectedCharacter;
}

void CharacterSelectScreen::ChangeSelectedCharacter(int change) {
	mSelectedCharacter += change;

	if (mSelectedCharacter < 0) {
		mSelectedCharacter = 2;
	}
	else if (mSelectedCharacter > 2) {
		mSelectedCharacter = 0;
	}

	mAudio->PlaySFX("Menu Select.mp3");

}