#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<sstream>
#include<ctime>
#include <iomanip>
#include <chrono>
#include <fstream>

using namespace std;
bool check_y_n();              // �����飨y/n��
int check_opt(int, int);       // �����飨��Χ�����֣�
float check_float(string,bool& );     // �����飨�Ƿ񹹳ɸ�������
int check_int(string,bool& );         // �����飨�Ƿ񹹳�������
void Stringsplit(string str, const char split, vector<string>& res); // �ָ��ַ���
bool StringContains(string str1, string str2);                             // �ж��Ƿ����
string gettime(int);                                                       // ��ȡʱ��
void WritingCommands(string str1);                                         // ������д���ļ�
void change_id(string&, int&, int);