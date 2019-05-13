#pragma once
#include "cocos2d.h"
#include "AudioEngine.h"

using namespace std;
USING_NS_CC;

class Obstacle
{
public:
	Obstacle(string type);
	~Obstacle();

	string name;											// 장애물의 종류
	Sprite* obstacleImage;									// 장애물의 이미지
	bool stopping;											// 정지하는 중인지 체크
	bool moving;											// 움직이는 중인지 체크
	float width;											// 장애물의 가로 길이
	float height;											// 장애물의 세로 길이
	Size visibleSize;										// 해상도

	void Stop();											// 정지하기
	void StopEnd();											// 정지 끝내기
	void Remove();											// 스폰장소로 이동하기
	void Move();											// 앞으로 움직이기
	void Fall();											// 떨어지는 장애물일 경우 떨어지기
	void PlayEffect();										// 떨어지고 소리 실행
	bool CheckNeedDelete();								// 삭제해야하는지 확인
};