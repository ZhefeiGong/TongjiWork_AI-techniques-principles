/*
 * @author   : gonzalez
 * @time     : 2022.5.26-2022.6.2
 * @function : 项目头文件
 */
#pragma once

#include<iostream>             // 标准流
#include<vector>               // SRL容器
#include<string>               // string
#include<queue>                // STL队列
#include<algorithm>            // 基础算法库
#include<iomanip>              // 格式化输入输出
#include<windows.h>            // windows系统库
#include<graphics.h>           // EasyX库
#include<conio.h>              // EasyX库

using namespace std;

//*********************************************************************
//* @function  : 一阶逻辑内部核心实现
//* @notice    : 无
//*********************************************************************

// @notice:
// K(x,y)  表示  怀疑x杀了y
// L(x)    表示  x生活在这栋房子里
// H(x,y)  表示  x恨y
// R(x,y)  表示  x比y富有
// E(x,y)  表示  x和y相等
// A(x)    表示  x就是所求凶手
//
// 变量 -- a-z
// 常量 -- A-Z
// 函数 -- f(x)用'&'表示函数

// @function : 长度归结限制长度
#define  LENGTHEDGE      3
// @function : 函数代表
#define  FUNCTION       '&'
// @function : 表达式划归
#define  OR             '|'
#define  NOT            '~'
#define  DOT            ','
#define  LEFTBRACKET    '('
#define  RIGHTBRACKET   ')'
#define  EQUAL          'E'
#define  ANSWER         'A'


// 函数结构体
struct FUNC {
	char name = '\0';
	char parameter = '\0';
};
// 独立表达式
struct EXPRE{
	bool IsNot = true;        // 表达式是否取非
	char type = '\0';         // 表达式的类别
	vector<char>element;      // 表达式中的元素
	FUNC func;                // 单独存储函数表达式
};
// 独立子句
struct CLAUSES{
	string name;              // 子句编号
	vector<EXPRE>expressions; // 子句表达式合集
};
// 过程记录
struct RECORD{
	string resultName;   // 结果逻辑名字
	string result;       // 逻辑表达式
	string father1Name;  // 父节点1名字
	string father2Name;  // 父节点2名字
	string change;       // 置换合一变化
};

// @function : 子句归结执行内核
class clauseResolution {
protected:

	// 内部参数
	CLAUSES answer;                                                  // 最终结果
	int countNum = 0;                                                // 用于记录转换个数
	vector<char>expressionType;                                      // 该推断问题中表达式的所有种类 --> 'A'-'Z'代替
	vector<CLAUSES>clauseBag;                                        // 存储所有转化后的子句集

	// 可视化结果存储
	vector<RECORD>initialList;                                       // 初始化数据存储
	vector<RECORD>recordList;                                        // 过程数据存储
	vector<RECORD>bestPath;                                          // 最优归结路线

	// 内部函数
	void initialRecord(void);                                                                      // 初始逻辑记录
	void processRecord(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& upData, RECORD& get); // 归结过程记录
	void traceBackIn(RECORD& c);                                                                   // 寻找最佳归结路线内部递归函数
	void expressionInput(string& original, CLAUSES& c);                                            // 将一个字符串转换成
	bool clausesUpdate(CLAUSES& ans, vector<char>& record, vector<char>& upData);                  // 子句更新
	bool judgeAnswer(CLAUSES& c1);                                                                 // 判断是否归结到终点
	bool equalDeal(CLAUSES& c, vector<CLAUSES>& tempBag);                                          // 等式归结[若为E(f(A),B)则将f(A)替换为B]
	bool containDeal(CLAUSES& c, vector<CLAUSES>& tempBag);                                        // 包容归结
	bool lengthDeal(CLAUSES& c, vector<CLAUSES>& tempBag);                                         // 长度限制
	bool twoClauseResolu(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& record);            // 两个子句归结 
	void processShow(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& upData);                // 控制台打印过程
	void initialShow(void);                                                                        // 控制台打印初始过程


public:
	// 外部函数
    void traceBack(void);                                            // 寻找最佳归结路线
	void clausInput(vector<string> &originalSentence);               // 将输入子句转化为易计算结构子句
	void resolution(void);                                           // 执行子句归结
	void allShow(void);                                              // 展示所有归结过程
	void bestShow(void);                                             // 展示最优归结过程
	void ansShow(void);                                              // 显示最终结果

	void tempShow(void);                                             // for test 
};



//*********************************************************************
//* @function  : UI界面类
//* @notice    : 无
//*********************************************************************

// 页面布局结构体
struct SURFACE {
	short left = 0;
	short top = 0;
};

#define UILENGTH   758
#define UIWIDTH    400

#define BUTTONLENGTH 189
#define BUTTONWIDTH  70
#define RESTARTLEN   50


#define MOUSEINPUT    1
#define MOUSEALL      2
#define MOUSEBEST     3
#define MOUSEREST     4

// @function : 字句归结UI界面
class clauseUI {
protected:
	// 界面布局结构体定义
	SURFACE backArea;
	SURFACE inputArea;
	SURFACE showallArea;
	SURFACE showbestArea;
	SURFACE restartArea;

	// 界面图片调用定义
	IMAGE background;
	IMAGE input;
	IMAGE inputActive;
	IMAGE showAll;
	IMAGE showAllActive;
	IMAGE showBest;
	IMAGE showBestActive;
	IMAGE restart;
	IMAGE restartActive;

public:
	clauseUI(void);                           // 初始化
	void bgShow(void);                        // 展示背景
	int orderChoose(bool haveIn = false);     // 按键指示

};



//*********************************************************************
//* @function  : 工具函数
//* @notice    : 无
//*********************************************************************

// @function : 工具函数
void dataIn(vector<string>& originalSentence);//输入对应的数据





