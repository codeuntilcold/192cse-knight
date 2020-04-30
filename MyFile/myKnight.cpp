#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

///////////////////////////// DEBUG MACROS /////////////////////////////////
#ifndef DEBUG
#define LOG_STAT
#define LOG_IDENTITY
#else
#define LOG_IDENTITY cout << "Paladin " << isPaladin << " DragonKnight " << isDragonKnight << endl
#define LOG_STAT cout << i + 1 << "th event " << theEvent << ":\t" << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.remedy << ' ' << theKnight.maidenkiss << ' ' << theKnight.phoenixdown << endl
#endif

///////////////////////////// VERY EPIC ////////////////////////////////////
enum Drop { Base = 1, Excalibur = 8, Mithril, Excalipoor, DragonBlade = 23 };

const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;

struct knight
{
	int HP;
	int level;
	int remedy;
	int maidenkiss;
	int phoenixdown;
};

// read data from input file to corresponding variables
// return 1 if successfully done, otherwise return 0
int readFile(const char* filename, knight& theKnight, int& nEvent, int* arrEvent)
{
	const char* file_name = filename;
	FILE* f = 0;
	char* str = new char[MAX_CHARACTER_EACH_LINE];
	int num;

	f = fopen(file_name, "r");
	if (f == NULL)	//file not found || cannot read
		return 0;

	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (feof(f))
		return 0;

	int start = 0;
	int len = strlen(str);
	
	// read HP
	while (start < len && str[start] == ' ')
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.HP = num;
	if (theKnight.HP < 1 || theKnight.HP > 999)
		return 0;

	// read level
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.level = num;
	if (theKnight.level < 1 || theKnight.level > 10)
		return 0;

	// read remedy
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.remedy = num;
	if (theKnight.remedy < 0 || theKnight.remedy > 99)
		return 0;

	// read maidenkiss
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.maidenkiss = num;
	if (theKnight.maidenkiss < 0 || theKnight.maidenkiss > 99)
		return 0;

	// read phoenixdown
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.phoenixdown = num;
	if (theKnight.phoenixdown < 0 || theKnight.phoenixdown > 99)
		return 0;

	// read events
	nEvent = 0;
	while (1){
		if (feof(f))
			break;
		fgets(str, MAX_CHARACTER_EACH_LINE, f);
		if (str == NULL)
			break;
		start = 0;
		len = strlen(str);
    // cout << "\'" << str << "\'" << "\t" << len << endl;
		while (start < len){
			while (start < len && (str[start] > '9' || str[start] < '0'))
				start++;
			if (start >= len)
				break;
			arrEvent[nEvent] = 0;
			while (start < len && str[start] <= '9' && str[start] >= '0'){
				arrEvent[nEvent] = arrEvent[nEvent] * 10 + str[start] - '0';
				start++;
			}
			nEvent++;
		}
    delete[] str;
	}
	fclose(f);
	return 1;
}

void display(int* nOut)
{
	if (nOut)
		cout << *nOut;
	else
		cout << "Error!";
}

