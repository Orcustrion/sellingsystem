#pragma once
#include<iostream>
#include<iomanip>
#include<string>
#include "help.h"
using namespace std;
class Platform;
class User
{
private:
    string uid;                 //�û�ID
    string password;            //����
    string phonenumber;         //��ϵ��ʽ
    string address;             //��ַ
    float balance;              //Ǯ�����
    bool state;                 //�û�״̬  1���� 0���
    vector<string> cart;        //���ﳵ
    friend class Platform;

public:
    string uname;             //�û���
    User();
    User(string, string,int );    //���ι��캯��
    User(string );       //ֻ��uid�Ĺ��캯��

    void user_display();      //��ʾ����
    string get_uid() { return uid; } // ����uid

    string user_control(int );             // �û��޸���Ϣ����
    string user_update(int);               // �û��޸���Ϣ����
};
class Seller : public User
{
public:
    Seller(string );
    string seller_control(int );         // ���ҽ�����������
    string seller_insert_commodity();    // ������Ʒ
    string seller_update_commodity(int); // �޸�/�¼���Ʒ

    friend class Platform;
};
class Buyer : public User
{

public:
    Buyer(string );
    string buyer_control(int);
    string buyer_select_commodity(int );
    string buyer_insert_order();

    friend class Platform;
};

class Administrator
{
private:
    string adname;      // ����Ա��
    string password;    // ����Ա����

    friend class Platform;
public:
    string admin_control(int );          // ����Ա������������
    string admin_select_commodity(int);  // ��ѯ/������Ʒ
    string admin_change_state(int );     // ����û�/�¼���Ʒ


};