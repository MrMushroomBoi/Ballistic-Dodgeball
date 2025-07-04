#include "Wall.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include <iostream>

Wall::Wall() {
	Tag("Wall");
	AddCollider(new BoxCollider(Vector2(50.0f,1000.0f)));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);


}

Wall::~Wall() {
	
}

void Wall::Update() {
	PhysEntity::Update();
	
}

void Wall::Render() {
	

}

void Wall::Hit(PhysEntity* other) {
	
}

bool Wall::IgnoreCollisions() {
	return false;
}
