#include "PlayScreen.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"


PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	//Map
	mBackground = new GLTexture("Dodgeball Map.png", 0, 0, 1920, 1080);
	mBackground->Parent(this);
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	
	//Character Icons;
	mRaccoonIcon = new GLTexture("Character Select.png", 0, 0, 25, 25);
	mRaccoonIcon->Parent(this);
	mRaccoonIcon->Scale(Vector2(5, 5));
	mRaccoonIcon->Position(Graphics::SCREEN_WIDTH * 0.1f, Graphics::SCREEN_HEIGHT * 0.1f);

	mRabbitIcon = new GLTexture("Character Select.png", 28, 0, 25, 25);
	mRabbitIcon->Parent(this);
	mRabbitIcon->Scale(Vector2(5, 5));
	mRabbitIcon->Position(Graphics::SCREEN_WIDTH * 0.1f, Graphics::SCREEN_HEIGHT * 0.1f);

	mBearIcon = new GLTexture("Character Select.png", 55, 0, 25, 25);
	mBearIcon->Parent(this);
	mBearIcon->Scale(Vector2(5, 5));
	mBearIcon->Position(Graphics::SCREEN_WIDTH * 0.1f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyIcon = new GLTexture("Character Select.png", 0, 0, 25, 25);
	mEnemyIcon->Parent(this);
	mEnemyIcon->Scale(Vector2(5, 5));
	mEnemyIcon->Position(Graphics::SCREEN_WIDTH * 0.9f, Graphics::SCREEN_HEIGHT * 0.1f);

	//Point outlines
	mPointOutline1 = new GLTexture("Point Outline.png", 0, 0, 130, 25);
	mPointOutline1->Parent(this);
	mPointOutline1->Scale(Vector2(4, 4));
	mPointOutline1->Position(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPointOutline2 = new GLTexture("Point Outline.png", 0, 0, 130, 25);
	mPointOutline2->Parent(this);
	mPointOutline2->Scale(Vector2(4, 4));
	mPointOutline2->Position(Graphics::SCREEN_WIDTH * 0.7f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint1 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint1->Parent(this);
	mPlayerPoint1->Scale(Vector2(4, 4));
	mPlayerPoint1->Position(Graphics::SCREEN_WIDTH * 0.1907f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint2 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint2->Parent(this);
	mPlayerPoint2->Scale(Vector2(4, 4));
	mPlayerPoint2->Position(Graphics::SCREEN_WIDTH * 0.245f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint3 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint3->Parent(this);
	mPlayerPoint3->Scale(Vector2(4, 4));
	mPlayerPoint3->Position(Graphics::SCREEN_WIDTH * 0.299f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint4 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint4->Parent(this);
	mPlayerPoint4->Scale(Vector2(4, 4));
	mPlayerPoint4->Position(Graphics::SCREEN_WIDTH * 0.353f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint5 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint5->Parent(this);
	mPlayerPoint5->Scale(Vector2(4, 4));
	mPlayerPoint5->Position(Graphics::SCREEN_WIDTH * 0.4071f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint1 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint1->Parent(this);
	mEnemyPoint1->Scale(Vector2(4, 4));
	mEnemyPoint1->Position(Graphics::SCREEN_WIDTH * 0.8071f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint2 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint2->Parent(this);
	mEnemyPoint2->Scale(Vector2(4, 4));
	mEnemyPoint2->Position(Graphics::SCREEN_WIDTH * 0.753f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint3 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint3->Parent(this);
	mEnemyPoint3->Scale(Vector2(4, 4));
	mEnemyPoint3->Position(Graphics::SCREEN_WIDTH * 0.699f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint4 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint4->Parent(this);
	mEnemyPoint4->Scale(Vector2(4, 4));
	mEnemyPoint4->Position(Graphics::SCREEN_WIDTH * 0.645f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint5 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint5->Parent(this);
	mEnemyPoint5->Scale(Vector2(4, 4));
	mEnemyPoint5->Position(Graphics::SCREEN_WIDTH * 0.5904f, Graphics::SCREEN_HEIGHT * 0.1f);

	//Walls
	mLeftWall = new Wall;
	mLeftWall->Parent(this);
	mLeftWall->Position(Graphics::SCREEN_WIDTH * 0.0f, Graphics::SCREEN_HEIGHT * 0.5f);

	mRightWall = new Wall;
	mRightWall->Parent(this);
	mRightWall->Position(Graphics::SCREEN_WIDTH * 1.0f, Graphics::SCREEN_HEIGHT * 0.5f);

	//Text
	mWinText = new GLTexture("YouWinText.png", 0, 0, 677, 119);
	mWinText->Parent(this);
	mWinText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mLoseText = new GLTexture("YouLoseText.png", 0, 0, 813, 119);
	mLoseText->Parent(this);
	mLoseText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mPlayerPoints = 0;
	mEnemyPoints = 0;

	mHasWon = false;
	mHasLost = false;
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mBackground;
	mBackground = nullptr;
	delete mRaccoonIcon;
	mRaccoonIcon = nullptr;
	delete mRabbitIcon;
	mRabbitIcon = nullptr;
	delete mBearIcon;
	mBearIcon = nullptr;
	delete mEnemyIcon;
	mEnemyIcon = nullptr;
	delete mPointOutline1;
	mPointOutline1 = nullptr;
	delete mPointOutline2;
	mPointOutline2 = nullptr;
	delete mPlayerPoint1;
	mPlayerPoint1 = nullptr;
	delete mPlayerPoint2;
	mPlayerPoint2 = nullptr;
	delete mPlayerPoint3;
	mPlayerPoint3 = nullptr;
	delete mPlayerPoint4;
	mPlayerPoint4 = nullptr;
	delete mPlayerPoint5;
	mPlayerPoint5 = nullptr;
	delete mEnemyPoint1;
	mEnemyPoint1 = nullptr;
	delete mEnemyPoint2;
	mEnemyPoint2 = nullptr;
	delete mEnemyPoint3;
	mEnemyPoint3 = nullptr;
	delete mEnemyPoint4;
	mEnemyPoint4 = nullptr;
	delete mEnemyPoint5;
	mEnemyPoint5 = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
	
	delete mEnemy;
	mEnemy = nullptr;

	for (auto ball : mBalls) {
		delete ball;
	}
	mBalls.clear();

	delete mLeftWall;
	mLeftWall = nullptr;
	delete mRightWall;
	mRightWall = nullptr;

	delete mWinText;
	mWinText = nullptr;
	delete mLoseText;
	mLoseText = nullptr;
	
}

void PlayScreen::StartNewGame() {
	RoundReset();

	mPlayer = new Player;
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.7f);

	mEnemy = new Enemy;
	mEnemy->Parent(this);
	mEnemy->Position(Graphics::SCREEN_WIDTH * 0.7f, Graphics::SCREEN_HEIGHT * 0.7f);

	int numBalls = 5;
	float startY = Graphics::SCREEN_HEIGHT * 0.63f;
	float spacing = (Graphics::SCREEN_HEIGHT * 0.3f) / (numBalls - 1);
	for (int i = 0; i < numBalls; ++i) {
		BallPickup* ball = new BallPickup;
		ball->Parent(this);
		// Position the balls vertically centered in the middle of the screen
		ball->Position(Graphics::SCREEN_WIDTH * 0.504f, startY + i * spacing);
		ball->SetPickupCallback([this, ball]() {
			DeleteBall(ball);
			});
		mBalls.push_back(ball);
	}

	// Set the callback for the Bullet class
	for (int i = 0; i < Enemy::MAX_BULLETS; ++i) {
		mPlayer->mBullets[i]->SetBallCreatedCallback([this](BallPickup* newBall) {
			HandleNewBallPickup(newBall);
			});
	}
	mGameOverTimer = 4.0f;

	mPlayerPoints = 0;
	mEnemyPoints = 0;

	mHasWon = false;
	mHasLost = false;
}


void PlayScreen::EnemyMovment() {
	if (mEnemy->mHasBall) {
		mEnemy->SetTarget(mPlayer);
	}
	else {
		UpdateEnemyTarget();
	}
}

void PlayScreen::HandleNewBallPickup(BallPickup* newBall) {
    newBall->Parent(this);
    newBall->SetPickupCallback([this, newBall]() {
        DeleteBall(newBall);
    });
    mBalls.push_back(newBall);
    UpdateEnemyTarget();
}

void PlayScreen::DeleteBall(BallPickup* ball) {
	auto it = std::find(mBalls.begin(), mBalls.end(), ball);
	if (it != mBalls.end()) {
		if (mEnemy->GetTarget() == ball) {
			mEnemy->SetTarget(nullptr);
		}
		delete* it;
		mBalls.erase(it);
	}
	UpdateEnemyTarget();
}




void PlayScreen::UpdateEnemyTarget() {
	if (mBalls.empty()) {
		mEnemy->SetTarget(nullptr);
		return;
	}

	BallPickup* nearestBall = nullptr;
	float nearestDistance = std::numeric_limits<float>::max();

	for (auto ball : mBalls) {
		// Check if the ball is active before considering it as a target
		if (ball->Active()) {
			float distance = (ball->Position() - mEnemy->Position()).MagnitudeSqr();
			if (distance < nearestDistance) {
				nearestDistance = distance;
				nearestBall = ball;
			}
		}
	}

	mEnemy->SetTarget(nearestBall);
}

void PlayScreen::StartNewRound() {
	//Clean up from last game
	RoundReset();

	mPlayer = new Player;
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.7f);

	mEnemy = new Enemy;
	mEnemy->Parent(this);
	mEnemy->Position(Graphics::SCREEN_WIDTH * 0.7f, Graphics::SCREEN_HEIGHT * 0.7f);

	int numBalls = 5;
	float startY = Graphics::SCREEN_HEIGHT * 0.63f;
	float spacing = (Graphics::SCREEN_HEIGHT * 0.3f) / (numBalls - 1);
	for (int i = 0; i < numBalls; ++i) {
		BallPickup* ball = new BallPickup;
		ball->Parent(this);
		// Position the balls vertically centered in the middle of the screen
		ball->Position(Graphics::SCREEN_WIDTH * 0.504f, startY + i * spacing);
		ball->SetPickupCallback([this, ball]() {
			DeleteBall(ball);
			});
		mBalls.push_back(ball);
	}

	// Set the callback for the Bullet class
	for (int i = 0; i < Player::MAX_BULLETS; ++i) {
		if (mPlayer->mBullets[i]) {
			mPlayer->mBullets[i]->SetBallCreatedCallback([this](BallPickup* newBall) {
				HandleNewBallPickup(newBall);
				});
		}
	}

	//Point icons
	mPlayerPoint1 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint1->Parent(this);
	mPlayerPoint1->Scale(Vector2(4, 4));
	mPlayerPoint1->Position(Graphics::SCREEN_WIDTH * 0.1907f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint2 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint2->Parent(this);
	mPlayerPoint2->Scale(Vector2(4, 4));
	mPlayerPoint2->Position(Graphics::SCREEN_WIDTH * 0.245f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint3 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint3->Parent(this);
	mPlayerPoint3->Scale(Vector2(4, 4));
	mPlayerPoint3->Position(Graphics::SCREEN_WIDTH * 0.299f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint4 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint4->Parent(this);
	mPlayerPoint4->Scale(Vector2(4, 4));
	mPlayerPoint4->Position(Graphics::SCREEN_WIDTH * 0.353f, Graphics::SCREEN_HEIGHT * 0.1f);

	mPlayerPoint5 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mPlayerPoint5->Parent(this);
	mPlayerPoint5->Scale(Vector2(4, 4));
	mPlayerPoint5->Position(Graphics::SCREEN_WIDTH * 0.4071f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint1 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint1->Parent(this);
	mEnemyPoint1->Scale(Vector2(4, 4));
	mEnemyPoint1->Position(Graphics::SCREEN_WIDTH * 0.8071f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint2 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint2->Parent(this);
	mEnemyPoint2->Scale(Vector2(4, 4));
	mEnemyPoint2->Position(Graphics::SCREEN_WIDTH * 0.753f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint3 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint3->Parent(this);
	mEnemyPoint3->Scale(Vector2(4, 4));
	mEnemyPoint3->Position(Graphics::SCREEN_WIDTH * 0.699f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint4 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint4->Parent(this);
	mEnemyPoint4->Scale(Vector2(4, 4));
	mEnemyPoint4->Position(Graphics::SCREEN_WIDTH * 0.645f, Graphics::SCREEN_HEIGHT * 0.1f);

	mEnemyPoint5 = new GLTexture("Dodgeball Sprite.png", 0, 0, 25, 25);
	mEnemyPoint5->Parent(this);
	mEnemyPoint5->Scale(Vector2(4, 4));
	mEnemyPoint5->Position(Graphics::SCREEN_WIDTH * 0.5904f, Graphics::SCREEN_HEIGHT * 0.1f);

	mWinText = new GLTexture("YouWinText.png", 0, 0, 677, 119);
	mWinText->Parent(this);
	mWinText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mLoseText = new GLTexture("YouLoseText.png", 0, 0, 813, 119);
	mLoseText->Parent(this);
	mLoseText->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverTimer = 4.0f;
}

void PlayScreen::RoundReset() {
	for (auto ball : mBalls) {
		delete ball;
	}
	mBalls.clear();
	delete mPlayer;
	mPlayer = nullptr;
	
	delete mEnemy;
	mEnemy = nullptr;
}

void PlayScreen::Win() {

	mPlayer->mCanMove = false;
	mEnemy->mCanMove = false;
	mAudio->PlaySFX("WinSound.mp3");

	mGameOverTimer = 0.0f;

}

void PlayScreen::Lose() {
	
	mPlayer->mCanMove = false;
	mEnemy->mCanMove = false;
	mAudio->PlaySFX("LoseSound.mp3");

	mGameOverTimer = 0.0f;
}

void PlayScreen::Update() {
	//Checks for what character was selected
	int selectedCharacter = CharacterSelectScreen::SelectedCharacter();

	if (selectedCharacter == 0) {
		mIcon = Raccoon;
	}
	if (selectedCharacter == 1) {
		mIcon = Rabbit;
	}
	if (selectedCharacter == 2) {
		mIcon = Bear;
	}

	mPlayer->Update();
	mEnemy->Update();

	for (auto ball : mBalls) {
		ball->Update();
	}

	mLeftWall->Update();
	mRightWall->Update();

	EnemyMovment();

	if (mPlayer->mWasHit) {
		RoundReset();
		StartNewRound();
		mEnemyPoints++;
		mPlayer->mWasHit = false;
	}

	if (mEnemy->mWasHit) {
		RoundReset();
		StartNewRound();
		mPlayerPoints++;
		mEnemy->mWasHit = false;
	}

	if (mPlayerPoints == 5) {
		Win();
		mHasWon = true;
		mPlayerPoints = 6;
	}

	if (mEnemyPoints == 5) {
		Lose();
		mHasLost = true;
		mEnemyPoints = 6;
	}

	mGameOverTimer += mTimer->DeltaTime();
	
}

void PlayScreen::Render() {
	//Player Points
	mBackground->Render();

	//Point outlines
	mPointOutline1->Render();
	mPointOutline2->Render();

	switch (mIcon) {
	case Raccoon:
		mRaccoonIcon->Render();
		break;

	case Rabbit:
		mRabbitIcon->Render();
		break;

	case Bear:
		mBearIcon->Render();
	}
	mEnemyIcon->Render();

	for (auto ball : mBalls) {
		ball->Render();
	}

	mPlayer->Render();
	mEnemy->Render();

	mLeftWall->Render();
	mRightWall->Render();

	if (mPlayerPoints >= 1) {
		mPlayerPoint1->Render();
	}
	if (mPlayerPoints >= 2) {
		mPlayerPoint2->Render();
	}
	if (mPlayerPoints >= 3) {
		mPlayerPoint3->Render();
	}
	if (mPlayerPoints >= 4) {
		mPlayerPoint4->Render();
	}
	if (mPlayerPoints >= 5) {
		mPlayerPoint5->Render();
	}
	if (mEnemyPoints >= 1) {
		mEnemyPoint1->Render();
	}
	if (mEnemyPoints >= 2) {
		mEnemyPoint2->Render();
	}
	if (mEnemyPoints >= 3) {
		mEnemyPoint3->Render();
	}
	if (mEnemyPoints >= 4) {
		mEnemyPoint4->Render();
	}
	if (mEnemyPoints >= 5) {
		mEnemyPoint5->Render();
	}

	if(mHasWon){
		mWinText->Render();
	}
	if (mHasLost) {
		mLoseText->Render();
	}
}

