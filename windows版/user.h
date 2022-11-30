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
    User(string, string,int );    //含参构造函数
    User(string );       //只含uid的构造函数

    void user_display();      //显示函数
    string get_uid() { return uid; } // 返回uid

    string user_control(int );             // 用户修改信息控制
    string user_update(int);               // 用户修改信息命令
};
class Seller : public User
{
public:
    Seller(string );
    string seller_control(int );         // 卖家界面生成命令
    string seller_insert_commodity();    // 发布商品
    string seller_update_commodity(int); // 修改/下架商品

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
    string adname;      // 管理员名
    string password;    // 管理员密码

    friend class Platform;
public:
    string admin_control(int );          // 管理员界面生成命令
    string admin_select_commodity(int);  // 查询/搜索商品
    string admin_change_state(int );     // 封禁用户/下架商品


};