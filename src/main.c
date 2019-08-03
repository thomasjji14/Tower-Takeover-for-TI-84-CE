/*
* --------------------------------------
* Program Name : Tower Takeover Calculator for TI - 84 CE
* Author : Thomas Ji
* License : N / A
* Description : Takes input from the user, showing the best possible movesand the results of all possible actions in Tower Takeover, by Vex.
* --------------------------------------
*/

#include "main.h"
#include "graphics.h"


int main() {
	// Defaults the auton winner to a tie
	auton autonWinner = AUTON_TIE;

	teamColor teamCol = TEAM_COLOR_RED;

	uint8_t towers[3], allianceS[3], enemyS[3];
	uint8_t future[2][3][3];

	bool toUpdate[4];

	uint8_t allianceScore = 0, enemyScore = 0;

	kb_SetMode(MODE_3_CONTINUOUS);

	gfx_Begin();
	initGUI();
	do {
		update(towers, allianceS, enemyS, &autonWinner, toUpdate, &teamCol);

		allianceScore = calcScore(towers, allianceS, autonWinner, TEAM_ALLIANCE);
		enemyScore = calcScore(towers, enemyS, autonWinner, TEAM_ENEMY);
		calcFuture(future, towers, allianceS, autonWinner);

		draw(teamCol, toUpdate);
	} while (kb_Data[1] != kb_Graph);
	gfx_End();
	return 0;
}


