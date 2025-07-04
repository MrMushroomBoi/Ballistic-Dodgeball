#ifndef __PLAYER2_H
#define __PLAYER2_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"
#include "Player2CharacterSelectScreen.h"
#include "Bullet.h"

class Bullet;

using namespace SDLFramework;

class Player2 : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	enum PlayerType { Raccoon, Rabbit, Bear };
	PlayerType mPlayerType;

	enum RaccoonTextures { RaccoonDefault, RaccoonRun, RaccoonDefaultLoaded, RaccoonRunLoaded };
	RaccoonTextures mRaccoonCurrentTexture;

	enum RabbitTextures { RabbitDefault, RabbitRun, RabbitDefaultLoaded, RabbitRunLoaded };
	RabbitTextures mRabbitCurrentTexture;

	enum BearTextures { BearDefault, BearRun, BearDefaultLoaded, BearRunLoaded };
	BearTextures mBearCurrentTexture;

	Texture* mPlayer;

	//Raccoon Textures
	Texture* mRaccoon;
	AnimatedGLTexture* mRaccoonRun;
	Texture* mRaccoonLoaded;
	AnimatedGLTexture* mRaccoonRunLoaded;

	//Rabbit Textures
	Texture* mRabbit;
	AnimatedGLTexture* mRabbitRun;
	Texture* mRabbitLoaded;
	AnimatedGLTexture* mRabbitRunLoaded;

	//Bear Textures
	Texture* mBear;
	AnimatedGLTexture* mBearRun;
	Texture* mBearLoaded;
	AnimatedGLTexture* mBearRunLoaded;

	//Movement variables
	float mMoveSpeed;
	Vector2 mMoveBounds;
	float mBulletSpeed;

	void CurrentTexture();
	void HandleMovment();

public:
	Player2();
	~Player2();

	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	void HandleFiring();

	static const int MAX_BULLETS = 1000;
	Bullet* mBullets[MAX_BULLETS];

	bool mWasHit;

	bool mCanMove;

	//Bullets
	bool mHasBullet;

	void Update() override;
	void Render() override;
};

#endif
