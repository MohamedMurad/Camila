/*
 * Parser.cpp
 *
 *  Created on: 13/3/2018
 *      Author: Murad
 */

#include "Rules.h"

#include <iostream>
#include <string>
#include <vector>

#include "RulesParser.h"

using namespace std;

Rules rules;

Rules RulesParser::parse_lines(vector<string> lines) {
	while (!lines.empty()) {
		unsigned int idx = 0;
		string line = lines.back();
		lines.pop_back();
		if (line[0] == '[') {	//keywords
			rules.keywords.push_back(parse(line, 0));
			rules.order.push_back(0);
		} else if (line[0] == '{') {	//Punctuation
			rules.punctuations.push_back(parse(line, 1));
			rules.order.push_back(1);
		} else {
			while (line[idx] != ':' && line[idx] != '=') {
				idx++;
			}
			if (line[idx] == '=') {	//definitions
				rules.definitions.push_back(parse(line, 2));
				rules.order.push_back(2);
			} else if (line[idx] == ':') {	//expressions
				rules.expressions.push_back(parse(line, 3));
				rules.order.push_back(3);
			}
		}
	}
	return rules;
}

vector<string> RulesParser::parse(string line, int priorities) {
	vector<string> temp;
	switch (priorities) {
	case 0:
		temp = keywords_parser(line);
		break;
	case 1:
		temp = Punctuation_parser(line);
		break;
	case 2:
		temp = definitions_parser(line);
		break;
	case 3:
		temp = expressions_parser(line);
		break;
	default:
		break;
	}
	return temp;
}
vector<string> RulesParser::keywords_parser(string line) {
	vector<string> tokens;
	for (unsigned int i = 1; i < line.length() - 1; i++) {
		string token;
		while (i < line.length() - 1 && line[i] != ' ' && line[i] != '\\') {
			token.append(line.begin() + i, line.begin() + i + 1);
			i++;
		}
		if (!token.empty()) {
			tokens.push_back(token);
		}
		token.clear();
	}
	return tokens;
}

vector<string> RulesParser::Punctuation_parser(string line) {
	vector<string> tokens;
	for (unsigned int i = 1; i < line.length() - 1; i++) {
		string token;
		while (i < line.length() - 1 && line[i] != ' ') {
			if (line[i] == '\\')
				continue;
			token.append(line.begin() + i, line.begin() + i + 1);
			i++;
		}
		if (!token.empty()) {
			tokens.push_back(token);
		}
		token.clear();
	}
	return tokens;
}

vector<string> RulesParser::definitions_parser(string line) {
	return expr_def_parser(line);
}

vector<string> RulesParser::expressions_parser(string line) {
	return expr_def_parser(line);
}

bool reserved_symbol(string line, unsigned int i) {
	return line[i] == '|' || line[i] == '(' || line[i] == ')' || line[i] == '+'
			|| line[i] == '*' || line[i] == '-' || line[i] == ':'
			|| line[i] == '=' || line[i] == '\\' || line[i] == '.';
}

bool is_exponent(string line, unsigned int i) {
	return (line[i] == 'E' || line[i] == 'e')
			&& (i - 1 >= 0 && line[i - 1] == ' ')
			&& (i + 1 < line.size() && line[i + 1] == ' ');
}

vector<string> RulesParser::expr_def_parser(string line) {
	vector<string> tokens;
	string token;
	for (unsigned int i = 0; i < line.length(); i++) {
		if (line[i] == ' '){
			if (!token.empty()) {
				tokens.push_back(token);
				token.clear();
			}
			continue;
		}
		if (reserved_symbol(line, i) || is_exponent(line, i)) {
			if(line[i] == '\\'){
				i++;
				token.append(line.begin() + i, line.begin() + i + 1);
				continue;
			}
			if (!token.empty()) {
				tokens.push_back(token);
				token.clear();
			}
			string sym(line.begin() + i, line.begin() + i + 1);
			tokens.push_back(sym);
		} else {
			token.append(line.begin() + i, line.begin() + i + 1);
		}
	}
	if (!token.empty()) {
		tokens.push_back(token);
		token.clear();
	}
	return tokens;
}