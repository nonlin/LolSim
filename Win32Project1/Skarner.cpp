#include "stdafx.h"
#include "Skarner.h"


Skarner::Skarner()
{
	levelMultiplier = 1;
	healthM = 96;
	healthRegenM = 0.85;
	manaM = 40;
	manaRegenM = 0.45;
	ADM = 4.2;
	ASM = 2.1;
	ARM = 3.8;
	MRM = 1.25;
	/////////////
	alive = true;
	health = 440 + (levelMultiplier * healthM);
	maxHealth = 440 + (levelMultiplier * healthM);
	healthRegen = 7.5 + (levelMultiplier * healthRegenM);
	mana = 205 + (levelMultiplier * manaM);
	maxMana = 205 + (levelMultiplier * manaM);
	manaRegen = 6.45 + (levelMultiplier * manaRegenM);
	range = 125;
	attackDamage = 54.1 + (levelMultiplier * ADM);
	attackSpeed = 0.625;
	attackSpeed = floor((attackSpeed + (((levelMultiplier * ASM) / 100) * attackSpeed )) * 1000 + 0.5) / 1000;
	armor =round( 23 + (levelMultiplier * ARM));
	magicRes = 30 + (levelMultiplier * MRM);
	magicDamage = 0;
	bonusMagicDamage = 0;
	stackQ = 0;
	coolDownQ = 3.5;
	coolDownW = 16;
	coolDownE = 14;
	coolDownR = 130;
	damageOut = 0;
	physicalDamage = 0;
	bonusAD = 0;
	critChance = 0;
	attacking = false;
	name = L"Skarner";
	out.open("skarnerLog.txt");

}

HANDLE wShiledTimer = NULL;
Skarner::~Skarner()
{
}

UINT Skarner::passive(Champion* enemy){

		coolDownQ = coolDownQ - 1;
		coolDownW = coolDownQ - 1;
		coolDownE = coolDownQ - 1;
		coolDownR = coolDownQ - 1;
		//if (coolDownQ < 0)
	out << "Q COOLD DOWN" <<coolDownQ << endl;
	return 0;
}

void Skarner::q(Champion* enemy){

	if (mana >= 16){
		Beep(500, 100);
		//range = 350;
		out << "Q ATTACK SKARNER" << endl;
		mana = mana - 16;
		if (stackQ == 0)
			physicalDamage = 25 + (bonusAD* 0.80);
		stackQ++;
		if (stackQ == 1){
			attackSpeed = attackSpeed*(0.08) + attackSpeed;
			physicalDamage = physicalDamage + (physicalDamage * .24);
			magicDamage = 24;
		}
		if (stackQ == 2){
			attackSpeed = attackSpeed*(0.08) + attackSpeed;
			physicalDamage = physicalDamage + (physicalDamage * .24);
			magicDamage = 24;
		}
		if (stackQ == 3){
			attackSpeed = attackSpeed*(0.08) + attackSpeed;
			physicalDamage = physicalDamage + (physicalDamage * .24);
			magicDamage = 24;
		}
		coolDownQ = 3.5;

		dealDamage(physicalDamage,magicDamage,enemy);
		
	}

}

void Skarner::w(double time, Champion* enemy){

	double shield = 80 + (bonusMagicDamage * 0.80);
	if (mana >= 50){
		mana = mana - 50;
		health = health + shield;
		std::clock_t start = std::clock();
		int wait, passed, old;
		float fPassed;

		wait = 6;
		passed = old = 0;
		while (std::clock() - start < wait * CLOCKS_PER_SEC){
			passed = std::clock() - start;
			if (passed > old){
				fPassed = ((float) passed) / CLOCKS_PER_SEC;
				printf("\r%.3f...", fPassed);
				//old = passed;
			}
		}
		//else
			
	}
}

void Champion::e(){

	if (coolDownE == 0 && mana >= 100){
	
		range = 350;
		mana = mana - 100;
		damageOut = 200 + (1 * (magicDamage));
	}
}

void Champion::r(){

}


void Skarner::basicAttack(double clock, Champion* enemy){

	range = 125;
	passiveCounter ++;
	//cout << "Time : " << clock << endl;
	//out << "Time : " << clock << endl;
	clock = floor(clock * 10 + 0.5) / 10;
	cout << "TIME TO ATTACK: " << clock << endl;
	out << "TIME TO ATTACK: " << clock << endl;
	dealDamage(attackDamage, 0,enemy);


}

double Skarner::dealDamage( double damage, double magicDamage, Champion* enemy){
	
	
		cout << "Skarner Attacking with " << damage << " damage" << endl;
		out << "Skarner Attacking with " << damage << " damage" << endl;
		out << "Skarner dealing magic with " << magicDamage << " Mdamage" << endl;
		enemy->getDamage(damage,magicDamage);

	
	return damageOut;
}

void Skarner::getDamage(double damage, double magicDamage){

	if (armor >= 0)
		damage = damage * (100 / (100 + armor));
	else
		damage = damage * (2 - (100 / (100 + armor)));

	if (magicRes >= 0)
		magicDamage = magicDamage * (100 / (100 + magicRes));
	else
		magicDamage = magicDamage * (2 - (100 / (100 + magicRes)));

	if (health > 0){ 
		health = health - damage; 
		health = health - magicDamage;
	}
	char str[256];

	sprintf_s(str, "Skarner Recieved Damage of", damage);
	OutputDebugString((LPCWSTR)str);
	cout << "Skarner Recieved Damage of" << damage << endl;
}

void Skarner::healthRegeneration(double clock){

	//	out << "Calling health regen." << endl;
		if (health < maxHealth)
			health = health + (healthRegen / 10);
}

bool Skarner::isAlive(){
	
	if (health <= 0){

		return false;
	}
	else
		return true;

}

