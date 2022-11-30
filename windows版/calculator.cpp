#include "calculator.h"
float Calculator::operatios(vector<float> num, int num_c, char c)
{
	float res;
	switch (c)
	{
	case '+':
		res = num[num_c - 1] + num[num_c - 2];
		break;
	case '-':
		res = num[num_c - 2] - num[num_c - 1];
		break;
	case '*':
		res = num[num_c - 1] * num[num_c - 2];
		break;
	case '/':
		if (num[num_c - 1] == 0)
		{
			state = 5;
			res = (1 << 31) - 1;
		}
		res = num[num_c - 2] / num[num_c - 1];
		break;
	default:
		res = num[num_c - 1];
		break;
	}
	return res;
}
bool Calculator::check_s(string s)
{
	int counter = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
			counter++;
		else if (s[i] == ')')
			counter--;
		else if (s[i] <= '9' && s[i] >= '0')
			;
		else if (s[i] == ' ')
			s.erase(i);
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '.')
			;
		else
		{
			state = 1;
			break;
		}
	}
	if (counter != 0)
		state = 4;
	return (state == 0);
}
float Calculator::calculation(string s)
{
	// state: 0成功  1非法字符  2数字格式错误 3操作符误用 4括号不匹配 5除数为0
	num.clear(); sym.clear();
	int num_c = 0, sym_c = 0; //栈指针
	state = 0;    // 状态标记
	if (check_s(s))  // 无非法字符、括号不匹配	
	{                                                                                                                                                                                                     
		s += "e"; // 结束符
		int length = s.length();
		bool neg = 0;
		int i = 0;
		string number; 
		int n = 0;  
		for (int i = 0; i < length; i++)
		{
			if (s[i] <= '9' && s[i] >= '0')
			{
				if (n == 0)
					n = 1;
				else if (n == 2)
					n = 3;
				else if (n == 3)
				{
					state = 2;
					break;
				}
				number += s[i];
			}
			else if (s[i] == '.')
			{
				if (n == 1)
				{
					n = 2;
					number += s[i];
				}
				else
				{
					state = 2;
					break;
				}
			}
			else
			{
				if (n != 0)
				{
					num.push_back(atof(number.c_str()));
					if (neg == 1)
					{
						num[num_c] = -num[num_c];
						neg = 0;
					}
					num_c++;
					number = "";
					n = 0;
				}
				if (s[i] == '(')
				{
					sym.push_back('(');
					sym_c++;
				}
				else if (s[i] == ')')
				{
					if (sym_c > 0)
					{
						while (sym[sym_c - 1] != '(' && sym_c > 0)
						{
							if(num_c>1)
								num[num_c - 2] = operatios(num, num_c, sym[sym_c - 1]);
							else
							{
								state = 3;
								break;
							}
							num.pop_back();
							num_c--;
							sym.pop_back();
							sym_c--;
							if (sym_c == 0)
								break;
						}
					}
					sym.pop_back();
					sym_c--;
				}
				else if (s[i] == '+' || s[i] == '-')
				{
					if (i > 0 )
					{
						if (s[i - 1] == '(' && s[i] == '-')
							neg = 1;
						else
						{
							if (sym_c > 0)
							{
								while (sym[sym_c - 1] != '(' && sym_c > 0)
								{
									if (num_c > 1)
										num[num_c - 2] = operatios(num, num_c, sym[sym_c - 1]);
									else
									{
										state = 3;
										break;
									}
									num.pop_back();
									num_c--;
									sym.pop_back();
									sym_c--;
									if (sym_c == 0)
										break;
								}
							}
							sym.push_back(s[i]);
							sym_c++;
						}
					}
					else
					{
						state = 3;
						break;
					}

				}
				else if (s[i] == '*' || s[i] == '/')
				{
					if (sym_c > 0)
					{
						while (sym[sym_c - 1] != '(' && sym[sym_c - 1] != '+' && sym[sym_c - 1] != '-' && sym_c > 0)
						{
							if (num_c > 1)
								num[num_c - 2] = operatios(num, num_c, sym[sym_c - 1]);
							else
							{
								state = 3;
								break;
							}
							num.pop_back();
							num_c--;
							sym.pop_back();
							sym_c--;
							if (sym_c == 0)
								break;
						}
					}
					sym.push_back(s[i]);
					sym_c++;
				}
			}
		}

		while (sym_c > 0 && state ==0)
		{
			if (num_c > 1)
				num[num_c - 2] = operatios(num, num_c, sym[sym_c - 1]);
			else
			{
				state = 3;
				break;
			}
			num.pop_back();
			num_c--;
			sym.pop_back();
			sym_c--;
			if (sym_c == 0)
				break;
		}
	}
	// state: 0成功  1非法字符  2数字格式错误 3操作符误用 4括号不匹配 5除数为0
	if (state == 0)
	{
		cout << round(num[0]*10)/10;
		return num[0];
	}
	else
	{
		switch (state)
		{
		case 1:
			cout << "非法字符" << endl;
			break;
		case 2:
			cout << "数字格式错误" << endl;
			break;
		case 3:
			cout << "操作符误用" << endl;
			break;
		case 4:
			cout << "括号不匹配" << endl;
			break;
		case 5:
			cout << "除数为0" << endl;
			break;
		default:
			break;
		}
		return -1;
	}
}
