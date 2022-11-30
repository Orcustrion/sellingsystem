#pragma once
#include<iostream>
#include<cstring>
using namespace std;
struct Commodity {
	string cid;    // ��Ʒid��M��ͷ
	string cname;   // ����
	float price;    // �۸�
	int number;     // ����
	string description;  // ����
	string sellerid;  // ����id
	string addedDate;         // �ϼ�ʱ��
	bool state;     // ��Ʒ״̬
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
	}; // �������
};

struct Order {
	string oid;    // ����id��T��ͷ
	string cid;    // ��Ʒid��M��ͷ
	float price;    // �ɽ�����
	int number;     // ��������
	string date;    // ����ʱ��
	string sellerid;  // ����id
	string buyerid;   // ���id
	void display(int authority)
	{ 
		cout << setiosflags(ios::left) << setw(9) << oid << setw(9) << cid
			<< setw(11) <<  fixed << setprecision(1)<< price << setw(8) << number << setw(13) << date << setw(4);
		if (authority != 2)
			cout << sellerid << "     ";
		if (authority != 3)
			cout << buyerid << "     ";
		cout << endl;
	}; // �������
};