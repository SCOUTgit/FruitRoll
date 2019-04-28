#pragma once
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Fruit
{
public:
	Fruit(string type);
	~Fruit();

	bool jumping;				// 점프하는 중인지 체크
	bool stopping;				// 정지하는 중인지 체크
	float fruitRadius;			// 과일의 반지름
	float width;				// 과일의 가로 길이
	float height;				// 과일의 세로 길이

	string fruitType;			// 과일의 종류
	Sprite* fruitImage;			// 과일의 이미지
	Animation* fruitAnimation;	// 과일애니메이션

	void MakeSprite();			// 애니메이트 생성
	void Jump();				// 점프하기
	void JumpEnd();				// 점프 끝내기
	void Stop();				// 정지하기
	void StopEnd();				// 정지 끝내기
	void Rotate();				// 구르기
	void PlayAnimation();		// 충돌 시 애니메이션 실행
};