/*
 * FileReader.h
 *
 *  Created on: Mar 21, 2018
 *      Author: muhammed
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <bits/stdc++.h>
using namespace std;

class File_Reader {
public:
	File_Reader();
	virtual ~File_Reader();
	bool read_file(string path);
	string src_code();
	bool write_file(string file, string path);
protected:

private:

	ifstream is;
	ofstream os;

};

#endif /* FILEREADER_H_ */
