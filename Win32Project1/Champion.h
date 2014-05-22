#pragma once
#include "stdafx.h"

using namespace std;
class Champion
{
public:
	Champion();
	~Champion();
	ofstream out;
	int levelMultiplier;
	double healthM;
	double healthRegenM;
	double manaM;
	double manaRegenM;
	double ADM;
	double ASM;
	double ARM;
	double MRM;
	//Champion* enemy;
	double maxHealth;
	double health;
	double healthRegen;
	double mana;
	double maxMana;
	double manaRegen;
	int range;
	double attackDamage;
	double attackSpeed;
	double armor;
	double magicRes;
	double magicDamage;
	int moveSpeed;
	double coolDownQ;
	double coolDownW;
	double coolDownE;
	double coolDownR;
	double coolDownReduction;
	double damageOut;
	double physicalDamage;
	double critChance;
	double bonusMagicDamage;
	LPCWSTR name;
	virtual void q(Champion* enemy) = 0;
	virtual void w(double time, Champion* enemy) = 0;
	void e();
	void r();
	//bool basicAttack(double, Champion*);
	bool attacking;
	bool alive;
	virtual UINT passive(Champion*) = 0;
	virtual double dealDamage(double, double, Champion*) = 0;
	virtual void getDamage(double,double) = 0;
	virtual void healthRegeneration(double) = 0;
	virtual void basicAttack(double, Champion*) = 0;
	virtual bool isAlive() = 0;

};

