#pragma once
#include "Champion.h"

class Skarner: virtual public Champion
{
public:
	Skarner();
	~Skarner();

	bool isAlive();
	UINT passive(Champion*);
	double dealDamage(double,double, Champion*);
	void getDamage(double,double);
	void healthRegeneration(double);
	void basicAttack(double, Champion*);
	void q(Champion*);
	void w(double time, Champion*);
	int stackQ;
	double bonusAD;
	int passiveCounter;
	//-------------------------------------------------------

	//-------------------------------------------------------
};

