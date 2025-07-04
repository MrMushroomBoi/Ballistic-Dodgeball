#include "BallPickup.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Enemy.h"
#include <iostream>

BallPickup::BallPickup() {
	mTexture = new GLTexture("Dodgeball Sprite.png");
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mTexture->Scale(Vector2(2, 2));

	Tag("BallPickup");
	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	mWasHit = false;
	mCallback = nullptr;
}

BallPickup::~BallPickup() {
	delete mTexture;
	mTexture = nullptr;
}

void BallPickup::Update() {
	if (Active()) {
		PhysEntity::Update();
	}
}

void BallPickup::Render() {
	if (Active()) {
		mTexture->Render();
	}

}

void BallPickup::Hit(PhysEntity* other) {
	if ((other->Tag() == "Player" )) {
		Player* player = dynamic_cast<Player*>(other);
		if (player && !player->mHasBullet) {
			player->mHasBullet = true;
			mWasHit = true;
			Active(false);

			if (mCallback) {
				mCallback();
			}
		}
	}

	else if ((other->Tag() == "Enemy")) {
		Enemy* enemy = dynamic_cast<Enemy*>(other);
			if (enemy && !enemy->mHasBall) {
				enemy->mHasBall = true;
				mWasHit = true;
				Active(false);

				if (mCallback) {
					mCallback();
				}
			}
	}

	if ((other->Tag() == "Bullet")) {
		Active(true);
	}
}

bool BallPickup::IgnoreCollisions() {
	return !Active();
}

void BallPickup::SetPickupCallback(BallPickupCallback callback) {
	mCallback = callback;
}