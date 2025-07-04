#ifndef __BALLPICKUP_H
#define __BALLPICKUP_H
#include "Player.h"
class Enemy;
#include "PhysEntity.h"
#include <functional>

using namespace SDLFramework;

class BallPickup : public PhysEntity {

private:
	Texture* mTexture;

	bool mWasHit;

public:
	using BallPickupCallback = std::function<void()>;

	BallPickup();
	~BallPickup();

	void Update() override;
	void Render() override;

	void Hit(PhysEntity* other) override;
	bool IgnoreCollisions() override;


	void SetPickupCallback(BallPickupCallback callback);

private:
	BallPickupCallback mCallback;


};

#endif