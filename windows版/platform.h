#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "user.h"
#include "calculator.h"
#include "commodity.h"
#include "help.h"
using namespace std;
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
	bool analyze_message(int );        // 解析命令 更改数据
	bool analyze_message_select(string , vector<string> ,int);     // 分析选择语句
	bool analyze_message_insert(string , vector<string> ,int);     // 分析插入语句
	bool analyze_message_update(string , vector<string> ,int);     // 分析更新语句

	void write_document(int );         // 写入文件

};
