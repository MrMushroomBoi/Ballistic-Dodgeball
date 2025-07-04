#ifndef __BULLET_H
#define __BULLET_H
#include "PhysEntity.h"
#include "Timer.h"
#include "BallPickup.h"
#include <functional>

class BallPickup;

using namespace SDLFramework;

class Bullet : public PhysEntity {
private:
	static const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;

	Texture * mTexture;

	float mSpeed;
	Vector2 mDirection;

	BallPickup* mPickup;

private:
	//Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:
	using BallCreatedCallback = std::function<void(BallPickup*)>;

	Bullet(bool friendly);
	~Bullet();

	void Fire(Vector2 pos, Vector2 direction, float speed);
	void Reload();

	// Inherited from PhysEntity
	void Hit(PhysEntity * other) override;

	void Update() override;
	void Render() override;

	void SetBallCreatedCallback(BallCreatedCallback callback);

	enum BulletState { Moving, Stationary };
	BulletState mBulletState;

private:
	BallCreatedCallback mBallCreatedCallback;
};
#endif