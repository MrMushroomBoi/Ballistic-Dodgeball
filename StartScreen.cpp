#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	//Background
	mBackground = new GLTexture("Background.png", 0, 0, 1000, 1000);
	mBackground->Parent(this);
	mBackground->Scale(Vector2(5,5));
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.0f);

	mPurpleBall = new GLTexture("Ball Layer.png", 0, 0, 1920000, 1080000);
	mPurpleBall->Parent(this);
	//mPurpleBall->Scale(Vector2(0.7, 0.7));
	mPurpleBall->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mBackgroundAnimation = true;

	//Logo
	mLogo = new GLTexture("Ballistic Dodgeball.png", 0, 0, 413, 133);
	mLogo->Parent(this);
	mLogo->Scale(Vector2(2, 2));
	mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.3f);

	//Game mode entitites
	mDodgeball = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mDodgeball->Parent(this);
	mDodgeball->Scale(Vector2(4, 4));
	mDodgeball->Position(Graphics::SCREEN_WIDTH * 0.27f, Graphics::SCREEN_HEIGHT * 0.6f);

	mCursorStartPos = mDodgeball->Position(Local);
	mCursorOffset = Vector2(0.0f, 100.0f);
	mSelectedMode = 0;

	mDodgeballAnimation = false;
	mAnimationDone = false;

	mSinglePlayer = new GLTexture("Single Player Text.png", 0, 0, 208, 18);
	mSinglePlayer->Parent(this);
	mSinglePlayer->Scale(Vector2(3, 3));
	mSinglePlayer->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.6f);

	mMultiplayer = new GLTexture("Multiplayer Text.png", 0, 0, 874, 86);
	mMultiplayer->Parent(this);
	mMultiplayer->Scale(Vector2(0.7, 0.7));
	mMultiplayer->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);

	mTutorial = new GLTexture("Tutorial Text.png", 0, 0, 762, 106);
	mTutorial->Parent(this);
	mTutorial->Scale(Vector2(0.6, 0.6));
	mTutorial->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.8f);

	mAudio->PlayMusic("MenuMusic.mp3", -1);
}


StartScreen::~StartScreen() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	//Background
	delete mBackground;
	mBackground = nullptr;
	delete mPurpleBall;
	mPurpleBall = nullptr;
	//Logo
	delete mLogo;
	mLogo = nullptr;
	//Game mode entities
	delete mDodgeball;
	mDodgeball = nullptr;
	delete mSinglePlayer;
	mSinglePlayer = nullptr;
	delete mMultiplayer;
	mMultiplayer = nullptr;
	delete mTutorial;
	mTutorial = nullptr;

}

int StartScreen::SelectedMode() {
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;

	if (mSelectedMode < 0) {
		mSelectedMode = 2;
	}
	else if (mSelectedMode > 2) {
		mSelectedMode = 0;
	}

	mDodgeball->Position(mCursorStartPos + mCursorOffset * (float)mSelectedMode);
	mAudio->PlaySFX("Menu Select.mp3");
}


void StartScreen::Update() {
	if (mInput->KeyPressed(SDL_SCANCODE_S)) {
		ChangeSelectedMode(1);
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_W)) {
		ChangeSelectedMode(-1);
	}

	//Dodgeball animation
	if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
		mDodgeballAnimation = true;
		mAudio->PlaySFX("Game Start.mp3");
	
	}
	if (mDodgeballAnimation == true) {
		mDodgeball->Translate(Vec2_Right * 20);
		if (mDodgeball->Position(Local).x > 1500) {
			mAnimationDone = true;
		}
		else {
			mAnimationDone = false;
		}
		if (mDodgeball->Position(Local).x > 1500) {
			mDodgeball->Position(mCursorStartPos);
			mDodgeballAnimation = false;
		}
	}

	//Background animation
	if (mBackgroundAnimation == true) {
		mPurpleBall->Translate(-Vec2_Up * 2);
		mPurpleBall->Translate(-Vec2_Right * 2);
	}
}

void StartScreen::Render() {
	mBackground->Render();
	mPurpleBall->Render();
	mLogo->Render();
	mSinglePlayer->Render();
	mMultiplayer->Render();
	mTutorial->Render();
	mDodgeball->Render();
}