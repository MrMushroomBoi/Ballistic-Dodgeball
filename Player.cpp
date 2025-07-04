#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mMoveBounds = Vector2(75.0f, 1100.0f);
	mMoveSpeed = 0;
	mBulletSpeed = 0.0f;

	//Raccoon Textures
	mRaccoon = new GLTexture("RaccoonSpriteSheet.png", 0, 0, 32, 32);
	mRaccoon->Parent(this);
	mRaccoon->Scale(Vector2(4, 4));
	mRaccoon->Position(Vec2_Zero);

	mRaccoonRun = new AnimatedGLTexture("RaccoonSpriteSheet.png", 0, 0, 32, 32, 3, 0.3f, Animation::Layouts::Horizontal);
	mRaccoonRun->Parent(this);
	mRaccoonRun->Scale(Vector2(4, 4));
	mRaccoonRun->Position(Vec2_Zero);
	mRaccoonRun->SetWrapMode(Animation::WrapModes::Loop);

	mRaccoonLoaded = new GLTexture("RaccoonGunLoaded.png", 0, 0, 32, 32);
	mRaccoonLoaded->Parent(this);
	mRaccoonLoaded->Scale(Vector2(4, 4));
	mRaccoonLoaded->Position(Vec2_Zero);

	mRaccoonRunLoaded = new AnimatedGLTexture("RaccoonGunLoaded.png", 0, 0, 32, 32, 3, 0.3f, Animation::Layouts::Horizontal);
	mRaccoonRunLoaded->Parent(this);
	mRaccoonRunLoaded->Scale(Vector2(4, 4));
	mRaccoonRunLoaded->Position(Vec2_Zero);
	mRaccoonRunLoaded->SetWrapMode(Animation::WrapModes::Loop);

	//Rabbit Textures
	mRabbit = new GLTexture("RabbitSpriteSheet.png", 0, 0, 32, 32);
	mRabbit->Parent(this);
	mRabbit->Scale(Vector2(4, 4));
	mRabbit->Position(Vec2_Zero);

	mRabbitRun = new AnimatedGLTexture("RabbitSpriteSheet.png", 0, 0, 32, 32, 3, 0.3f, Animation::Layouts::Horizontal);
	mRabbitRun->Parent(this);
	mRabbitRun->Scale(Vector2(4, 4));
	mRabbitRun->Position(Vec2_Zero);
	mRabbitRun->SetWrapMode(Animation::WrapModes::Loop);

	mRabbitLoaded = new GLTexture("RabbitGunLoaded.png", 0, 0, 32, 32);
	mRabbitLoaded->Parent(this);
	mRabbitLoaded->Scale(Vector2(4, 4));
	mRabbitLoaded->Position(Vec2_Zero);

	mRabbitRunLoaded = new AnimatedGLTexture("RabbitGunLoaded.png", 0, 0, 32, 32, 3, 0.3f, Animation::Layouts::Horizontal);
	mRabbitRunLoaded->Parent(this);
	mRabbitRunLoaded->Scale(Vector2(4, 4));
	mRabbitRunLoaded->Position(Vec2_Zero);
	mRabbitRunLoaded->SetWrapMode(Animation::WrapModes::Loop);

	//Bear Textures
	mBear = new GLTexture("BearSpriteSheet.png", 0, 0, 32, 32);
	mBear->Parent(this);
	mBear->Scale(Vector2(4, 4));
	mBear->Position(Vec2_Zero);

	mBearRun = new AnimatedGLTexture("BearSpriteSheet.png", 0, 0, 32, 32, 3, 0.3f, Animation::Layouts::Horizontal);
	mBearRun->Parent(this);
	mBearRun->Scale(Vector2(4, 4));
	mBearRun->Position(Vec2_Zero);
	mBearRun->SetWrapMode(Animation::WrapModes::Loop);

	mBearLoaded = new GLTexture("BearGunLoaded.png", 0, 0, 32, 32);
	mBearLoaded->Parent(this);
	mBearLoaded->Scale(Vector2(4, 4));
	mBearLoaded->Position(Vec2_Zero);

	mBearRunLoaded = new AnimatedGLTexture("BearGunLoaded.png", 0, 0, 32, 32, 3, 0.3f, Animation::Layouts::Horizontal);
	mBearRunLoaded->Parent(this);
	mBearRunLoaded->Scale(Vector2(4, 4));
	mBearRunLoaded->Position(Vec2_Zero);
	mBearRunLoaded->SetWrapMode(Animation::WrapModes::Loop);

	Tag("Player");
	AddCollider(new BoxCollider(Vector2(50.0f, 100.0f)));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	mPlayer = mRabbit;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(true);
	}

	mWasHit = false;

	mCanMove = true;
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mRaccoon;
	mRaccoon = nullptr;
	delete mRaccoonRun;
	mRaccoonRun = nullptr;
	delete mRaccoonLoaded;
	mRaccoonLoaded = nullptr;
	delete mRaccoonRunLoaded;
	mRaccoonRunLoaded = nullptr;

	delete mRabbit;
	mRabbit = nullptr;
	delete mRabbitRun;
	mRabbitRun = nullptr;
	delete mRabbitLoaded;
	mRabbitLoaded = nullptr;
	delete mRabbitRunLoaded;
	mRabbitRunLoaded = nullptr;

	delete mBear;
	mBear = nullptr;
	delete mBearRun;
	mBearRun = nullptr;
	delete mBearLoaded;
	mBearLoaded = nullptr;
	delete mBearRunLoaded;
	mBearRunLoaded = nullptr;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

