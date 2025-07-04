#include "Enemy.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "PlayScreen.h"

Enemy::Enemy() {
	mAudio = AudioManager::Instance();
	mTimer = Timer::Instance();

	mRaccoonRun = new AnimatedGLTexture("RaccoonSpriteSheet.png", 0, 0, 32, 32, 3, 0.3f, Animation::Layouts::Horizontal);
	mRaccoonRun->Parent(this);
	mRaccoonRun->Scale(Vector2(-4, 4));
	mRaccoonRun->Position(Vec2_Zero);
	mRaccoonRun->SetWrapMode(Animation::WrapModes::Loop);

	mRaccoonRunLoaded = new AnimatedGLTexture("RaccoonGunLoaded.png", 0, 0, 32, 32, 3, 0.3f, Animation::Layouts::Horizontal);
	mRaccoonRunLoaded->Parent(this);
	mRaccoonRunLoaded->Scale(Vector2(-4, 4));
	mRaccoonRunLoaded->Position(Vec2_Zero);
	mRaccoonRunLoaded->SetWrapMode(Animation::WrapModes::Loop);

	mMoveSpeed = 400.0f;
	mMoveBounds = Vector2(75.0f, 1920.0f);

	mHasBall = false;
	mIsMoving = false;

	Tag("Enemy");
	AddCollider(new BoxCollider(Vector2(50.0f, 100.0f)));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i] = new Bullet(true);
	}

	mWasHit = false;

	mCanMove = true;

	mBulletSpeed = 1000.0f;
}

Enemy::~Enemy() {
	mAudio = nullptr;
	mTimer = nullptr;

	delete mRaccoonRun;
	mRaccoonRun = nullptr;
	delete mRaccoonRunLoaded;
	mRaccoonRunLoaded = nullptr;

	for (int i = 0; i < MAX_BULLETS; ++i) {
		delete mBullets[i];
		mBullets[i] = nullptr;
	}

}


bool Enemy::IgnoreCollisions(){
	return false;
}

void Enemy::Hit(PhysEntity* other) {
	if (other->Tag() == "BallPickup") {
		BallPickup* ballPickup = dynamic_cast<BallPickup*>(other);
		if (ballPickup && !mHasBall) {
			mHasBall = true;
			ballPickup->Active(false); // Deactivate the BallPickup
		}
	}

	if (other->Tag() == "Bullet") {
		mWasHit = true;
		mAudio->PlaySFX("Hit.mp3");
	}
}

void Enemy::Update() {
	HandleMovement();
	CurrentTexture();
	mRaccoonRun->Update();
	mRaccoonRunLoaded->Update();

	HandleFiring();
	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Update();
	}

	PhysEntity::Update();
}

void Enemy::Render() {
	CurrentTexture();

	for (int i = 0; i < MAX_BULLETS; ++i) {
		mBullets[i]->Render();
	}

}


void Enemy::HandleMovement() {
	if (mCanMove) {
		if (mTarget) {
			// Calculate the difference in position between the enemy and the target (player)
			Vector2 direction = mTarget->Position(Local) - Position(Local);

			// Calculate the length of the vector (magnitude)
			float length = sqrt(direction.x * direction.x + direction.y * direction.y);

			// If the length is not zero (to avoid division by zero)
			if (length > 0) {
				// Normalize the direction manually
				direction.x /= length;
				direction.y /= length;
			}

			// Move the enemy towards the target
			Translate(direction * mMoveSpeed * mTimer->DeltaTime(), World);

			// Movement bounds
			Vector2 pos = Position(Local);

			// Update x-axis bounds
			if (pos.x < 1000.0f) {
				pos.x = 1000.0f;
			}
			if (pos.x > 1920) {
				pos.x = 1920;
			}

			if (pos.y < 600.0f) {
				pos.y = 600.0f;
			}
			if (pos.y > 1000.0f) {
				pos.y = 1000.0f;
			}
			Position(pos);
		}
		else {
			RandomMovement();
		}
	}
}


#include <iostream> // Include for debug output TODO

void Enemy::HandleFiring() {
	// Check if the enemy has a target and the enemy has the ball
	if (mTarget && mHasBall) {
		const float tolerance = 7.5f;
		float enemyY = Position(Local).y;
		float targetY = mTarget->Position(Local).y;

		// Fires a bullet when the enemy is at a close position to the player on the y axis
		if (fabs(enemyY - targetY) < tolerance) {
			for (int i = 0; i < MAX_BULLETS; ++i) {
				if (!mBullets[i]->Active()) {
					mAudio->PlaySFX("Shoot.mp3");
					Vector2 direction = Vector2(-1.0f, 0.0f);
					mBullets[i]->Fire(Position() - 100.0f, direction, mBulletSpeed);
					mBullets[i]->SetBallCreatedCallback([this](BallPickup* newBall) {
						GameEntity* parent = this->Parent();
						PlayScreen* playScreen = dynamic_cast<PlayScreen*>(parent);
						if (playScreen) {
							newBall->Parent(playScreen);
							newBall->SetPickupCallback([playScreen, newBall]() {
								playScreen->DeleteBall(newBall);
								});
							playScreen->HandleNewBallPickup(newBall);
						}
						});
					mHasBall = false;
					break;
				}
			}
		}
	}
}





void Enemy::SetTarget(PhysEntity* target) {
	mTarget = target;
}

void Enemy::RandomMovement() {
	if (mTarget) {
		// Get the player's Y position
		float playerY = mTarget->Position(Local).y;

		// Calculate the direction away from the player's Y position
		float directionY = (Position(Local).y > playerY) ? 1.0f : -1.0f;

		// Move the enemy away from the player's Y position
		Vector2 moveDirection(0.0f, directionY);
		Translate(moveDirection * mMoveSpeed * mTimer->DeltaTime(), Local);
	}
	else {
		// Default random movement if no target is set
		Vector2 randomDirection(rand() % 2 == 0 ? 2.0f : -2.0f, rand() % 2 == 0 ? 1.0f : -1.0f);
		Translate(randomDirection * mMoveSpeed * mTimer->DeltaTime(), Local);
	}
}

void Enemy::CurrentTexture() {
	if (mHasBall == false) {
		mRaccoonRun->Render();
	}
	else if (mHasBall == true) {
		mRaccoonRunLoaded->Render();
	}
}