void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[],
			auton *a, bool updates[], teamColor *col) {
	
	// uint8_t num = 1;
	// uint8_t i = 0;
	// uint8_t oldTowers[3], oldAllianceStack[3], oldEnemyStack[3];

	// if (kb_Data[3] & kb_4)	num = 4;
	// else if (kb_Data[3] & kb_7)	num = 7;
	// else if (kb_Data[4] & kb_2)	num = 2;
	// else if (kb_Data[4] & kb_5)	num = 5;
	// else if (kb_Data[4] & kb_8)	num = 8;
	// else if (kb_Data[5] & kb_3)	num = 3;
	// else if (kb_Data[5] & kb_6)	num = 6;
	// else if (kb_Data[5] & kb_9)	num = 9;


	// memcpy(oldTowers, towers, 3 * sizeof(uint8_t));
	// memcpy(oldAllianceStack, allianceStack, 3 * sizeof(uint8_t));
	// memcpy(oldEnemyStack, enemyStack, 3 * sizeof(uint8_t));

	// if (kb_Data[1] & kb_Yequ) {
	// 	updates[0] = true;
	// 	*col = *col == TEAM_COLOR_BLUE ? TEAM_COLOR_RED : TEAM_COLOR_BLUE;
	// }
	// else if (kb_Data[1] & kb_Trace) {
	// 	updates[1] = true;
	// }


	// if (kb_Data[1] & kb_2nd) towers[0] += num;
	// else if (kb_Data[2] & kb_Alpha)	towers[0] -= num;
	// else if (kb_Data[1] & kb_Mode)	towers[1] += num;
	// else if (kb_Data[3] & kb_GraphVar)	towers[1] -= num;
	// else if (kb_Data[1] & kb_Del) towers[2] += num;
	// else if (kb_Data[4] & kb_Stat) towers[2] -= num;
	// else if (kb_Data[2] & kb_Math) allianceStack[0] += num;
	// else if (kb_Data[2] & kb_Recip) allianceStack[1] += num;
	// else if (kb_Data[2] & kb_Square) allianceStack[2] += num;
	// else if (kb_Data[3] & kb_Apps) allianceStack[0] -= num;
	// else if (kb_Data[3] & kb_Sin) allianceStack[1] -= num;
	// else if (kb_Data[3] & kb_Comma) allianceStack[2] -= num;
	// else if (kb_Data[5] & kb_Vars) enemyStack[0] += num;
	// else if (kb_Data[5] & kb_Tan) enemyStack[1] += num;
	// else if (kb_Data[5] & kb_RParen) enemyStack[2] += num;
	// else if (kb_Data[6] & kb_Clear) enemyStack[0] -= num;
	// else if (kb_Data[6] & kb_Power) enemyStack[1] -= num;
	// else if (kb_Data[6] & kb_Div) enemyStack[2] -= num;

	// //There's probably a better way to do this, like a premade method, but I couldn't find one. Essentially checks if the if/else block above had anything true by comparing if any array was modified
	// for (i = 0; i < 3; i++)
	// {
	// 	if (towers[i] == oldTowers[i] || allianceStack[i] == oldAllianceStack[i] || enemyStack[i] == oldEnemyStack[i])
	// 	{
	// 		updates[2] = true;
	// 	}
	// }

	// switch (kb_Data[2])
	// {
	// case kb_Log:
	// 	*a = AUTON_WIN;
	// 	updates[3] = true;
	// 	break;
	// case kb_Ln:
	// 	*a = AUTON_LOSS;
	// 	updates[3] = true;
	// 	break;
	// case kb_Sto:
	// 	*a = AUTON_TIE;
	// 	updates[3] = true;
	// 	break;
	// }

	typedef struct {
		kb_key_t key;
		int8_t multiplier;
		//uint8_t * ptr;
	} keyBind;

	uint8_t inc = 1;
	uint8_t oldTowers[3], oldAllianceStack[3], oldEnemyStack[3];

	uint16_t incrementors[10] = {
						   0, 0,
						   1026,	// 2
						   1282,	// 3
						   772,		// 4
						   1028,	// 5
						   1284,	// 6
						   776,		// 7
						   1040,	// 8
						   1288		// 9
						   };

	keyBind keys[18] = {
			{kb_Key2nd, 1},// towers},				// 2nd
			{kb_KeyAlpha, -1},// towers},				// Alpha
			{kb_KeyMode, 1},// *(towers + 1)},			// Mode
			{kb_KeyGraphVar, -1},// *(towers + 1)},		// X, T, Ѳ, n
			{kb_KeyDel, 1},// *(towers + 2)},			// Del
			{kb_KeyStat, -1},// *(towers + 2)},		// Stat
			{kb_KeyMath, 1},// allianceStack},		// Math
			{kb_KeyRecip, 1},// *(allianceStack + 1)},	// Reciprocal
			{kb_KeySquare, 1},// *(allianceStack + 2)},	// Square
			{kb_KeyApps, -1},// allianceStack},		// Apps
			{kb_KeySin, -1},// *(allianceStack + 1)},	// Sin
			{kb_KeyComma, -1},// *(allianceStack + 2)},	// Comma
			{kb_KeyVars, 1},// enemyStack},			// Vars
			{kb_KeyTan, 1},// *(enemyStack + 1)},	// Tan
			{kb_KeyRParen, 1},// *(enemyStack + 2)},	// RParen
			{kb_KeyClear, -1},// enemyStack},			// Clear
			{kb_KeyPower, -1},// *(enemyStack + 1)},	// Power
			{kb_KeyDiv, -1}// *(enemyStack + 2)}	// Divide
	};

	uint8_t * keyPtrs[] = {
		towers,
		towers,
		*(towers + 1),
		*(towers + 1),
		*(towers + 2),
		*(towers + 2),
		allianceStack,
		*(allianceStack + 1),
		*(allianceStack + 2),
		*allianceStack,
		*(allianceStack + 1),
		*(allianceStack + 2),
		enemyStack,
		*(enemyStack + 1),
		*(enemyStack + 2),
		enemyStack,
		*(enemyStack + 1),
		*(enemyStack + 2)
	};

	uint8_t iter;
	for (iter = 2; iter <= 10; iter++) {
		if (kb_IsDown(incrementors[iter])) {
			inc = iter;
			break;
		}
	}
	
	memcpy(oldTowers, towers, 24);
	memcpy(oldAllianceStack, allianceStack, 24);
	memcpy(oldEnemyStack, enemyStack, 24);
	
	if(kb_Data[1] & kb_Yequ) {
		updates[0] = true;
		*col = *col == TEAM_COLOR_BLUE ? TEAM_COLOR_RED : TEAM_COLOR_BLUE;
	} else if(kb_Data[1] & kb_Trace)
		updates[1] = true;

	for (iter = 0; iter <=18; iter++) {
		if (kb_IsDown(keys[iter].key)) {
			//*keys[iter].ptr = *keys[iter].ptr + (inc * keys[iter].multiplier);
		}
	}
	
	for (iter = 0; iter < 3; iter++) {
		if (towers[iter] == oldTowers[iter] ||
			allianceStack[iter] == oldAllianceStack[iter] ||
			enemyStack[iter] == oldEnemyStack[iter]) 
			{
				updates[2] = true;
			}
	}

	switch (kb_Data[2]) {
	case kb_Log:
		*a = AUTON_WIN;
		updates[3] = true;
		break;
	case kb_Ln:
		*a = AUTON_LOSS;
		updates[3] = true;
		break;
	case kb_Sto:
		*a = AUTON_TIE;
		updates[3] = true;
		break;
	}
}


uint8_t calcScore(uint8_t towers[], uint8_t stack[], auton a, team t) {
	uint8_t count = 0;

	uint8_t i = 0;
	for (i = 0; i < 3; i++) {
		count += (towers[i] + 1) * stack[i];
	}

	count += (a == t ? 6 : a == AUTON_TIE ? 3 : 0);
	// count += (t == TEAM_ALLIANCE ? 1 : -1) * (-4.5 * pow(a, 2) + 7.5 * a) + 3;

	return count;
}

void calcFuture(uint8_t future[2][3][3], uint8_t towers[], uint8_t stack[], auton a) {
	uint8_t tempTower[3], tempAllianceStack[3];

	uint8_t x, i;
	for (x = 0; x < 2; x++) {
		for (i = 0; i < 3; i++) {
			memcpy(tempTower, towers, 3 * sizeof(uint8_t));
			memcpy(tempAllianceStack, stack, 3 * sizeof(uint8_t));

			tempTower[i] += 1;
			future[x][i][0] = calcScore(tempTower, tempAllianceStack, a, x);

			tempTower[i] -= 2;
			future[x][i][1] = calcScore(tempTower, tempAllianceStack, a, x);

			tempAllianceStack[i] += 1;
			future[x][i][2] = calcScore(tempTower, tempAllianceStack, a, x);
		}
	}
}