void Player::Update() {
	int selectedCharacter = CharacterSelectScreen::SelectedCharacter();

	if (selectedCharacter == 0) {
		mPlayerType = Raccoon;
	}
	if (selectedCharacter == 1) {
		mPlayerType = Rabbit;
	}
	if (selectedCharacter == 2) {
		mPlayerType = Bear;
	}

	//Animations
	mRaccoonRun->Update();
	mRaccoonRunLoaded->Update();
	mRabbitRun->Update();
	mRabbitRunLoaded->Update();
	mBearRun->Update();
	mBearRunLoaded->Update();

	CurrentTexture();
	HandleMovment();
	HandleFiring();

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}

	PhysEntity::Update();
}

void Player::Render() {
	CurrentTexture();

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}

}

void Player::CurrentTexture() {
	switch (mPlayerType) {
	case Raccoon:
	
		if (mInput->KeyDown(SDL_SCANCODE_W) || mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_S) || mInput->KeyDown(SDL_SCANCODE_D)) {
			mRaccoonCurrentTexture = RaccoonRun;
		}
		else {
			mRaccoonCurrentTexture = RaccoonDefault;
		}


		if (mHasBullet == true) {
			if (mInput->KeyDown(SDL_SCANCODE_W) || mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_S) || mInput->KeyDown(SDL_SCANCODE_D)) {
				mRaccoonCurrentTexture = RaccoonRunLoaded;
			}
			else {
				mRaccoonCurrentTexture = RaccoonDefaultLoaded;
			}
		}

		//Render
		if (mRaccoonCurrentTexture == RaccoonRun) {
			mRaccoonRun->Render();
		}

		if (mRaccoonCurrentTexture == RaccoonDefault) {
			mRaccoon->Render();
		}

		if (mRaccoonCurrentTexture == RaccoonRunLoaded) {
			mRaccoonRunLoaded->Render();
		}

		if (mRaccoonCurrentTexture == RaccoonDefaultLoaded) {
			mRaccoonLoaded->Render();
		}

		break;

	case Rabbit:
		if (mInput->KeyDown(SDL_SCANCODE_W) || mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_S) || mInput->KeyDown(SDL_SCANCODE_D)) {
			mRabbitCurrentTexture = RabbitRun;
		}
		else {
			mRabbitCurrentTexture = RabbitDefault;
		}

		if (mHasBullet == true) {
			if (mInput->KeyDown(SDL_SCANCODE_W) || mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_S) || mInput->KeyDown(SDL_SCANCODE_D)) {
				mRabbitCurrentTexture = RabbitRunLoaded;
			}
			else {
				mRabbitCurrentTexture = RabbitDefaultLoaded;
			}
		}

		//Render
		if (mRabbitCurrentTexture == RabbitRun) {
			mRabbitRun->Render();
		}

		if (mRabbitCurrentTexture == RabbitDefault) {
			mRabbit->Render();
		}

		if (mRabbitCurrentTexture == RabbitRunLoaded) {
			mRabbitRunLoaded->Render();
		}

		if (mRabbitCurrentTexture == RabbitDefaultLoaded) {
			mRabbitLoaded->Render();
		}
		break;

	case Bear:
		if (mInput->KeyDown(SDL_SCANCODE_W) || mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_S) || mInput->KeyDown(SDL_SCANCODE_D)) {
			mBearCurrentTexture = BearRun;
		}
		else {
			mBearCurrentTexture = BearDefault;
		}

		if (mHasBullet == true) {
			if (mInput->KeyDown(SDL_SCANCODE_W) || mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_S) || mInput->KeyDown(SDL_SCANCODE_D)) {
				mBearCurrentTexture = BearRunLoaded;
			}
			else {
				mBearCurrentTexture = BearDefaultLoaded;
			}
		}

		//Render
		if (mBearCurrentTexture == BearRun) {
			mBearRun->Render();
		}

		if (mBearCurrentTexture == BearDefault) {
			mBear->Render();
		}

		if (mBearCurrentTexture == BearRunLoaded) {
			mBearRunLoaded->Render();
		}

		if (mBearCurrentTexture == BearDefaultLoaded) {
			mBearLoaded->Render();
		}
		break;
	}
}

