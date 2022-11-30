#include<iostream>
#include "platform.h"
#include <Windows.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;
Platform::Platform()  // 默认构造函数
{
	// 初始化管理员
	admin.adname="admin";
	admin.password = "123456";

	// 文件路径
	file_path="D:/data";

	// 暂用ID
	to_use_cid = 0;
	to_use_oid = 0;
	to_use_uid = 0;

	display_string.push_back("====================================================================");
	display_string.push_back("商品ID   名称    卖家ID    价格     数量     上架时间       状态");
	display_string.push_back("商品ID   名称    价格      数量      上架时间       状态");
	display_string.push_back("商品ID   名称    卖家ID    价格     数量     上架时间");
	display_string.push_back("订单ID   商品ID   交易单价   数量    交易时间     卖家ID   买家ID");
	display_string.push_back("订单ID   商品ID   交易单价   数量    交易时间     买家ID");
	display_string.push_back("订单ID   商品ID   交易单价   数量    交易时间     卖家ID");
	display_string.push_back("用户ID   用户名   联系方式     地址            余额      用户状态");

	display_string.push_back("userID, username, password, phoneNumber, address, balance, userState");
	display_string.push_back("commodityID, commodityName, price, number, description, sellerID, addedDate, state");
	display_string.push_back("orderID, commodityID, unitPrice, number, date, sellerID, buyerID");


}
void Platform::start_display()
{
	// 开始图像
	system("cls");
	cout << "     ============================================================    "  << endl;
	cout << "                     欢迎使用冬奥纪念品交易平台     "                  << endl;
	cout << "     ============================================================    " << endl << endl << endl;

	// 读取商品文件
	ifstream in1("D:/data/commodity.txt");
	if (!in1.is_open())
	{
		cout << "no file commodity.txt"<<endl; 
	}
	else
	{	
		cout << "成功读取 commodity.txt" << endl;
		string linestr;
		int size = 0;
		string maxm="M000";
		while (getline(in1, linestr,'\n'))
		{
			if (size != 0)   // 忽略第一行
			{
				vector<string>token;
				Stringsplit(linestr, ',', token);
				Commodity c;
				c.cid = token[0]; c.cname = token[1]; c.price = atof(token[2].c_str());
				c.number = atoi(token[3].c_str()); c.description = token[4];
				c.sellerid = token[5]; c.addedDate = token[6];
				c.state = (token[7]== "active");
				commodities.push_back(c);

				if (token[0] > maxm)
					maxm = token[0];
			}
			size += 1;
		}
		change_id(maxm, to_use_cid, 1);
	}

	// 读取用户文件
	ifstream in2("D:/data/user.txt");
	if (!in2.is_open())
	{
		cout << "no file user.txt"<<endl;
	}
	else
	{
		cout << "成功读取 user.txt" << endl;
		string linestr;		
		int size = 0;
		string maxu = "U000";
		while (getline(in2, linestr))
		{
			if (size != 0)   // 忽略第一行
			{
				vector<string>token;
				Stringsplit(linestr, ',', token);
				User u;
				u.uid = token[0]; u.uname = token[1]; u.password = token[2];
				u.phonenumber = token[3]; u.address = token[4];
				u.balance = atof(token[5].c_str());
				u.state = (token[6] == "active");
				users.push_back(u);
				if (token[0] > maxu)
					maxu = token[0];
			}
			size += 1;
		}
		change_id(maxu, to_use_uid, 1);
	}

	// 读取订单文件
	ifstream in3("D:/data/order.txt");
	if (!in3.is_open())
	{
		cout << "no file order.txt"<<endl;
		// 文件不存在  创建订单文件
		ofstream out3("D:/data/order.txt", ios::out);
		out3 << display_string[10] << endl;
	}
	else
	{
		cout << "成功读取 order.txt" << endl;
		string linestr;
		int size = 0;
		string maxo = "T000";
		while (getline(in3, linestr))
		{
			if (size != 0)   // 忽略第一行
			{
				vector<string>token;
				Stringsplit(linestr, ',', token);
				Order o;
				o.oid = token[0]; o.cid = token[1]; o.price = atof(token[2].c_str()); o.number = atoi(token[3].c_str()); 
				o.date = token[4]; o.sellerid = token[5]; o.buyerid = token[6];
				orders.push_back(o);
				if (maxo < token[0])
					maxo = token[0];
			}
			size += 1;
		}
		change_id(maxo, to_use_oid, 1);
	}

	// 读取购物车文件
	ifstream in4("D:/data/cart.txt");
	if (!in4.is_open())
	{
		cout << "no file cart.txt" << endl;
	}
	else
	{
		cout << "成功读取 cart.txt" << endl;
		string linestr;
		while (getline(in4, linestr, '\n'))
		{
			vector<string>token;
			Stringsplit(linestr, ',', token);
			string uid = token[0];
			for (auto u : users)
			{
				if (u.uid == uid)
				{
					for (int i = 1; i < token.size(); i++)
						u.cart.push_back(token[i]);
				}
			}
		}
	}

	system("pause");
	login_display();
}
void Platform::login_display()
{
	system("cls");
	cout << "     =====================================================================     "<<endl;
	cout << "     1、管理员登录   2、用户登录   3、用户注册   4、辅助功能   5、退出程序     "<<endl;
	cout << "     =====================================================================     "<<endl<<endl<<endl;

	cout << "请输入对应数字以继续：";
	int opt=check_opt(1,5);
	switch (opt)
	{
	case 1:     // 管理员登录
		login_admin();
		break;
	case 2:    // 用户登录
		login_user();
		break;
	case 3:    // 用户注册 
		signin_user();
		break;
	case 4:    // 辅助功能
		calculator_display();  // 计算器
		break;
	case 5:    // 退出
		cout << "程序运行结束" << endl;
		break;
	default:
		break;
	}
		
}
void Platform::login_admin()
{
	cout << endl;
	cout << "请输入管理员名称：";
	string adname;
	cin >> adname;
	int success = 0;
	if (adname == admin.adname)
	{
		
		int trytimes = 0;
		string password;
		while (trytimes < 3)
		{
			cout << "请输入密码：";
			cin >> password;
			if (password == admin.password)
			{
				cout << "登录成功！";
				success = 1;
				Sleep(500);
				admin_display();
				break;
			}
			else
			{
				trytimes += 1;
				if (trytimes != 3)
					cout << "密码错误，还有" << 3 - trytimes << "次机会"<<endl;
			}
			
		}
		if (success == 0)
		{
			cout << "密码输入错误！" << endl;
			Sleep(500);
			login_display();
		}
	}
	else
	{
		cout << "名称输入错误!" << endl;
		Sleep(500);
		login_display();
	}
}
void Platform::login_user()
{
	cin.ignore();
	cout << endl;
	label:cout << "请输入用户名：";
	string uname;
	getline(cin, uname);
	int success = 0;
	for (int i = 0; i < users.size(); i++)
	{
		if (uname == users[i].uname)
		{
			int trytimes = 0;
			string password;
			while (trytimes < 3)
			{
				cout << "请输入密码：";
				getline(cin, password);
				if (password == users[i].password)
				{
					if (users[i].state == 1)
					{
						cout << "登录成功！";
						success = 1;
						temp_user = users[i];
						Sleep(500);
						user_display();
						break;
					}
					else
					{
						cout << "该账号已封禁";
						Sleep(500);
						login_display();
					}
				}
				else
				{
					success = -1;
					trytimes += 1;
					if (trytimes != 3)
						cout << "密码错误，还有" << 3 - trytimes << "次机会" << endl;
				}

			}
			if (success == -1)
			{
				cout << "密码输入错误！" << endl;
				Sleep(500);
				login_display();
			}
		}
	}
	if(success==0)
	{
		cout << "用户名输入错误!" << endl;
		goto label;
	}
}
void Platform::signin_user()
{
	cin.ignore();
	string uname;
	while (1)
	{
		cout << "请输入用户名:";
		getline(cin, uname);
		int length = uname.size();
		int success = 1;
		if (length > 10)
		{
			success = 0;
			cout << "名称过长，请重新输入"<<endl;
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				
				if (uname[i] <= 'z' && uname[i]>='a')     // 字母
					;
				else if (uname[i] <= 'Z' && uname[i]>='A')
					;
				else
				{
					cout << "用户名中含非法字符"<<endl;
					success = 0;
					break;
				}
			}	
		}
		for (int i = 0; i < users.size(); i++)
			if (users[i].uname == uname)
			{
				cout << "与已有用户重名"<<endl;
				success = 0;
				break;
			}
		if (success)
			break;
	}
	string password;
	while (1)
	{
		cout << "请输入密码:";
		getline(cin, password);
		int length = password.size();
		int success = 1;
		if (length > 20)
		{
			success = 0;
			cout << "密码过长，请重新输入" << endl;
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				if (password[i] <= 'z' && password[i]>='a')  // 字母
					;
				else if (password[i] <= '9' && password[i]>='0')  // 数字
					;
				else
				{
					success = 0;
					cout << "密码中含非法字符"<<endl;
					break;
				}
			}
		}
		if (success)
			break;
	}

	// 分配uid & 写入文件
	to_use_uid += 1;
	User new_user(uname,password,to_use_uid);
	users.push_back(new_user);
	cout << "注册成功!" << endl;
	write_document(1);
	Sleep(800);
	login_display();
}
void Platform::calculator_display()
{
	cout << "======================================" << endl;
	cout << "               计算器使用            " << endl;
	cout << "======================================" << endl;
	cin.ignore();
	while (1)
	{
		cout << "请输入算式: (输入exit结束)"<<endl;
		string s;
		getline(cin, s);
		if (s == "exit")
			break;
		cal.calculation(s);
		cout << endl;

	}
	login_display();
}
void Platform::admin_display()
{
	int sign = 0;
	while (!sign)
	{
		system("cls");
		cout << "     ===============================================================     " << endl;
		cout << "     |  1、查看商品  2、搜索商品   3、下架/上架商品   4、查看订单   | "     << endl;
		cout << "     |         5、查看用户  6、封禁/解封  7、注销                   |      " << endl;
		cout << "     ===============================================================     " << endl << endl << endl;

		cout << "请输入对应数字以继续：";
		int opt = check_opt(1, 7);
		if (opt == 7)
		{
			cout << "确认注销？ [y/n]";
			if (check_y_n())
			{
				cout << "注销成功！" << endl;
				Sleep(800);
				login_display();
				sign = 1;
			}
		}
		else
		{
			// 控制权移交
			message = admin.admin_control(opt);
			analyze_message(1);
			system("pause");
		}
	}
}
void Platform::user_display()
{
	int sign = 0;
	while (!sign)
	{
		system("cls");
		cout << "     ===========================================================     " << endl;
		cout << "       1、我是卖家  2、我是买家   3、个人信息管理   4、注销登录    " << endl;
		cout << "     ===========================================================     " << endl << endl << endl;

		cout << "请输入对应数字以继续：";
		int opt = check_opt(1, 4);
		switch (opt)
		{
		case 1:
			seller_display();
			break;
		case 2:
			buyer_display();
			break;
		case 3:
			user_info_display();
			break;
		case 4:
			cout << "确认注销？ [y/n] ";
			if (check_y_n())
			{
				cout << "注销成功！" << endl;
				Sleep(800);
				login_display();
				sign = 1;
			}
			break;
		}
	}
}
void Platform::seller_display()
{
	Seller temp_seller(temp_user.uid);
	int sign = 0;
	while (!sign)
	{
		system("cls");
		cout << "     ===========================================================     " << endl;
		cout << "     |  1、发布商品       2、查看发布商品   3、修改商品信息    | "     << endl;
		cout << "     |  4、下架/上架商品  5、查看历史订单   6、返回主界面      |      "<< endl;
		cout << "     ===========================================================     " << endl << endl << endl;

		cout << "请输入对应数字以继续：";
		int opt = check_opt(1, 6);
		if (opt == 6)
		{
			cout << "确认返回？ [y/n]";
			if (check_y_n())
			{
				Sleep(800);
				sign = 1;
			}
		}
		else
		{
			// 控制权移交
			message = temp_seller.seller_control(opt);
			analyze_message(2);
			system("pause");
		}
	}
}
void Platform::buyer_display()
{
	Buyer temp_buyer(temp_user.uid);
	int sign = 0;
	while (!sign)
	{
		system("cls");
		cout << "     ==============================================================     " << endl;
		cout << "     |  1、查看商品列表  2、购买商品       3、搜索商品信息        | "     << endl;
		cout << "     |  4、查看历史订单  5、查看商品详情   6、购物车              |      " << endl;
		cout << "     |                   7、返回用户主界面                        |      " << endl;
		cout << "     ==============================================================     " << endl << endl << endl;

		cout << "请输入对应数字以继续：";
		int opt = check_opt(1, 7);
		if (opt == 7)
		{
			cout << "确认返回？ [y/n]";
			if (check_y_n())
			{
				Sleep(800);
				sign = 1;
			}
		}
		else if (opt == 6)
			cart_display();
		else
		{
			// 控制权移交
			message = temp_buyer.buyer_control(opt);
			analyze_message(3);
			system("pause");
		}
	}
}
void Platform::cart_display()
{
	int sign = 0;
	while (!sign)
	{
		system("cls");
		cout << "     ==============================================================     " << endl;
		cout << "     |  1、查看购物车     2、加入商品      3、删除商品            | " << endl;
		cout << "     |  4、购买商品       5、退出                                 | " << endl;
		cout << "     ==============================================================     " << endl;

		cout << "请输入对应数字以继续：";
		int cart_size = temp_user.cart.size();
		int opt = check_opt(1, 5);
		if (opt == 5)
		{
			cout << "确认返回？ [y/n]";
			if (check_y_n())
			{
				Sleep(500);
				sign = 1;
			}
		}
		else if (opt == 1)
		{
			cout << display_string[0] << endl << "您的购物车包括：" << endl;
			for (int i = 0; i < cart_size; i++)
			{
				for (auto c : commodities)
					if (c.cid == temp_user.cart[i])
						cout <<i+1<<": "<< c.cid << "  " << c.cname << endl;
			}
		}
		else if(opt==2)
		{
			cout <<display_string[0]<<endl<< "请输入想要加入的商品id:" ;
			string str; cin >> str;
			int success = 0;
			for (auto &c : commodities)
				if (c.cid == str && c.state==1)
				{
					success = 1;
					cout << display_string[3]<<endl;
					c.display(3);
					cout << "请输入要加入的数量：";
					int add_num; cin >> add_num;
					if (add_num <= 0)
						cout << "非法输入，返回上一级" << endl;
					else if (add_num > c.number)
						cout << "超过商品数量上限" << endl;
					else if (add_num > (10 - cart_size))
						cout << "超过购物车数量上限" << endl;
					else
					{
						for (int i = 0; i < add_num; i++)
							temp_user.cart.push_back(c.cid);
						c.number -= add_num;
						cout << "加入成功！" << endl;
					}
				}
			if (!success)
				cout << "没有找到对应结果!" << endl;
		}
		else if (opt == 3)
		{
			cout << display_string[0] << endl << "请输入想要删除的商品在购物车内对应编号:";
			int del_num; cin >> del_num;
			if (del_num > 0 && del_num <= cart_size)
			{
				temp_user.cart.erase(temp_user.cart.begin()+del_num - 1);
				for (auto &c : commodities)
					if (c.cid == temp_user.cart[del_num - 1])
						c.number += 1;
				cout << "删除完成！" << endl;
			}
			else
				cout << "没有找到对应结果!" << endl;
		}
		else if (opt == 4)
		{
			cout << display_string[0] << endl << "请输入想要购买的商品在购物车内对应编号:";
			int buy_num; cin >> buy_num;
			if (buy_num > 0 && buy_num <= cart_size)
			{
				temp_user.cart.erase(temp_user.cart.begin() + buy_num - 1);
				message = "INSERT INTO order VALUES ";
				for (auto &c : commodities)
					if (c.cid == temp_user.cart[buy_num - 1])
					{
						message = message + c.cid + " " + "1";
						c.number += 1;
					}
				analyze_message(3);
			}
			else
				cout << "没有找到对应结果!" << endl;
		}
		for (int i = 0; i < users.size(); i++)
			if (users[i].uid == temp_user.uid)
			{
				users[i].cart.clear();
				for (int j = 0; j < temp_user.cart.size(); j++)
					users[j].cart.push_back(temp_user.cart[j]);
			}
		write_document(4);
		write_document(2);
		system("pause");
	}
	
}
void Platform::user_info_display()
{
	int sign = 0;
	while (!sign)
	{
		system("cls");
		cout << "     =================================================================     " << endl;
		cout << "       1、查看个人信息  2、修改个人信息  3、充值  4、返回用户主界面       " << endl;
		cout << "     =================================================================     " << endl << endl << endl;

		cout << "请输入对应数字以继续：";
		int opt = check_opt(0, 4);
		if (opt == 4)
		{
			cout << "确认返回？ [y/n]";
			if (check_y_n())
			{
				Sleep(800);
				sign = 1;
			}
		}
		else
		{
			// 控制权移交
			message = temp_user.user_control(opt);
			analyze_message(4);
			system("pause");
		}

	}
}
bool Platform::analyze_message(int identity)  // 1 admin;2 seller;3 buyer;4 user info 
{
	vector<string> token;
	string temp_message = message;
	Stringsplit(temp_message, ' ', token);
	// 选择语句
	if (token[0] == "SELECT")      
		return analyze_message_select(temp_message,token,identity);
	// 插入语句
	else if (token[0] == "INSERT") 
		return analyze_message_insert(temp_message,token,identity);
	// 更新语句
	else if (token[0] == "UPDATE") 
		return analyze_message_update(temp_message,token,identity);
	message = "";
	return false;
}
bool Platform::analyze_message_select(string message,vector<string> token,int identity)
{
	int length = token.size();
	bool success = 0;
	string command = message;
	cout << display_string[0] << endl;
	// 查询商品
	if (token[3] == "commodity")
	{	
		if (length > 4)  // 额外条件
		{
			if (token[5] == "commodityName")
			{
				if (identity == 3 || identity == 1)
					cout << display_string[1] << endl;
				else
					cout << display_string[3]<<endl;
				for (auto c : commodities)
					if (StringContains(c.cname,token[7]))
					{
						success = 1;
						if (identity == 3)
						{
							if (c.state == 1)
								c.display(identity);
						}
						else
							c.display(identity);
					}
			}
			else if (token[5] == "sellerid")
			{
				cout << display_string[2] << endl;
				command.erase(command.begin() + 23, command.end()); // 去掉末尾部分
				for(auto c :commodities)
					if (c.sellerid == token[7])
					{
						success = 1;
						
						c.display(identity);
					}
			}
			else if (token[5] == "commodityID")
			{
				for (auto c : commodities)
					if (c.cid == token[7])
					{
						success = 1;
						cout << "商品ID；" << c.cid << endl;
						cout << "商品名称；" << c.cname << endl;
						cout << "商品价格；" << fixed << setprecision(1) << c.price << endl;
						cout << "上架时间；" << c.addedDate << endl;
						cout << "商品详情；" << c.description << endl;
						cout << "卖家ID；" << c.sellerid << endl;
					}
			}
		}
		else
		{
			success = 1;
			if (identity == 1)
				cout << display_string[1] << endl;
			else if(identity == 3)
				cout << display_string[3] << endl;
			for (int i = 0; i < commodities.size(); i++)
			{
				if (identity == 3)
				{
					if (commodities[i].state == 1)
						commodities[i].display(identity);
				}
				else
					commodities[i].display(identity);
			}
		}
		
	}
	// 查询订单
	else if (token[3] == "order")
	{

		if (length > 4)  // 额外条件
		{
			if (token[5] == "sellerid")
			{
				command.erase(command.begin()+20,command.end()); // 去掉末尾部分
				cout << display_string[5]<<endl;
				for(auto o:orders)
					if (o.sellerid == token[7])
					{
						success = 1;
						o.display(identity);
					}
			}
			else if (token[5] == "buyerid")
			{
				command.erase(command.begin() + 20, command.end()); // 去掉末尾部分
				cout << display_string[6]<<endl;
				for (auto o : orders)
					if (o.buyerid == token[7])
					{
						success = 1;
						o.display(identity);
					}
			}
		}
		else
		{
			cout << display_string[4] << endl;
			success = 1;
			for (int i = 0; i < orders.size(); i++)
				orders[i].display(identity);
		}
	}
	// 查询用户
	else if (token[3] == "user")
	{
		if (length > 4)  // 额外条件
		{
			if (token[5] == "userID")
			{
				for(auto u:users)
					if (u.uid == token[7])
					{
						success = 1;
						cout << "用户名： " << u.uname << endl;
						cout << "联系方式： " << u.phonenumber << endl;
						cout << "地址： " << u.address << endl;
						cout << "余额： " << fixed << setprecision(1) << u.balance << endl;
					}
			}
		}
		else
		{
			success = 1;
			cout << display_string[7] << endl;
			for (auto u : users)
				u.user_display();
		}
	}
	if (!success)
		cout << "没找到相应结果！" << endl;
	else
		WritingCommands(command);
	cout << display_string[0] << endl;
	return success;
}
bool Platform::analyze_message_insert(string message, vector<string> token, int identity)
{
	int length = token.size();
	bool success = 0;
	string command ;
	if (token[2] == "commodity")  // 加入商品
	{
		// 检查输入
		bool legal_p = 1; check_float(token[5], legal_p);
		bool legal_n = 1; check_int(token[6], legal_n);
		if (legal_p && legal_n)
		{
			command = "INSERT INTO commodity VALUES(";
			cout << "请确认输入商品信息准确无误！" << endl;
			cout << display_string[0] << endl;
			
			// 设定新商品值并构成命令
			Commodity new_c;
			new_c.cname = token[4]; command = command + token[4] + ",";
			new_c.price = atof(token[5].c_str()); command = command + token[5] + ",";
			new_c.number = atoi(token[6].c_str()); command = command + token[6] + ",";
			new_c.description = token[7]; command = command + token[7] + ")";
			to_use_cid += 1;
			new_c.cid = "M";
			change_id(new_c.cid, to_use_cid, 2);
			new_c.addedDate = gettime(2);
			new_c.state = 1;
			new_c.sellerid = temp_user.uid;

			cout << "商品名称：" << new_c.cname << endl;
			cout << "商品价格：" << new_c.price << endl;
			cout << "商品数量：" << new_c.number << endl;
			cout << "商品描述：" << new_c.description << endl;
			cout << display_string[0] << endl;
			cout << "您确认要发布商品吗？[y/n]";
			if (check_y_n())
			{
				success = 1;
				commodities.push_back(new_c);
				write_document(2);
				cout << "发布成功" << endl;
			}
			else
				cout << "取消发布" << endl;
		}
		else
			cout << "非法输入！" << endl;
	}
	else if (token[2] == "order")  // 加入订单
	{
		int i=0;
		bool legal_n = 1; check_int(token[5], legal_n);
		if (legal_n)
		{
			cout << display_string[0] << endl;
			cout << "交易提醒！" << endl;
			for (; i < commodities.size(); i++)
				if (commodities[i].cid == token[4] && commodities[i].state == 1)
					break;
			if (i < commodities.size())
			{
				cout << "交易时间：" << gettime(1)<< endl;
				cout << "交易单价：" << fixed << setprecision(1) << commodities[i].price << endl;
				cout << "交易数量：" << token[5] << endl;
				float money = commodities[i].price * atoi(token[5].c_str());
				cout << "花费：" << fixed << setprecision(1) << money << endl;
				cout << "是否要交易？ [y/n]" << endl;
				if (check_y_n())
				{
					cout << display_string[0] << endl;
					if (commodities[i].number < atoi(token[5].c_str()))
						cout << "交易失败！ 该商品库存不足！" << endl;
					else if (temp_user.balance < money)
						cout << "交易失败！ 余额不足！" << endl;
					else
					{
						success = 1;
						commodities[i].number -= atoi(token[5].c_str());
						temp_user.balance -= money;
						// 重新设置数量
						WritingCommands("UPDATE commodity SET number = "
							+ to_string(commodities[i].number) + " WHERE commodityID = " + commodities[i].cid);
						if (commodities[i].number == 0)
						{
							commodities[i].state = 0;
							// 下架商品
							WritingCommands("UPDATE commodity SET state = inactive WHERE commodityID = " + commodities[i].cid);

						}
						cout << "交易成功！" << endl;
						Order new_o;
						to_use_oid += 1;
						new_o.oid = "T";
						change_id(new_o.oid, to_use_oid, 2);
						new_o.cid = commodities[i].cid;
						new_o.price = commodities[i].price;
						new_o.number = atoi(token[5].c_str());
						new_o.date = gettime(2);
						new_o.sellerid = commodities[i].sellerid;
						new_o.buyerid = temp_user.get_uid();
						orders.push_back(new_o);
						write_document(3);
						write_document(1);
						write_document(2);
					}
				}
				else
					cout << "取消交易" << endl;
			}
			else
				cout << "交易失败！ 找不到该id对应商品" << endl;
			cout << display_string[0] << endl;
		}
		else
			cout << "非法输入！" << endl;
	}
	if (success)
		WritingCommands(command);

	return success;
}
bool Platform::analyze_message_update(string message, vector<string> token, int identity)
{
	int length = token.size();
	bool success = 0;   // 更改成功
	bool legal = 1;     // 非法输入
	cout << display_string[0] << endl;
	string command = message;
	// 更新商品
	if (token[1] == "commodity")
	{
		for (auto &c : commodities)
			if (c.cid == token[9])
			{
				if (token[3] == "state")
				{
					
					if(token[5]=="inactive")
						c.state = 0;
					else if (token[5] == "active")
					{
						if(c.number>0)
							c.state = 1;
						else
						{
							cout << "上架失败 数量不足" << endl;
						}
					}
					success = 1;
				}
				else if (token[3] == "number")
				{
					int num = check_int(token[5], legal);
					if (legal)
					{
						success = 1;
						c.number = num;
					}
				}
				else if (token[3] == "description")
				{
					c.description = token[5];
					success = 1;
				}
				else if (token[3] == "price")
				{
					float price = check_float(token[5], legal);
					if (legal)
					{
						success = 1;
						c.price = price;
					}
				}
			}
		if(success)
			write_document(2);
	}
	// 更新用户
	else if (token[1] == "user")
	{
		for (auto &u : users)
		{
			if (u.uid == token[9])
			{
				if (token[3] == "username")
				{
					int name_length = token[5].size();
					if (name_length > 10)
					{
						legal = 0;
						cout << "用户名称过长" << endl;
					}
					else
					{
						for (int i = 0; i < name_length; i++)
						{

							if (token[5][i] <= 'z' && token[5][i] >= 'a')     // 字母
								;
							else if (token[5][i] <= 'Z' && token[5][i] >= 'A')
								;
							else
							{
								cout << "用户名中含非法字符" << endl;
								legal = 0;
								break;
							}
						}
					}
					for (int i = 0; i < users.size(); i++)
						if (users[i].uname == token[5])
						{
							cout << "与已有用户重名" << endl;
							legal = 0;
							break;
						}
					if (legal == 1)
					{
						u.uname = token[5];
						success = 1;
					}
				}
				else if (token[3] == "phonenumber")
				{
					success = 1;
					u.phonenumber = token[5];
				}
				else if (token[3] == "address")
				{
					success = 1;
					u.address = token[5];
				}
				else if (token[3] == "balance")
				{
					float bal = check_float(token[5], legal);
					if (legal == 1)
					{
						success = 1;
						u.balance += bal;
					}
				}
				else if (token[3] == "password")
				{
					success = 1;
					u.password = token[5];
				}
				else if (token[3] == "userState")
				{
					if (token[5] == "inactive")
					{
						u.state = 0;
						for (auto& c : commodities)
							if (c.sellerid == u.uid && c.state==1)
							{
								c.state = 0;
								WritingCommands("UPDATE commodity SET commodityState = inactive WHERE sellerid = " + u.uid);
							}
					}
					else if (token[5] == "active")
					{
						u.state = 1;
						for (auto& c : commodities)
							if (c.sellerid == u.uid && c.number>0 && c.state==0)
							{
								c.state = 1;
								WritingCommands("UPDATE commodity SET commodityState = active WHERE sellerid = " + u.uid);
							}
					}
					success = 1;
				}
			}
		}
		if (success)
			write_document(1);
		
	}
	if (!legal)
		cout << "非法输入！" << endl;
	if(!success)
		cout << "没找到相应结果！" << endl;
	else
	{
		cout << "更改成功！" << endl;
		WritingCommands(command);
	}
	cout << display_string[0] << endl;
	return success;
}
void Platform::write_document(int kind)      // 1 user;2 commodity;3 order;4 
{
	switch (kind)
	{
	case 1:
	{
		ofstream fout("D:/data/user.txt", ios::out);
		if (!fout.is_open())
			cout << "no file user.txt!";
		else
		{
			fout << display_string[8] << endl;
			for (int i = 0; i < users.size(); i++)
			{
				fout << users[i].uid << "," << users[i].uname << "," << users[i].password << ",";
				fout <<  fixed << setprecision(1)<< users[i].phonenumber;
				fout << "," << users[i].address << "," << users[i].balance << ",";
				if (users[i].state)
					fout << "active" << endl;
				else
					fout << "inactive" << endl;
			}
			fout.close();
		}
		break;
	}
	case 2:
	{
		ofstream fout("D:/data/commodity.txt", ios::out);
		if (!fout.is_open())
			cout << "no file commodity.txt!";
		else
		{
			fout << display_string[9] << endl;
			for (int i = 0; i < commodities.size(); i++)
			{
				fout << commodities[i].cid << "," << commodities[i].cname << ",";
				fout << fixed << setprecision(1) << commodities[i].price<<",";
				fout << commodities[i].number << "," << commodities[i].description << ","
					<< commodities[i].sellerid << "," << commodities[i].addedDate<<",";
				if (commodities[i].state)
					fout << "active" << endl;
				else
					fout << "inactive" << endl;
			}
			fout.close();
		}
		break;
	}
	case 3:
	{
		// orderID,commodityID,unitPrice,number,date,sellerID,buyerID
		ofstream fout("D:/data/order.txt", ios::app|ios::out);
		if (!fout.is_open())
			cout << "no file order.txt!";
		else
		{
			int t = orders.size() - 1;
			fout << orders[t].oid << "," << orders[t].cid << ",";
			fout << fixed << setprecision(1) << orders[t].price << "," << orders[t].number << ","
				<< orders[t].date << "," << orders[t].sellerid << "," << orders[t].buyerid << endl;
			fout.close();
		}
		break;
	}
	case 4:
	{
		ofstream fout("D:/data/cart.txt", ios::out);
		if (!fout.is_open())
			cout << "no file cart.txt!";
		else
		{
			for (int i = 0; i < users.size(); i++)
			{
				fout << users[i].uid;
				for (int j = 0; j < users[i].cart.size(); j++)
					fout << "," << users[i].cart[j];
				fout << endl;
			}
			fout.close();
		}
		break;
	}
	}
}


