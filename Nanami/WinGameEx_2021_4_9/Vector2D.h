#pragma once

class Vector2D
{
public:
	float    x;
	float    y;

public:
	Vector2D();		//생성자 선언
	Vector2D(float a_X, float a_Y) //생성자 함수의 오버로딩
	{
		x = a_X;
		y = a_Y;
	}
	~Vector2D();	//소멸자 선언

	//-----글로벌 연산자 오버라이딩 함수 선언과 정의
	friend Vector2D operator +(const Vector2D& T1, const Vector2D& T2);
	friend Vector2D operator -(const Vector2D& T1, const Vector2D& T2);
	friend Vector2D operator *(const Vector2D& T1, const float& T2);
	friend Vector2D operator *(const float& T1, const Vector2D& T2);
	//-----글로벌 연산자 오버라이딩 함수 선언과 정의

	float Magnitude();    //벡터의 크기만 구해오기 함수
	void  Normalize();    //노멀 백터로 만들기...

	static Vector2D GetNormalFromRotation(float RotationYaw);  //각도를 벡터로 환산하는 함수
	float GetAngle();     //벡터를 각도로 환산하는 함수
};

//글로벌 함수, 두점의 사이각을 구하는 함수 선언
float GetAngle(Vector2D& a_A, Vector2D& a_B);