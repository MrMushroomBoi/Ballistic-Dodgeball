 #include "ScreenManager.h"

ScreenManager * ScreenManager::sInstance = nullptr;

ScreenManager * ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void ScreenManager::Update() {

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();

		if (mStartScreen->mAnimationDone == true) {
			mCurrentScreen = Select;
		}
		
		break;

	case Play:
		mPlayScreen->Update();
		//Sends player back to title screen once the game ends
		if (mPlayScreen->mGameOverTimer >= 3.0f && mPlayScreen->mGameOverTimer <= 3.9f) {
			mCurrentScreen = Start;
			mStartScreen->mAnimationDone = false;
			mStartScreen->mSelectedMode = 0;
			mPlayScreen->mGameOver = false;
		}

		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = Start;
			mStartScreen->mAnimationDone = false;
			mStartScreen->mSelectedMode = 0;
		}
		break;

	case Multiplayer:
		mMultiplayerScreen->Update();
		//Sends player back to title screen once the game ends
		if (mMultiplayerScreen->mGameOverTimer >= 3.0f && mMultiplayerScreen->mGameOverTimer <= 3.9f) {
			mCurrentScreen = Start;
			mStartScreen->mAnimationDone = false;
			mStartScreen->mSelectedMode = 0;
			mPlayScreen->mGameOver = false;
		}
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = Start;
			mStartScreen->mAnimationDone = false;
			mStartScreen->mSelectedMode = 0;
		}
		break;

	case Tutorial:
		mTutorialScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = Start;
			mStartScreen->mAnimationDone = false;
			mStartScreen->mSelectedMode = 0;
		}
		break;

	case Select:
		mCharacterSelectScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = Start;
			mStartScreen->mAnimationDone = false;
			mStartScreen->mSelectedMode = 0;
		}

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode() == 0) {
			mCurrentScreen = Play;
			mPlayScreen->StartNewGame();
		}
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode() == 1){
			mCurrentScreen = P2Select;
		}
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode() == 2){
			mCurrentScreen = Tutorial;
		}
		break;

	case P2Select:
		mPlayer2CharacterSelectScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = Start;
			mStartScreen->mAnimationDone = false;
			mStartScreen->mSelectedMode = 0;
		}

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			mCurrentScreen = Multiplayer;
			mMultiplayerScreen->StartNewGame();
		}
		break;
	}
	
}

void ScreenManager::Render() { 
	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Render();
		break;

	case Play:
		mPlayScreen->Render();
		break;

	case Multiplayer:
		mMultiplayerScreen->Render();
		break;

	case Tutorial:
		mTutorialScreen->Render();
		break;

	case Select:
		mCharacterSelectScreen->Render();
		break;

	case P2Select:
		mPlayer2CharacterSelectScreen->Render();
		break;
	}
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mMultiplayerScreen = new MultiplayerScreen();
	mTutorialScreen = new TutorialScreen();
	mCharacterSelectScreen = new CharacterSelectScreen();
	mPlayer2CharacterSelectScreen = new Player2CharacterSelectScreen();

	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mMultiplayerScreen;
	mMultiplayerScreen = nullptr;

	delete mTutorialScreen;
	mTutorialScreen = nullptr;

	delete mCharacterSelectScreen;
	mCharacterSelectScreen = nullptr;

	delete mPlayer2CharacterSelectScreen;
	mPlayer2CharacterSelectScreen = nullptr;
}