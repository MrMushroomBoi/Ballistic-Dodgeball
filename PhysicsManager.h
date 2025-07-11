#ifndef __PHYSICSMANAGER_H
#define __PHYSICSMANAGER_H
#include <bitset>
#include "PhysEntity.h"

class PhysicsManager {
public:
	enum class CollisionLayers {
		Friendly,
		FriendlyProjectiles,
		Hostile,
		HostileProjectiles,
		Pickup,
		MaxLayers
	};

	enum class CollisionFlags {
		None				= 0x00,	// 00000000
		Friendly			= 0x01, // 00000001
		FriendlyProjectiles = 0x02, // 00000010
		Hostile				= 0x04, // 00000100
		HostileProjectiles	= 0x08, // 00001000
		Pickup      		= 0x10  // 00010000
	};

private:
	static PhysicsManager * sInstance;

	std::vector<PhysEntity * > mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long mLastId;

public:
	static PhysicsManager * Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysEntity * entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void Update();

private:
	PhysicsManager();
	~PhysicsManager();
};

inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}
#endif