#ifndef __WALL_H
#define __WALL_H
#include "PhysEntity.h"

using namespace SDLFramework;

class Wall : public PhysEntity {
public:
	Wall();
	~Wall();

	void Update() override;
	void Render() override;

	void Hit(PhysEntity* other) override;
	bool IgnoreCollisions() override;

};

#endif