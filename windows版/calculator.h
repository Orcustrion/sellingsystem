#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
class Calculator
{
private:
	vector<float> num;
	vector<char> sym;
	int state;
public:
	bool check_s(string );
	float calculation(string );     // �����㺯��
	float operatios(vector<float>, int num_c, char c);

};

