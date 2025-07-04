#ifndef __MULTIPLAYERSCREEN_H
#define __MULTIPLAYERSCREEN_H
#include "Player.h"
#include "Player2.h"
#include "Scoreboard.h"
#include "Enemy.h"
#include "CharacterSelectScreen.h"
#include "BallPickup.h"
#include "Wall.h"
#include "Bullet.h"
#include <vector>


using namespace SDLFramework;

class MultiplayerScreen :public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	Texture* mBackground;

	//UI
	enum PlayerIcon { Raccoon, Rabbit, Bear };
	PlayerIcon mIcon;

	Texture* mRaccoonIcon;
	Texture* mRabbitIcon;
	Texture* mBearIcon;

	enum Player2Icon { Raccoon2, Rabbit2, Bear2 };
	Player2Icon mIcon2;

	Texture* mRaccoonIcon2;
	Texture* mRabbitIcon2;
	Texture* mBearIcon2;

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
	Player2* mPlayer2;

	std::vector<BallPickup*> mBalls;

	Wall* mLeftWall;
	Wall* mRightWall;

	int mPlayerPoints;
	int mEnemyPoints;

	bool mHasWon;
	bool mHasLost;

	Texture* mP1WinText;
	Texture* mP2WinText;

public:
	MultiplayerScreen();
	~MultiplayerScreen();

	void StartNewGame();

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
