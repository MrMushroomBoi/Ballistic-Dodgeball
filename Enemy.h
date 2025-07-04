#ifndef __ENEMY_H
#define __ENEMY_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "PhysEntity.h"
#include "Bullet.h"
#include "Timer.h"
#include <iostream>
class Player;
class PlayScreen;

using namespace SDLFramework;

class Enemy : public PhysEntity {
private:

	AudioManager* mAudio;
	Timer* mTimer;

	//Textures
	AnimatedGLTexture* mRaccoonRun;
	AnimatedGLTexture* mRaccoonRunLoaded;

	//Movement
	bool mIsMoving;
	float mMoveSpeed;
	Vector2 mMoveBounds;
	float mBulletSpeed;

	PhysEntity* mTarget = nullptr;
	
	void CurrentTexture();
	void HandleMovement();
	void HandleFiring();

public:
	Enemy();
	~Enemy();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;

	void SetTarget(PhysEntity* target);
	bool mHasBall;

	void RandomMovement();

	void Update() override;
	void Render() override;

	//Bullets
	static const int MAX_BULLETS = 1000;
	Bullet* mBullets[MAX_BULLETS];

	bool mWasHit;
	bool mCanMove;

	PhysEntity* GetTarget() const {
		return mTarget;
	}

};
#endif