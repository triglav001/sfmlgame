/*
 * BattleFormula.h
 *
 *  Created on: Dec 29, 2020
 *      Author: Domen
 */

#ifndef BATTLE_BATTLEFORMULA_H_
#define BATTLE_BATTLEFORMULA_H_

struct BattleMultiplier {
	double m_mhp = 0.0f;
	double m_atk = 0.0f;
	double m_def = 0.0f;
	double m_mat = 0.0f;
	double m_mdf = 0.0f;
};

class BattleFormula {
public:
	int damage_base;
	bool use_multipliers = false;
	BattleMultiplier mul_a;
	BattleMultiplier mul_b;
};

#endif /* BATTLE_BATTLEFORMULA_H_ */
