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
	Administrator admin;            // Ψһ����Ա
	User temp_user;                 // ��ǰ��¼�û�
	Calculator cal;                 // �������ӿ�
	string message;                 // ָ��

	vector<Commodity> commodities;  // ��Ʒ����
	vector<Order>     orders;       // ��������
	vector<User>      users;        // �û�����

	int to_use_uid;                 // ׼����id
	int to_use_cid;
	int to_use_oid;

	string file_path;               // ��ȡ�ļ�·��
	vector<string> display_string;  // ��������ַ�����

public:
	Platform();

	// ��Ҫ��ʾ����
	void start_display();          // ��ʼ����չʾ
	void login_display();          // ��¼����չʾ
	void calculator_display();     // ����������չʾ 
	void admin_display();          // ����Ա����չʾ
	void user_display();           // �û�����չʾ
	void seller_display();         // ���ҽ���չʾ
	void buyer_display();          // ��ҽ���չʾ
	void cart_display();           // ���ﳵ����չʾ
	void user_info_display();      // �û���Ϣ����չʾ
	
	// ��¼���溯��
	void login_admin();  
	void login_user();
	void signin_user();

	// ���ƺ���
	bool analyze_message(int );        // �������� ��������
	bool analyze_message_select(string , vector<string> ,int);     // ����ѡ�����
	bool analyze_message_insert(string , vector<string> ,int);     // �����������
	bool analyze_message_update(string , vector<string> ,int);     // �����������

	void write_document(int );         // д���ļ�

};
