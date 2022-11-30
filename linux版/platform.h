#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<sstream>
#include<ctime>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <unistd.h>
using namespace std;


bool check_y_n();              // 输入检查（y/n）
int check_opt(int, int);       // 输入检查（范围内数字）
float check_float(string, bool&);     // 输入检查（是否构成浮点数）
int check_int(string, bool&);         // 输入检查（是否构成整数）
void Stringsplit(string str, const char split, vector<string>& res); // 分割字符串
bool StringContains(string str1, string str2);                             // 判断是否包含
string gettime(int);                                                       // 获取时间
void WritingCommands(string str1);                                         // 将命令写入文件
void change_id(string&, int&, int);



struct Commodity {
	string cid;    // 商品id，M开头
	string cname;   // 名称
	float price;    // 价格
	int number;     // 数量
	string description;  // 描述
	string sellerid;  // 卖家id
	string addedDate;         // 上架时间
	bool state;     // 商品状态
	void display(int authority)
	{
		cout << setiosflags(ios::left) << setw(9) << cid << setw(8) << cname << setw(10);
		if (authority != 2)
			cout << sellerid << setw(9);
		cout << fixed << setprecision(1) << price << setw(9) << number << setw(15) << addedDate << setw(8);
		if (authority != 3)
		{
			if (state)
				cout << "active" << "   ";
			else
				cout << "inactive" << "   ";
		}
		cout << endl;
	}; // 输出函数
};

struct Order {
	string oid;    // 订单id，T开头
	string cid;    // 商品id，M开头
	float price;    // 成交单价
	int number;     // 交易数量
	string date;    // 交易时间
	string sellerid;  // 卖家id
	string buyerid;   // 买家id
	void display(int authority)
	{
		cout << setiosflags(ios::left) << setw(9) << oid << setw(9) << cid
			<< setw(11) << fixed << setprecision(1) << price << setw(8) << number << setw(13) << date << setw(4);
		if (authority != 2)
			cout << sellerid << "     ";
		if (authority != 3)
			cout << buyerid << "     ";
		cout << endl;
	}; // 输出函数
};

class Calculator
{
private:
	vector<float> num;
	vector<char> sym;
	int state;
public:
	bool check_s(string);
	float calculation(string);     // 主计算函数
	float operatios(vector<float>, int num_c, char c);

};

class Platform;
class User
{
private:
	string uid;                 //用户ID
	string password;            //密码
	string phonenumber;         //联系方式
	string address;             //地址
	float balance;              //钱包余额
	bool state;                 //用户状态  1正常 0封禁
	vector<string> cart;        //购物车
	friend class Platform;

public:
	string uname;             //用户名
	User();
	User(string, string, int);    //含参构造函数
	User(string);       //只含uid的构造函数

	void user_display();      //显示函数
	string get_uid() { return uid; } // 返回uid

	string user_control(int);             // 用户修改信息控制
	string user_update(int);               // 用户修改信息命令
};
class Seller : public User
{
public:
	Seller(string);
	string seller_control(int);         // 卖家界面生成命令
	string seller_insert_commodity();    // 发布商品
	string seller_update_commodity(int); // 修改/下架商品

	friend class Platform;
};
class Buyer : public User
{

public:
	Buyer(string);
	string buyer_control(int);
	string buyer_select_commodity(int);
	string buyer_insert_order();

	friend class Platform;
};

class Administrator
{
private:
	string adname;      // 管理员名
	string password;    // 管理员密码

	friend class Platform;
public:
	string admin_control(int);          // 管理员界面生成命令
	string admin_select_commodity(int);  // 查询/搜索商品
	string admin_change_state(int);     // 封禁用户/下架商品


};

class Platform
{
private:
	Administrator admin;            // 唯一管理员
	User temp_user;                 // 当前登录用户
	Calculator cal;                 // 计算器接口
	string message;                 // 指令

	vector<Commodity> commodities;  // 商品容器
	vector<Order>     orders;       // 订单容器
	vector<User>      users;        // 用户容器

	int to_use_uid;                 // 准备的id
	int to_use_cid;
	int to_use_oid;

	string file_path;               // 读取文件路径
	vector<string> display_string;  // 常用输出字符串集

public:
	Platform();

	// 主要显示函数
	void start_display();          // 开始界面展示
	void login_display();          // 登录界面展示
	void calculator_display();     // 计算器界面展示 
	void admin_display();          // 管理员界面展示
	void user_display();           // 用户界面展示
	void seller_display();         // 卖家界面展示
	void buyer_display();          // 买家界面展示
	void cart_display();           // 购物车界面展示
	void user_info_display();      // 用户信息界面展示

	// 登录界面函数
	void login_admin();
	void login_user();
	void signin_user();

	// 控制函数
	bool analyze_message(int);        // 解析命令 更改数据
	bool analyze_message_select(string, vector<string>, int);     // 分析选择语句
	bool analyze_message_insert(string, vector<string>, int);     // 分析插入语句
	bool analyze_message_update(string, vector<string>, int);     // 分析更新语句

	void write_document(int);         // 写入文件

};