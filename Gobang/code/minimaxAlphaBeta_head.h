#pragma once
/*
 * @author    : gonzalez
 * @time      : 2022.5.2-2022.5.9
 * @function  : AlphaBeta 头文件
 */


#include <vector>              // vector数组
#include <iostream>            // 标准库
#include <algorithm>           // 算法库
#include <stack>               // 优先队列
#include <graphics.h>          // EasyX库
#include <conio.h>             // EasyX库
using namespace std;


/**********************************************************************/
//@author    : gonzalez
//@time      : 2022.4.27-2022.5.9
//@function  : 运用alphabeta搜索实现简单五子棋ai
//@notice    : 返回值规定-->True成功；False失败
//             '1'黑棋  '0'白棋  '*'无棋
//             默认下白棋
/**********************************************************************/

//宏定义区域
#define BOARDLENGHT 15  //棋盘长度
#define BOARDWIDTH  15  //棋盘宽度
#define BOARDADD    2   //棋盘需添加值


#define BLACKCHESS     '1'  // 定义黑子代表 
#define WHITECHESS     '0'  // 定义百子代表
#define NONECHESS      '*'  // 定义空棋盘代表
#define EACHSEARCH     2    // 定义每层的探索个数
#define EXPLORELAYER   6    // 定义探索层数

//@function:结点信息结构体
struct NODE {
	vector<NODE>children;               //孩子结点
	vector<short> blackAdd;             //添加的黑子坐标 row*100+col
	vector<short> whiteAdd;             //添加的白子坐标 row*100+col
	short layer = 0;
	int alpha = INT_MIN;                //该结点的alpha值-->最大值
	int beta = INT_MAX;                 //该结点的beta值-->最小值
};

//@function:统计边界信息
struct BORDER{
	int left = 0;
	int top = 0;
	int right = 0;
	int down = 0;
};

//@function:用于寻找较优拓展点
struct NODESCORE {
	short rowSite = 0;
	short colSite = 0;
	int score;
};

//@function:alpha-beta剪枝搜索类
class searchAlphaBeta {
protected:
	NODE head;
	char board[BOARDWIDTH + BOARDADD][BOARDLENGHT + BOARDADD] = { '\0' };
protected:
    
	int getScoreFromString(string& get);                                                                              //得到一个string串的评估得分
    int toneUpAssessIn(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& site);                                   //增益函数内部评估
    void toneUpAssess(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& site, char sort);	                      //增益评估
	bool searchThreeMust(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& get, char chessSort);                  //白棋活三特判
	bool searchFiveMust(char(*chessBoard)[BOARDLENGHT + BOARDADD], NODESCORE& get, char chessSort);                   //五子连珠特判
	bool fiveMust(string& get, char chessSort);                                                                       //五子连珠特判内部执行函数
	bool firstLayerAssess(char(*chessBoard)[BOARDLENGHT + BOARDADD], int& feeBack);                                   //第一层首先评估
	bool chessAround(int row, int col, char(*chess)[BOARDLENGHT + BOARDADD]);                                         //判断NONECHESS周围是否存在CEHSS
	bool findBorder(char(*chessBoard)[BOARDLENGHT + BOARDADD], BORDER& bor);                                          //找到搜索边界
	int eachGet(string& extract);                                                                                     //评价函数中对不同的情况返回不同得分
	int assessBoardValue(char(*chessBoard)[BOARDLENGHT + BOARDADD]);                                                  //全局评估函数
	bool seekBestPoint(char(*chessBoard)[BOARDLENGHT + BOARDADD], char chessClass, vector<NODESCORE>& result);        //找到较优的几个点进行针对性拓展
	int alphabetaAlgorithm(char(*chessBoard)[BOARDLENGHT + BOARDADD], int depth, int alpha, int beta);                //进行alpha-beta剪枝搜索

public:
	searchAlphaBeta(char(*chessBoard)[BOARDLENGHT + BOARDADD]);                                                       //构造棋盘函数                             
	int alphabetaGetBack(void);                                                                                       //执行函数
};


/**********************************************************************/
//@author    : gonzalez
//@time      : 2022.4.27-2022.5.9
//@function  : 界面可视化
/**********************************************************************/

//@function : 存储界面布局的结构体
struct SURFACE{
	short left = 0;
	short top = 0;
	short right = 0;
	short bottom = 0;
};

//@function : 用于图像的初始化
#define PICTUREBKWIDTH    700//游戏界面宽度
#define PICTUREBKLENGTH   1000//游戏界面长度
#define CBbetweenBK       25//左端点间隔
#define PICTURECBWIDTH    650//棋盘宽度

#define CHESSMID          42//棋盘格子宽度
#define CHESSWIDTH        36//判断鼠标点击正确的区域直径

#define BUTTONLENGTH     255//按键长度
#define BUTTONWIDTH      125//按键宽度
#define PICTURELENGTH    255//右下角图片长度
#define PICTUREWIDTH     335//右下角图片宽度

#define ENDPICLENGTH     394//结束图片长度
#define ENDPICWIDTH      250//结束图片宽度

#define REGRET            -1//悔棋指令
#define RESTART           -2//重开指令

#define NOWINNER   0//无胜者
#define BLACKWIN   1//黑棋胜
#define WHITEWIN   2//白棋胜

//@function : 图像UI界面显示类
class showUI {
protected:

	//界面布局结构体定义
	SURFACE boardImage;
	SURFACE regretButton;
	SURFACE restartButton;
	SURFACE pictureSite;
	SURFACE winloseShow;

	//界面图片调用定义
	IMAGE backGround;
	IMAGE chessBoard;
	IMAGE chessBlack;
	IMAGE chessWhite;
	IMAGE chessWhitePre;

	IMAGE regretImage;
	IMAGE regretMouseImage;
	IMAGE restartImage;
	IMAGE restartMouseImage;
	IMAGE thinkingImage;
	IMAGE userImage;

	IMAGE winImage;
	IMAGE loseImage;

	bool findXY(int x, int y, int& boardX, int& boardY);            //找到xy所对应在棋盘中的位置
	void endShow(void);                                             //结束后只能按下重新开始按钮
public:
	showUI(void);                                                   //构造函数
	bool refresh(char(*chessBoard)[BOARDLENGHT + BOARDADD]);        //重置界面情况
	bool uiLoad(void);                                              //加载背景界面函数
	int uiGetBack(char(*chessBoard)[BOARDLENGHT + BOARDADD]);       //单步下棋执行函数
	bool addWhite(int site);                                        //在棋盘上添加白棋
	void winShow(void);                                             //成功显示
	void loseShow(void);                                            //失败显示
	void showThinking(void);                                        //切换图片
	void showNormal(void);                                          //切换图片
};


/**********************************************************************/
//@author    : gonzalez
//@time      : 2022.5.4-2022.5.9
//@function  : 其余工具函数
/**********************************************************************/
int judgeWinner(char(*chessBoard)[BOARDLENGHT + BOARDADD]);         //判断是否成功
void refreshBoard(char(*chessBoard)[BOARDLENGHT + BOARDADD]);       //重置棋盘

