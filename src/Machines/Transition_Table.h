/*
 * Transition_Table.h
 *
 *  Created on: Mar 14, 2018
 *      Author: muhammed
 */

#ifndef TRANSITION_TABLE_H_
#define TRANSITION_TABLE_H_

#include <bits/stdc++.h>
#include "State.h"

using namespace std;

class Transition_Table{

public:
	Transition_Table(unordered_map<int,unordered_map<char,int>> table);
	State* get_next_state(int current,char input);
	State* get_start_state();
	State* current_state();
	void add_state(State* s);
	void print_table();

protected:

private:

	unordered_map<int,unordered_map<char,int>> table;
	vector<State*> state_ids;
	int current_id;

};


#endif /* TRANSITION_TABLE_H_ */