#pragma once

inline Vector2f operator+(Vector2f V1, Vector2f V2)
{
	Vector2f result;
	_asm
	{
		movlps xmm0, qword ptr [V1]
		movlps xmm1, qword ptr [V2]
		addps xmm0, xmm1
		movlps qword ptr [result], xmm0
	}

	return result;
}

inline Vector2f operator-(Vector2f V1, Vector2f V2)
{
	Vector2f result;
	_asm
	{
		movlps xmm0, qword ptr [V1]
		movlps xmm1, qword ptr [V2]
		subps xmm0, xmm1
		movlps qword ptr [result], xmm0
	}

	return result;
}

inline Vector2f operator*(Vector2f V, float F)
{
	Vector2f result;
	_asm
	{

		movlps xmm0, qword ptr [V]
		movss xmm1, dword ptr [F]
		shufps xmm1,xmm1,0
		mulps xmm0, xmm1
		movlps qword ptr [result], xmm0
	}

	return result;
}

inline Vector2f operator/(Vector2f V, float F)
{
	Vector2f result;
	_asm
	{

		movlps xmm0, qword ptr [V]
		movss xmm1, dword ptr [F]
		shufps xmm1,xmm1,0
		divps xmm0, xmm1
		movlps qword ptr [result], xmm0
	}

	return result;
}

inline bool operator==(Vector2f V1, Vector2f V2)
{
	long result;
	_asm
	{
		xorps xmm0, xmm0
		xorps xmm1, xmm1
		movlps xmm0, qword ptr [V1]
		movlps xmm1, qword ptr [V2]
		cmpeqps xmm0, xmm1
		movmskps eax, xmm0
		mov dword ptr [result], eax
	}
	return (result == 0xF);
}

inline bool operator!=(Vector2f V1, Vector2f V2)
{
	long result;
	_asm
	{
		xorps xmm0, xmm0
		xorps xmm1, xmm1
		movlps xmm0, qword ptr [V1]
		movlps xmm1, qword ptr [V2]
		cmpneqps xmm0, xmm1
		movmskps eax, xmm0
		mov dword ptr [result], eax
	}
	return (result == 0xF);
}