int main(int argc, char** argv)
{
    if (argc < 2) return 1;
    const char* filename = argv[1];	

	struct knight theKnight;
	int nEvent; //number of events
	int* arrEvent = new int[EVENT_SIZE];	// array of events
	
	readFile(filename, theKnight, nEvent, arrEvent);
	//cout << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.remedy << ' ' << theKnight.maidenkiss << ' ' << theKnight.phoenixdown << endl;


	int* nOut = new int;		//////////////////////////// VERY IMPORTANT POINT /////////////////////////
	int i;
	
	// SAVE DATA
	int levelO = 0, b = 0;
	int maxHP = theKnight.HP;
	int savedLevel = theKnight.level;

	// COUNTDOWN FLAG
	int isTiny = 0;
	int isFrog = 0;
	int odinBuff = 0;

	// ONE TIME FLAG
	bool metPrincess = false;
	bool metOdin = false;
	
	bool isArthur = (theKnight.HP == 999) ? true : false;
	bool isLancelot = (theKnight.HP == 888) ? true : false;
	bool isPaladin = true;
	bool isDragonKnight = false;
	
	Drop weapon = Base;
	Drop armor = Base;
	
	// IDENTITY
	if (theKnight.HP == 1) { isPaladin = false; }

	for (int itr = 2; itr < theKnight.HP / 2 + 1; itr++) { 
		if (theKnight.HP % itr == 0) 
		{ 
			isPaladin = false; 
		} 
	}

	if (theKnight.HP % 2 == 0 && !isLancelot) {				// Sum of Pythagorean triples is always even
		for (int x = 1; x < theKnight.HP / 3 + 1; x++) {
			for (int y = x + 1; y < theKnight.HP - x + 1; y++) {
				int z = theKnight.HP - x - y;

				if (x*x + y*y == z*z) { isDragonKnight = true; }
			}
		}
	}
	LOG_IDENTITY;

	// MAIN EVENTS
	for (i = 0; i < nEvent; i++)
	{
		int theEvent = arrEvent[i];

		b = (i + 1) % 10;
		levelO = ( (i + 1) > 6 ) ? ( b > 5 ? b : 5) : b;

		// NEW: Lancelot can pick up Excalipoor
		bool normalWin = isPaladin || odinBuff || (theKnight.level > levelO || isArthur) && weapon != Excalipoor || isDragonKnight && weapon == DragonBlade;
		bool normalLose = theKnight.level < levelO || weapon == Excalipoor;
	
		// MAIN EVENT		
		switch (theEvent)
		{
		case 0:		// BOWSER SURRENDERED 
		break;

		case 1:
		case 2:
		case 3:
		case 4:
		case 5:		// LOW LEVEL MONSTERS
			if (normalWin || weapon == Excalibur) 
			{ 
				theKnight.level = (theKnight.level > 9) ? (theKnight.level) : (++theKnight.level); 
			}
			else if (normalLose && armor!= Mithril)
			{
				float baseDamage;
				switch (theEvent)
				{
				case 1: baseDamage = 1; break;
				case 2:	baseDamage = 1.5; break;
				case 3:	baseDamage = 4.5; break;
				case 4:	baseDamage = 6.5; break;
				case 5:	baseDamage = 8.5; break;
				}
				
				int damage = baseDamage * levelO * 10;
				theKnight.HP = theKnight.HP - damage;
			}
		break;
		case 6:		// SHAMAN
			if (isTiny || isFrog) { break; }

			if (normalWin) 
			{ 
				theKnight.level = (theKnight.level + 2 > 10) ? 10 : (theKnight.level + 2);
			}
			else if (normalLose)
			{
				// NEW: Wearing Mithril and you won't lose health, but still get a *5 HP increase after this debuff
				if (armor != Mithril) { theKnight.HP = (theKnight.HP < 5) ? 1 : (theKnight.HP / 5); }
				isTiny = 4;	// Affects next 3 events
			}
		break;
		case 7:		// VAJSH
			if (isTiny || isFrog) { break; }

			if (normalWin) 
			{ 
				theKnight.level = (theKnight.level + 2 > 10) ? 10 : (theKnight.level + 2);
			}
			else if (normalLose)
			{
				savedLevel = theKnight.level;
				theKnight.level = 1;
				isFrog = 4;	// Affect next 3 events
			}
		break;

		case 8:		// EXCALIBUR
			if ( !(isDragonKnight && weapon == DragonBlade) ) { weapon = Excalibur; }
		break;
		case 9:		// MITHRIL
			armor = Mithril;
		break;
		case 10:	// EXCALIPOOR
			// NEW: Odin won't pick you a bad sword
			if ( !(theKnight.level > 4 || isArthur || isPaladin || isDragonKnight || odinBuff) )
				weapon = Excalipoor;
		break;

		case 11:	// MUSH MARIO
			theKnight.HP = (theKnight.HP + 50 > maxHP) ? maxHP : (theKnight.HP + 50);
		break;
		case 12:	// MUSH FIBO
			// Avoid cross initialization
			int upperFibo;
			int temp1, temp2, temp3;
			temp1 = 1, temp2 = 1, temp3 = 0;

			while (temp1 < theKnight.HP && temp2 < theKnight.HP && temp3 < theKnight.HP)
			{
				temp3 = temp2 + temp1; if (temp3 > theKnight.HP) { upperFibo = temp3; break; }
				temp1 = temp3 + temp2; if (temp1 > theKnight.HP) { upperFibo = temp1; break; }
				temp2 = temp1 + temp3; if (temp2 > theKnight.HP) { upperFibo = temp2; break; }
			}
			
			theKnight.HP = (upperFibo > maxHP) ? maxHP : upperFibo;
		break;
		case 13:	// MUSH GHOST
			if ( !(isPaladin || isDragonKnight && weapon == DragonBlade || armor == Mithril || odinBuff) ) 
			{ 
				theKnight.HP = (theKnight.HP < 51) ? 1 : (theKnight.HP - 50); 
			}
		break;
		case 14:	// MUSH KNIGHT
			maxHP = (maxHP + 50 > 999) ? 999 : (maxHP + 50);
			theKnight.HP = maxHP;
		break; 
		case 15:	// REMEDY
			if (theKnight.remedy < 99) { theKnight.remedy++; }
		break;
		case 16:	// MAIDENKISS
			if (theKnight.maidenkiss < 99) { theKnight.maidenkiss++; }
		break;			
		case 17:	// PHOENIX DOWN
			if (theKnight.phoenixdown < 99) { theKnight.phoenixdown++; }
		break;
		case 18:	// MERLIN
			if (isTiny) { isTiny = 0; }	// HP is full
			if (isFrog) { isFrog = 0; }	// Level stays the same

			if (theKnight.level < 10) { theKnight.level++; }

			theKnight.HP = maxHP;
		break;

		case 19:	// ABYSS
			if ( !(theKnight.level > 6 || isDragonKnight && weapon == DragonBlade || odinBuff) ) { *nOut = -1; }
		break;

		case 20:	// PRINCESS ESCAPED == Past become future
			metPrincess = true;
			
			//This is valid, but it destroys later events
			int past;
			past = 0;
			nEvent = 2 * i + 1;

			for (int future = nEvent - 1; future > i; future--) 
			{	
				arrEvent[future] = arrEvent[past++];
			}
		break;

		case 21:	// LIGHTWING
			for (int step = 0; step < 3; step++)
			{
				if (++i > nEvent - 1 || arrEvent[i] == 0 || arrEvent[i] == 20 || metPrincess)
				{
					i = nEvent;	// END ADVENTURE
				}
			}
		break;

		case 22:	// ODIN
			if (!metOdin) { odinBuff = 4; metOdin = true; }	// Can only meet Odin once
		break;

		case 23:	// DRAGON SWORD
			if (isDragonKnight) { weapon = DragonBlade; }
		break;

		case 99:	// BOWSER
			// NEW: Excalipoor = lose
			if (odinBuff || (isArthur || isLancelot || theKnight.level == 10) && weapon != Excalipoor || isPaladin && theKnight.level > 7 || isDragonKnight && weapon == DragonBlade)
			{
				theKnight.level = 10;
			}
			else
			{
				*nOut = -1;
			}
		break;
		} // SWITCH BREAK GOES HERE = EVENT IS DONE
		
		// AFTER EVENT
		if (isLancelot)	// LANCELOT - ARTHUR DUALITY
		{
			if (theKnight.level % 2 != 0) 
				{ isArthur = true; }
			else 
				{ isArthur = false; }
		}
		
		if (odinBuff) { odinBuff--; }	// Odin helps EVERY event		
		
		if (theKnight.HP < 1)	// NEAR-DEATH
		{
			if (theKnight.phoenixdown > 0)
			{
				theKnight.phoenixdown--;
				theKnight.HP = maxHP;

				if (isTiny) { isTiny = 0; }	// Full HP and no longer tiny
				if (isFrog) { isFrog = 0; }	// Level stays the same
			}
			else
			{
				*nOut = -1;
			}	
		}
				
		if (isTiny)	// RECOVER FROM SHAMAN ATTACK
		{
			if (theKnight.remedy > 0)	// IMMEDIATE RECOVERY
			{
				isTiny = 0;
				theKnight.remedy--;
				theKnight.HP *= 5;
				theKnight.HP = (theKnight.HP > maxHP) ? maxHP : theKnight.HP;
			}
			else if ( !(--isTiny) ) 	// SLOW RECOVERY
			{ 
				theKnight.HP *= 5;
				theKnight.HP = (theKnight.HP > maxHP) ? maxHP : theKnight.HP;
			}	
		}

		if (isFrog)	// RECOVER FROM VAJSH ATTACK
		{
			if (theKnight.maidenkiss > 0)	// IMMEDIATE RECOVERY
			{
				isFrog = 0;
				theKnight.maidenkiss--;
				theKnight.level = savedLevel;
			}
			else if ( !(--isFrog) )			// SLOW RECOVERY
			{
				theKnight.level = savedLevel;
			}
		}

		LOG_STAT;

		if (*nOut == -1 || theEvent == 0) { break; }
	}

	if (*nOut != -1)
	{
		*nOut = theKnight.HP + theKnight.level + theKnight.remedy + theKnight.maidenkiss + theKnight.phoenixdown;  
	}
	
	display(nOut);
	
	delete nOut;	//////////////////// VERY IMPORTANT //////////////////////////////////////
	delete[] arrEvent;

	return 0;
}

