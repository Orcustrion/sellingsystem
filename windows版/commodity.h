#pragma once
#include<iostream>
#include<cstring>
using namespace std;
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
		cout <<  fixed << setprecision(1) << price << setw(9) << number << setw(15) << addedDate << setw(8);
		if (authority != 3)
		{
			if (state)
				cout << "active"<<"   ";
			else
				cout << "inactive"<<"   ";
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
			<< setw(11) <<  fixed << setprecision(1)<< price << setw(8) << number << setw(13) << date << setw(4);
		if (authority != 2)
			cout << sellerid << "     ";
		if (authority != 3)
			cout << buyerid << "     ";
		cout << endl;
	}; // 输出函数
};