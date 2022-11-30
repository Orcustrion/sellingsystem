#include "help.h"

bool check_y_n()
{
	char y_n;
	cin >> y_n;
	while ((!cin) || (y_n != 'y' && y_n != 'n'))
	{
		cout << "输入有误 请重新输入！[y/n]";
		cin.clear();
		cin.ignore();
		cin >> y_n;
	}
	if (y_n == 'y')
		return true;
	else
		return false;
}
int check_opt(int opt_min, int opt_max)
{
	int opt;
	cin >> opt;
	while ((!cin) || opt < opt_min || opt> opt_max)
	{
		cout << "输入有误 请重新输入！" << endl << endl;
		cout << "请输入对应数字以继续：";
		cin.clear();
		cin.ignore();
		cin >> opt;
	}
	return opt;
}
float check_float(string s,bool& legal)
{
	int point = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '.')
			point += 1;
		else if (s[i] <= '9' && s[i] >= '0')
			;
		else
		{
			legal = 0;
			break;
		}
		if (point > 1)
		{
			legal = 0;
			break;
		}
	}
	if (legal == 1)
		return atof(s.c_str());
	else
		return -1;
}
int check_int(string s, bool& legal)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] <= '9' && s[i] >= '0')
			;
		else
		{
			legal = 0;
			break;
		}
	}
	if (legal == 1)
		return atoi(s.c_str());
	else
		return -1;
}
void Stringsplit(string str, const const char split, vector<string>& res)
{
	istringstream iss(str);	// 输入流
	string token;			// 接收缓冲区
	while (getline(iss, token, split))	// 以split为分隔符
		res.push_back(token);
}
bool StringContains(string str1, string str2)  // str1 主
{
	int n = str1.length();
	int m = str2.length();
	if (n < m)
		return false;
	else
	{
		int* next = new int[m];
		int q0, k0;
		next[0] = 0;
		for (k0 = 0, q0 = 1; q0 < m; ++q0)
		{
			while (k0 > 0 && str2[k0] != str2[q0])
			{
				k0 = next[k0];
			}
			if (str2[k0] == str2[q0])
			{
				++k0;
			}
			next[q0] = k0;
		}

		for (int i = 0, q = 0; i < n; ++i)
		{
			while (q > 0 && str2[q] != str1[i])
			{
				q = next[q];
			}
			if (str2[q] == str1[i])
			{
				++q;
			}
			if (q == m)
			{
				return true;
				q = 0;
			}
		}
	}
	return false;
}
string gettime(int kind)
{
	// 生成时间
	auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
	stringstream ss;
	if(kind == 1) 
		ss << put_time(localtime(&t), "%F %T");
	else
		ss << put_time(localtime(&t), "%F ");
	return ss.str();
}
void WritingCommands(string str1)
{
	string command = gettime(1)+ " " + str1;
	// 写入文件
	ofstream fout("D:/data/commands.txt",ios::app|ios::out);
	if (!fout.is_open())
		cout << "no file commands.txt!";
	else
	{
		fout << command << endl;
		fout.close();
	}
}
void change_id(string& id, int& id_to_use, int kind)
{
	if (kind == 1)  // string->int
	{
		string t_id = id;
		t_id.erase(t_id.begin());
		id_to_use = atoi(t_id.c_str());
	}
	if (kind == 2)  // int->string
	{
		stringstream ss;
		ss << setw(3) << setfill('0') << id_to_use;
		id+=ss.str();        
	}
}