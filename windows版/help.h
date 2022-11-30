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
bool check_y_n();              // 输入检查（y/n）
int check_opt(int, int);       // 输入检查（范围内数字）
float check_float(string,bool& );     // 输入检查（是否构成浮点数）
int check_int(string,bool& );         // 输入检查（是否构成整数）
void Stringsplit(string str, const char split, vector<string>& res); // 分割字符串
bool StringContains(string str1, string str2);                             // 判断是否包含
string gettime(int);                                                       // 获取时间
void WritingCommands(string str1);                                         // 将命令写入文件
void change_id(string&, int&, int);