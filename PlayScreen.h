#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Player.h"
#include "Scoreboard.h"
#include "Enemy.h"
#include "CharacterSelectScreen.h"
#include "BallPickup.h"
#include "Wall.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

class PlayScreen : public GameEntity {
private:
	Timer * mTimer;
	AudioManager * mAudio;

	Texture* mBackground;

	//UI
	enum PlayerIcon { Raccoon, Rabbit, Bear};
	PlayerIcon mIcon;
	Texture* mEnemyIcon;

	Texture* mRaccoonIcon;
	Texture* mRabbitIcon;
	Texture* mBearIcon;

	//Points
	Texture* mPointOutline1;
	Texture* mPointOutline2;

	Texture* mPlayerPoint1;
	Texture* mPlayerPoint2;
	Texture* mPlayerPoint3;
	Texture* mPlayerPoint4;
	Texture* mPlayerPoint5;

	Texture* mEnemyPoint1;
	Texture* mEnemyPoint2;
	Texture* mEnemyPoint3;
	Texture* mEnemyPoint4;
	Texture* mEnemyPoint5;

	Player* mPlayer;
	Enemy* mEnemy;

	std::vector<BallPickup*> mBalls;

	Wall* mLeftWall;
	Wall* mRightWall;

	int mPlayerPoints;
	int mEnemyPoints;

	bool mHasWon;
	bool mHasLost;

	Texture* mWinText;
	Texture* mLoseText;

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void EnemyMovment();
	void UpdateEnemyTarget();

	void DeleteBall(BallPickup* ball);
	void HandleNewBallPickup(BallPickup* ball);

	void StartNewRound();
	void RoundReset();

	void Win();
	void Lose();

	bool mGameOver;
	float mGameOverTimer;

	void Update() override;
	void Render() override;

};
#endif