bool Player::IgnoreCollisions() {
	return false;
}

void Player::Hit(PhysEntity* other) {
	if (other->Tag() == "BallPickup") {
		BallPickup* ballPickup = dynamic_cast<BallPickup*>(other);
		if (ballPickup && !mHasBullet) {
			mHasBullet = true;
			ballPickup->Active(false); // Deactivate the BallPickup
		}
	}

	if (other->Tag() == "Bullet") {
		mWasHit = true;
		mAudio->PlaySFX("Hit.mp3");
	}
	
}


void Player::HandleMovment() {
	if (mCanMove) {
		switch (mPlayerType) {
		case Raccoon:
			mMoveSpeed = 500.0f;
			break;

		case Rabbit:
			mMoveSpeed = 1000.0f;
			break;

		case Bear:
			mMoveSpeed = 250.0f;
			break;
		}

		if (mInput->KeyDown(SDL_SCANCODE_W)) {
			Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
		}
		if (mInput->KeyDown(SDL_SCANCODE_S)) {
			Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
		}
		if (mInput->KeyDown(SDL_SCANCODE_D)) {
			Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		}
		if (mInput->KeyDown(SDL_SCANCODE_A)) {
			Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
		}


		Vector2 pos = Position(Local);
		//Movement bounds
		if (pos.x < mMoveBounds.x + mPlayer->ScaledDimensions().x * -0.3f) {
			pos.x = mMoveBounds.x + mPlayer->ScaledDimensions().x * -0.3f;
		}
		if (pos.x > mMoveBounds.y - mPlayer->ScaledDimensions().x * 1.2f) {
			pos.x = mMoveBounds.y - mPlayer->ScaledDimensions().x * 1.2f;
		}
		if (pos.y < mMoveBounds.x + mPlayer->ScaledDimensions().y * 4.1f) {
			pos.y = mMoveBounds.x + mPlayer->ScaledDimensions().y * 4.1f;
		}
		if (pos.y > mMoveBounds.y - mPlayer->ScaledDimensions().y * 0.9f) {
			pos.y = mMoveBounds.y - mPlayer->ScaledDimensions().y * 0.9f;
		}
		Position(pos);
	}
}


void Player::HandleFiring() {
	switch (mPlayerType) {
	case Raccoon:
		mBulletSpeed = 1000.0f;
		break;
	case Rabbit:
		mBulletSpeed = 500.0f;
		break;
	case Bear:
		mBulletSpeed = 1500.0f;
		break;
	}

	if (mInput->KeyPressed(SDL_SCANCODE_SPACE) && mHasBullet == true) {
		for (int i = 0; i < MAX_BULLETS; ++i) {
			if (!mBullets[i]->Active()) {
				mAudio->PlaySFX("Shoot.mp3");
				Vector2 direction = Vector2(1.0f, 0.0f);
				mBullets[i]->Fire(Position(), direction, mBulletSpeed);
				mHasBullet = false;
				break;
			}
		}
	}
}

