#pragma once
#include "stdafx.h"
#include "Skarner.h"
#include "MasterYi.h"
#include "Riven.h"


using namespace std;
class Controller
{
public:
	Controller();
	~Controller();
	double PCFreq;
	__int64 CounterStart;
	int CounterCheck;
	ofstream out;
	static int choice1;
	static int choice2;
	shared_ptr<Champion> yi;
	shared_ptr<Champion> riven;
	shared_ptr<Champion> skarner;
	shared_ptr<Champion> champ1;
	shared_ptr<Champion> champ2;
	vector<shared_ptr<Champion>> pChampions;//vector of pointers to champion
	void SetStdOutToNewConsole();
	double clock;
	void runSim(HWND, HWND, HWND, HWND, HWND, HWND, HWND, HWND, HWND);
	double GetCounter();
	void StartCounter();
	INT getHealth1();
	INT getHealth2();
	void update_Time(HWND);
	//-------------------------------------------------------
	void basicAttackC1_TimeHandler();
	static void CALLBACK callBaseAttackC1(void* lpParametar,
				BOOLEAN TimerOrWaitFired);
	//-------------------------------------------------------
	void basicAttackC2_TimeHandler();
	static void CALLBACK callBaseAttackC2(void* lpParametar,
				BOOLEAN TimerOrWaitFired);
	//-------------------------------------------------------
	void updateRunTimeHandler();
	static void CALLBACK callToUpdateTime(void* lpParametar,
		BOOLEAN TimerOrWaitFired);
	//-------------------------------------------------------
	void updateChamp_1_HealthBar(HWND, HWND);
	void updateChamp_2_HealthBar(HWND, HWND);
	void updateHealthRegen();
	static void CALLBACK callToHealthRegen(void* lpParametar,
		BOOLEAN TimerOrWaitFired);
	//-------------------------------------------------------
	void updateChamp_1_ManaBar(HWND, HWND);
	void updateChamp_2_ManaBar(HWND, HWND);
	void updateMana();
	static void CALLBACK callToUpdateMana(void* lpParametar,
		BOOLEAN TimerOrWaitFired);
	//-------------------------------------------------------
	void champ2Q();
	static void CALLBACK callChamp2Q(void* lpParametar,
		BOOLEAN TimerOrWaitFired);
	//-------------------------------------------------------
	void champ1Q();
	static void CALLBACK callChamp1Q(void* lpParametar,
		BOOLEAN TimerOrWaitFired);
	//-------------------------------------------------------
	void champ2W();
	static void CALLBACK callChamp2W(void* lpParametar,
		BOOLEAN TimerOrWaitFired);
	//-------------------------------------------------------
	static void stopTimeOnDeath(Controller*, HANDLE);
	void checkDeath();
	void setClock(double);
};

//int Controller::choice1 = 0;
//int Controller::choice2 = 1;