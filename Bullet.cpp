#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Bullet::IgnoreCollisions() {
	return !Active();
}

Bullet::Bullet(bool friendly) {
	mTimer = Timer::Instance();

	mTexture = new GLTexture("Dodgeball Sprite.png");
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	mTexture->Scale(Vector2(2, 2));

	mSpeed = 500;

	Reload();

	Tag("Bullet");
	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectiles);
	
	mPickup = new BallPickup();
	mPickup->Active(false);
}

Bullet::~Bullet() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;

	delete mPickup;
	mPickup = nullptr;
	
}

void Bullet::Fire(Vector2 pos, Vector2 direction, float speed) {
	mSpeed = speed;
	Position(pos + 50);
	mDirection = direction;
	Active(true);
}

void Bullet::Reload() {
	Active(false);
}

void Bullet::Hit(PhysEntity* other) {
	if (other->Tag() == "Wall") {
		BallPickup* newPickup = new BallPickup();
		newPickup->Active(true);
		newPickup->Position(this->Position());
		newPickup->Parent(nullptr);
		Active(false);

		if (mBallCreatedCallback) {
			std::cout << "Bullet::Hit calling BallCreatedCallback" << std::endl;
			mBallCreatedCallback(newPickup);
		}
	}
	else if (other->Tag() == "Player" || other->Tag() == "Enemy") {
		Active(false);
	}
}

void Bullet::Update() {
	if (Active()) {
		Translate(mDirection * mSpeed * mTimer->DeltaTime());

		Vector2 pos = Position();
		if (pos.y < -OFFSCREEN_BUFFER || pos.x < -OFFSCREEN_BUFFER) {
			Reload();
		}
	}
}

void Bullet::Render() {
	if (Active()) {
		mTexture->Render();
	}
	if (mPickup->Active()) {
			mPickup->Render();
	}
	
}

void Bullet::SetBallCreatedCallback(BallCreatedCallback callback) {
	mBallCreatedCallback = callback;
}