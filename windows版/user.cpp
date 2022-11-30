#include<iostream>
#include "user.h"
#include "help.h"
using namespace std;

User::User()
{
	password = uname = phonenumber = address = "";
	balance = 0;
	state = 1;
}
User::User(string _uname, string _password,int _uid)
{
	uname = _uname;
	password = _password;
	phonenumber = address = "";
	balance = 0;
	state = 1;
	uid = "U";
	change_id(uid, _uid, 2);
}
User::User(string _uid)
{
	uid=_uid;
}
void User::user_display()
{
	// 对齐
	cout << setiosflags(ios::left) <<setw(9)<<uid << setw(9) << uname 
		<< setw(13) << phonenumber << setw(16) << address 
		<< setw(10) <<  fixed << setprecision(1) << balance << setw(8);
	if (state)
		cout << "active";
	else
		cout << "inactive";
	cout << endl;
}
string User::user_control(int opt)
{
	string message;
	switch (opt)
	{
	case 1:   // 查看信息
		message = "SELECT * FROM user WHERE userID = " + uid;
		break;
	case 2:   // 修改信息
	case 3:   // 充值
		message = user_update(opt);
		break;
	default:
		break;
	}
	return message;
}
string User::user_update(int opt)
{
	string message1 = "UPDATE user SET ";
	string message2 = " WHERE userID = " + string(uid);
	if (opt == 2)
	{
		cout << "请输入要修改的属性：(1.用户名 2.联系方式 3.地址)";
		int sign = check_opt(1, 3);
		if (sign == 1)
		{
			cout << "请输入修改后的用户名：";
			string a; 
			cin.ignore();
			getline(cin, a);
			message1 = message1 + "username = " + a;
		}
		else if (sign == 2)
		{
			cout << "请输入修改后的联系方式：";
			string a; 
			cin.ignore();
			getline(cin, a);
			message1 = message1 + "phonenumber = " + a;
		}
		else if (sign == 3)
		{
			cout << "请输入修改后的地址：";
			string a; 
			cin.ignore();
			getline(cin, a);
			message1 = message1 + "address = " + a;
		}
	}
	else
	{
		cout << "请输入要充值的金额：";
		string a; 
		cin.ignore();
		getline(cin, a);
		message1 += "balance + "+a;
	}

	return message1 + message2;
}


Seller::Seller(string _uid):User(_uid)
{

}
string Seller::seller_control(int opt)
{
	string message;
	switch (opt)
	{
	case 1:   // 发布商品
		message = seller_insert_commodity();
		break;
	case 2:   // 查看发布的商品
		message = "SELECT * FROM commodity WHERE sellerid = " + get_uid();
		break;
	case 3:   // 修改商品属性
	case 4:   // 下架商品
		message = seller_update_commodity(opt);
		break;
	case 5:
		message = "SELECT * FROM order WHERE sellerid = " + get_uid();
		break;
	default:
		break;
	}
	return message;
}
string Seller::seller_insert_commodity()
{
	string message = "INSERT INTO commodity VALUES ";
	cin.ignore();
	cout << "请输入商品名称：";
	string str;
	getline(cin,str);
	message = message + str + " ";

	cout << "请输入商品价格：";
	getline(cin, str);
	message = message + str + " ";

	cout << "请输入商品数量：";
	getline(cin, str);
	message = message + str + " ";

	cout << "请输入商品描述：";
	getline(cin, str);
	message = message + str;

	return message;
}
string Seller::seller_update_commodity(int opt)
{
	string message1 = "UPDATE commodity SET ";
	cout << "请输入要进行操作的商品编号：";
	string cid;
	cin.ignore();
	getline(cin, cid);
	string message2 = " WHERE commodityID = " + cid;
	if (opt == 3)
	{
		cout << "请输入要修改商品的属性：(1.价格 2.数量 3.描述)";
		int sign=check_opt(1, 3);
		if (sign == 1)
		{
			cout << "请输入被修改商品的价格：";
			string a; 
			cin.ignore();
			getline(cin, a);
			message1 = message1 + "price = " + a;
		}
		else if (sign == 2)
		{
			cout << "请输入被修改商品的数量：";
			string a; 
			cin.ignore();
			getline(cin, a);
			message1 = message1 + "number = " + a;
		}
		else if (sign == 3)
		{
			cout << "请输入被修改商品的描述：";
			string a; 
			cin.ignore();
			getline(cin, a);
			message1 = message1 + "description = " + a;
		}
	}
	else
	{
		cout << "请输入：1、下架  2、上架";
		int change = check_opt(1, 2);
		if(change==1)
			message1 += "state = inactive";
		else
			message1 += "state = active";
	}

	return message1 + message2;
}

Buyer::Buyer(string _uid) :User(_uid)
{

}
string Buyer::buyer_control(int opt)
{
	string message;
	switch (opt)
	{
	case 1:   // 查询商品
	case 3:
	case 5:
		message = buyer_select_commodity(opt);
		break;
	case 2:   // 购买商品
		message = buyer_insert_order();
		break;
	case 4:   // 查看订单
		message = "SELECT * FROM order WHERE buyerid = " + get_uid();
		break;
	default:
		break;
	}
	return message;
}
string Buyer::buyer_select_commodity(int opt)
{
	string message = "SELECT * FROM commodity";
	cin.ignore();
	if (opt == 1)
		return message;
	else if(opt == 3)
	{
		cout << "请输入商品名称: ";
		string cname;
		getline(cin, cname);
		return (message + " WHERE commodityName CONTAINS " + cname);
	}
	else if (opt == 5)
	{
		cout << "请输入要查看商品的ID: ";
		string cid;
		getline(cin, cid);
		return (message + " WHERE commodityID = " + cid);
	}
}
string Buyer::buyer_insert_order()
{
	string message = "INSERT INTO order VALUES ";
	string str;
	cin.ignore();
	cout << "请输入商品ID：";
	getline(cin, str);
	message = message + str + " ";
	cout << "请输入数量：";
	getline(cin, str);
	message = message + str;

	return message;
}


string Administrator::admin_control(int opt)
{
	string message;
	switch (opt)
	{
	case 1:
	case 2:
		message = admin_select_commodity(opt);
		break;
	case 3:
	case 6:
		message = admin_change_state(opt);
		break;
	case 4:
		message = "SELECT * FROM order";
		break;
	case 5:
		message = "SELECT * FROM user";
		break;
	default:
		break;
	}
	return message;
}

string Administrator::admin_select_commodity(int opt)
{
	string message= "SELECT * FROM commodity";
	if (opt == 1)
		return message;
	
	else
	{
		cout << "请输入商品名称: ";
		string cname;
		cin >> cname;
		return (message + " WHERE commodityName CONTAINS " + cname);
	}
}
string Administrator::admin_change_state(int opt)
{
	if (opt == 3)
	{
		cout << "请输入要下架/上架商品的ID: ";
		string cid;
		cin >> cid;
		cout << "请输入：1、下架  2、上架";
		int change = check_opt(1, 2);
		if(change==1)
			return "UPDATE commodity SET state = inactive WHERE commodityID = " + cid;
		else
			return "UPDATE commodity SET state = active WHERE commodityID = " + cid;
	}
	if (opt == 6)
	{
		cout << "请输入要封禁/解封的用户ID: ";
		string uid;
		cin >> uid;
		cout << "请输入：1、封禁  2、解封";
		int change = check_opt(1, 2);
		if(change==1)
			return "UPDATE user SET userState = inactive WHERE userID = " + uid;
		else
			return "UPDATE user SET userState = active WHERE userID = " + uid;
	}
}