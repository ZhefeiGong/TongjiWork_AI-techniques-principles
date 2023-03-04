/*
 * @author   : gonzalez
 * @time     : 2022.5.26-2022.6.2
 * @function :
 */

#include"logicalReasoning_head.h"
using namespace std;


/*****************************************************************************************/
/******************************一阶逻辑归结内部核心函数***********************************/
/*****************************************************************************************/

// @function : 表达式子句划归
void clauseResolution::expressionInput(string& original, CLAUSES& c) {

	// 表达式数据
	EXPRE expression;

	// 判断类型
	string getString = original;
	int st = 0;
	if (getString[0] == NOT) {
		expression.IsNot = false;
		st = 1;
	}
	else
		expression.IsNot = true;

	// 表达式添加新类型
	bool hadFlag = false;
	for (int i = 0; i < (int)expressionType.size(); i++)
		if (expressionType[i] == getString[st]) {
			hadFlag = true;
			break;
		}
	if (!hadFlag)
		expressionType.push_back(getString[st]);
	expression.type = getString[st];

	// 此后仅考虑'(exprenssion)'
	++st;
	getString = getString.substr(st);

	// 判断内部数据
	int num = count(getString.begin(), getString.end(), DOT);
	// 表达式内两个字符
	if (num != 0) {

		// 初始化
		int site = getString.find(DOT);
		string frontString = getString;
		frontString.erase(site);
		string backString = getString.substr(site + 1);
		
		// 判断前半部
		if (count(frontString.begin(), frontString.end(), RIGHTBRACKET)) {     // 函数特判
			expression.element.push_back(FUNCTION);
			expression.func.name = *(frontString.begin() + 1);
			expression.func.parameter = *(frontString.begin() + 1 + 1 + 1);
		}
		else {
			char front = frontString[frontString.size() - 1];
			expression.element.push_back(front);
		}

		// 判断后半部
		if (count(backString.begin(), backString.end(), LEFTBRACKET)) {        // 函数特判
			expression.element.push_back(FUNCTION);
			expression.func.name = *(backString.begin());
			expression.func.parameter = *(backString.begin() + 1 + 1);
		}
		else {
			char back = backString[0];
			expression.element.push_back(back);
		}


	}
	// 表达式内仅一个字符
	else {
		// 判断是否为函数
		if (count(getString.begin(), getString.end(), RIGHTBRACKET) == 2) {    // 函数特判
			expression.element.push_back(FUNCTION);
			expression.func.name = *(getString.begin() + 1);
			expression.func.parameter = *(getString.begin() + 1 + 1 + 1);
		}
		// 判断常量或变量
		else {
			char val = getString[1];
			expression.element.push_back(val);
		}
	}

	// 添加对应子句
	c.expressions.push_back(expression);

	return;
}

// @function : 读入字符串转机内子句
void clauseResolution::clausInput(vector<string>& originalSentence){

	int len = originalSentence.size();
	for (int i = 0; i < len; i++) {
		CLAUSES c;                                // 子句获取
		string temp = originalSentence[i];
		int num = count(temp.begin(), temp.end(), OR);
		for (int i = 0; i <= num; i++) {
			if (i == num)
				expressionInput(temp,c);
			else {
				int site = temp.find(OR);
				string subTemp = temp;
				subTemp.erase(site);
				temp = temp.substr(site + 1);     // 删去对应的'|'
				expressionInput(subTemp,c);
			}
		}
		c.name = "c" + to_string(i + 1);          // 子句名字赋值
		clauseBag.push_back(c);                   // 添加子句
	}
	return;
}

// @function : 两个子句进行归结
bool clauseResolution::twoClauseResolu(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& record) {

	bool flag = false;
	for (int c1i = 0; c1i < (int)c1.expressions.size(); c1i++) {
		for (int c2j = 0; c2j < (int)c2.expressions.size(); c2j++) {
			flag = true;
			if (c1.expressions[c1i].type == c2.expressions[c2j].type) {                                   // 表达式类型一致
				if (c1.expressions[c1i].IsNot != c2.expressions[c2j].IsNot) {                             // 表达式符号相反
					if (c1.expressions[c1i].element.size() == c2.expressions[c2j].element.size()) {       // 参数个数一致
						vector<char> recordTemp;                                                          // 暂时进行归结存储
						// 判断具体各个是否能合一置换
						for (int k = 0; k < (int)c1.expressions[c1i].element.size(); k++) {
							//// 为存在函数的情况
							//if(c1.expressions[c1i].element[k]==FUNCTION)
							//	if (c1.expressions[c1i].func.parameter >= 'A' && c1.expressions[c1i].func.parameter <= 'Z')
							//		if (c2.expressions[c2j].element[k] >= 'A' && c2.expressions[c2j].element[k] <= 'Z') {
							//			flag = false;                                                     // 不可进行归结
							//			break;
							//		}
							//if (c2.expressions[c1i].element[k] == FUNCTION)
							//	if (c2.expressions[c1i].func.parameter >= 'A' && c2.expressions[c1i].func.parameter <= 'Z')
							//		if (c1.expressions[c2j].element[k] >= 'A' && c1.expressions[c2j].element[k] <= 'Z') {
							//			flag = false;                                                     // 不可进行归结
							//			break;
							//		}
							//// 均为常量
							//if ((c1.expressions[c1i].element[k] >= 'A' && c1.expressions[c1i].element[k] <= 'Z') &&
							//	(c2.expressions[c2j].element[k] >= 'A' && c2.expressions[c2j].element[k] <= 'Z')) {
							//	if (c1.expressions[c1i].element[k] != c2.expressions[c2j].element[k]) {
							//		flag = false;                                                         // 不可进行归结
							//		break;
							//	}
							//}
							
							// 至少一个变量||均常量且相等  -->  可归结
							if ((c1.expressions[c1i].element[k] >= 'a' && c1.expressions[c1i].element[k] < 'z') ||
								(c2.expressions[c2j].element[k] >= 'a' && c2.expressions[c2j].element[k] < 'z') ||
								(c1.expressions[c1i].element[k] == c2.expressions[c2j].element[k]))
								flag = true;
							else {
								flag = false;
								break;
							}
							recordTemp.push_back(c1.expressions[c1i].element[k]);// 归结过程统计
							if (c1.expressions[c1i].element[k] == FUNCTION) {
								recordTemp.push_back(c1.expressions[c1i].func.name);
								recordTemp.push_back(c1.expressions[c1i].func.parameter);
							}
							recordTemp.push_back(c2.expressions[c2j].element[k]);// 归结过程统计
							if (c2.expressions[c2j].element[k] == FUNCTION) {
								recordTemp.push_back(c2.expressions[c2j].func.name);
								recordTemp.push_back(c2.expressions[c2j].func.parameter);
							}
						}
						// 进行归结
						if (flag) {
							// 新子句名字
							ans.name = "T" + to_string(++countNum);

							// 添加原有子句
							for (int tempi = 0; tempi < (int)c1.expressions.size(); tempi++) {
								if (tempi != c1i)
									ans.expressions.push_back(c1.expressions[tempi]);
							}
							// 添加原有子句
							for (int tempj = 0; tempj < (int)c2.expressions.size(); tempj++) {
								if (tempj != c2j)
									ans.expressions.push_back(c2.expressions[tempj]);
							}
							// 合一置换等式语句
							for (int i = 0; i < (int)recordTemp.size(); i++)
								record.push_back(recordTemp[i]);

							return true;
						}
					}
				}
			}
		}
	}

	return false;

}

// @function : 新子句标识符更新
bool clauseResolution::clausesUpdate(CLAUSES& ans, vector<char>& record, vector<char>& upData) {

	for (int i = 0; i < (int)record.size();) {

		// 交换参数获取
		char get1[3] = { '\0','\0' ,'\0'};
		char get2[3] = { '\0','\0' ,'\0' };
		if (record[i] == FUNCTION) {
			get1[0] = FUNCTION;
			get1[1] = record[i + 1];
			get1[2] = record[i + 2];
			i += 3;
		}
		else {
			get1[0] = record[i];
			i += 1;
		}
		if (record[i] == FUNCTION) {
			get2[0] = FUNCTION;
			get2[1] = record[i + 1];
			get2[2] = record[i + 2];
			i += 3;
		}
		else {
			get2[0] = record[i];
			i += 1;
		}
		
		// 此时存在替换情况-->即1常量/1变量/1函数 代替 1变量
		if ((get1[0] >= 'a' && get1[0] <= 'z') || (get2[0] >= 'a' && get2[0] <= 'z')) {

			// 确定替换项和被替换项
			char cans, para;
			if ((get1[0] >= 'a' && get1[0] <= 'z')) {
				para = get1[0];
				cans = get2[0];
			}
			else {
				para = get2[0];
				cans = get1[0];
			}

			// 变化矩阵同步更新
			for (int ini = 0; ini < (int)upData.size(); ini++)
				if (upData[ini] == para)
					upData[ini] = cans;

			// upData参数追加
			upData.push_back(para);//被替换变量
			upData.push_back(cans);//被替换常量
			// 函数参数追加
			FUNC temp = { '\0','\0' };
			if (get1[0] == FUNCTION) {
				upData.push_back(get1[1]);//函数符号
				temp.name = get1[1];
				upData.push_back(get1[2]);//函数参数
				temp.parameter = get1[2];
			}
			else if (get2[0] == FUNCTION) {
				upData.push_back(get2[1]);//函数符号
				temp.name = get2[1];
				upData.push_back(get2[2]);//函数参数
				temp.parameter = get2[2];
			}

			// 开始更新当前新子句信息
			for (int i = 0; i < (int)ans.expressions.size(); i++) {
				for (int j = 0; j < (int)ans.expressions[i].element.size(); j++) {
					// 参数更换
					if (para == ans.expressions[i].element[j]) {
						ans.expressions[i].element[j] = cans;
						ans.expressions[i].func.name = temp.name;
						ans.expressions[i].func.parameter = temp.parameter;
					}
					// 函数参数更换
					if (para == ans.expressions[i].func.parameter)
						ans.expressions[i].func.parameter = cans;
				}
			}

			// 变化矩阵同步更新
			for (int ini = i; ini < (int)record.size(); ini++)
				if (record[ini] == para)
					record[ini] = cans;
		}
	}
	return true;

}

// @function : 判断是否归结到终止符
bool clauseResolution::judgeAnswer(CLAUSES& c1) {
	if (c1.expressions.size() == 1)
		if (c1.expressions[0].IsNot == true)
			if (c1.expressions[0].type == ANSWER)
				if (c1.expressions[0].element.size() == 1)
					if (c1.expressions[0].element[0] >= 'A' && c1.expressions[0].element[0] <= 'Z')
						return true;
	return false;
}

// *****************************
// * @NOTICE   : 优化改进策略  *
// *****************************

// @function : EQUAL等式归结
bool clauseResolution::equalDeal(CLAUSES& c,vector<CLAUSES>& tempBag) {
	if (c.expressions.size() == 1) {
		if (c.expressions[0].IsNot == true) {
			if (c.expressions[0].type == EQUAL) {
				char ori = c.expressions[0].element[0];
				char sub = c.expressions[0].element[1];
				FUNC func;
				func.name = c.expressions[0].func.name;
				func.parameter = c.expressions[0].func.parameter;
				// 开始全局替换
				if (((ori >= 'A' && ori <= 'Z') || (ori == FUNCTION && func.parameter >= 'A' && func.parameter <= 'Z'))
					&& ((sub > 'A' && sub <= 'Z') || (ori == FUNCTION && func.parameter >= 'A' && func.parameter <= 'Z'))) {

					// clauseBag数据替换
					for (int i = 0; i < (int)clauseBag.size(); i++) {
						for (int j = 0; j < (int)clauseBag[i].expressions.size(); j++) {
							for (int k = 0; k < (int)clauseBag[i].expressions[j].element.size(); k++) {
								if (clauseBag[i].expressions[j].element[k] == ori) {
									if (ori == FUNCTION) {
										if (clauseBag[i].expressions[j].func.parameter == func.parameter) {
											clauseBag[i].expressions[j].element[k] = sub;
											clauseBag[i].expressions[j].func.name = '\0';
											clauseBag[i].expressions[j].func.parameter = '\0';
										}
									}
									else if (sub == FUNCTION) {
										clauseBag[i].expressions[j].element[k] = sub;
										clauseBag[i].expressions[j].func.name = func.name;
										clauseBag[i].expressions[j].func.parameter = func.parameter;
									}
									else {
										clauseBag[i].expressions[j].element[k] = sub;
									}
								}
							}
						}
					}

					// tempBag数据替换
					for (int i = 0; i < (int)tempBag.size(); i++) {
						for (int j = 0; j < (int)tempBag[i].expressions.size(); j++) {
							for (int k = 0; k < (int)tempBag[i].expressions[j].element.size(); k++) {
								if (tempBag[i].expressions[j].element[k] == ori) {
									if (ori == FUNCTION) {
										if (tempBag[i].expressions[j].func.parameter == func.parameter) {
											tempBag[i].expressions[j].element[k] = sub;
											tempBag[i].expressions[j].func.name = '\0';
											tempBag[i].expressions[j].func.parameter = '\0';
										}
									}
									else if (sub == FUNCTION) {
										tempBag[i].expressions[j].element[k] = sub;
										tempBag[i].expressions[j].func.name = func.name;
										tempBag[i].expressions[j].func.parameter = func.parameter;
									}
									else {
										tempBag[i].expressions[j].element[k] = sub;
									}
								}
							}
						}
					}

					return true;
				}
			}
		}
	}

	return false;

}

// @function : 包容归结函数
bool clauseResolution::containDeal(CLAUSES& c, vector<CLAUSES>& tempBag) {

	// 输入长度初始化
	int len = c.expressions.size();
	
	// 原clauseBag中是否存在包含子句
	for (int outSite = 0; outSite < (int)clauseBag.size(); outSite++) {
		if ((int)clauseBag[outSite].expressions.size() <= len) {
			vector<bool> flag((int)clauseBag[outSite].expressions.size(), false);
			for (int each = 0; each < (int)clauseBag[outSite].expressions.size(); each++) {
				for (int inSite = 0; inSite < (int)c.expressions.size(); inSite++) {
					bool flagIn = true;
					if (clauseBag[outSite].expressions[each].IsNot == c.expressions[inSite].IsNot)
						if (clauseBag[outSite].expressions[each].type == c.expressions[inSite].type)
							if (clauseBag[outSite].expressions[each].element.size() == c.expressions[inSite].element.size())
								for (int k = 0; k < (int)clauseBag[outSite].expressions[each].element.size(); k++) {
									// 均为变量
									if (clauseBag[outSite].expressions[each].element[k] >= 'A' && clauseBag[outSite].expressions[each].element[k] <= 'Z')
										if (clauseBag[outSite].expressions[each].element[k] != c.expressions[inSite].element[k]) {
											flagIn = false;
											break;
										}
									// 均为常量
									if (clauseBag[outSite].expressions[each].element[k] >= 'a' && clauseBag[outSite].expressions[each].element[k] <= 'z')
										if (!(c.expressions[inSite].element[k] >= 'a' && c.expressions[inSite].element[k] <= 'z')) {
											flagIn = false;
											break;
										}
									// 均为函数
									if (clauseBag[outSite].expressions[each].element[k] == FUNCTION)
										if (c.expressions[inSite].element[k] != FUNCTION) {
											flagIn = false;
											break;
										}
										else if (clauseBag[outSite].expressions[each].func.parameter >= 'A' && clauseBag[outSite].expressions[each].func.parameter >= 'Z') {
											if (c.expressions[inSite].func.parameter != clauseBag[outSite].expressions[each].func.parameter) {
												flagIn = false;
												break;
											}
										}
										else if (clauseBag[outSite].expressions[each].func.parameter >= 'a' && clauseBag[outSite].expressions[each].func.parameter >= 'z') {
											if (!(c.expressions[inSite].func.parameter >= 'a' && c.expressions[inSite].func.parameter <= 'z')) {
												flagIn = false;
												break;
											}
										}
								}
							else
								flagIn = false;
						else
							flagIn = false;
					else
						flagIn = false;

					// 判断是否存在一致的表达式
					if (flagIn) {
						flag[each] = flagIn;
						break;
					}
				}
			}
			bool getAns = true;
			for (int i = 0; i < (int)flag.size(); i++)
				if (!flag[i]) {
					getAns = false;
					break;
				}
			if (getAns)
				return true;// 全部存在一致的表达式
		}
	}

	// tempBag中是否存在包含子句
	for (int outSite = 0; outSite < (int)tempBag.size(); outSite++) {
		if ((int)tempBag[outSite].expressions.size() <= len) {
			vector<bool> flag((int)tempBag[outSite].expressions.size(), false);
			for (int each = 0; each < (int)tempBag[outSite].expressions.size(); each++) {
				for (int inSite = 0; inSite < (int)c.expressions.size(); inSite++) {
					bool flagIn = true;
					if (tempBag[outSite].expressions[each].IsNot == c.expressions[inSite].IsNot)
						if (tempBag[outSite].expressions[each].type == c.expressions[inSite].type)
							if (tempBag[outSite].expressions[each].element.size() == c.expressions[inSite].element.size())
								for (int k = 0; k < (int)tempBag[outSite].expressions[each].element.size(); k++) {
									// 均为常量
									if (tempBag[outSite].expressions[each].element[k] >= 'A' && tempBag[outSite].expressions[each].element[k] <= 'Z')
										if (tempBag[outSite].expressions[each].element[k] != c.expressions[inSite].element[k]) {
											flagIn = false;
											break;
										}
									// 均为变量
									if (tempBag[outSite].expressions[each].element[k] >= 'a' && tempBag[outSite].expressions[each].element[k] <= 'z')
										if (!(c.expressions[inSite].element[k] >= 'a' && c.expressions[inSite].element[k] <= 'z')) {
											flagIn = false;
											break;
										}
									// 均为函数
									if (tempBag[outSite].expressions[each].element[k] == FUNCTION)
										if (c.expressions[inSite].element[k] != FUNCTION) {
											flagIn = false;
											break;
										}
										else if (tempBag[outSite].expressions[each].func.parameter >= 'A' && tempBag[outSite].expressions[each].func.parameter >= 'Z') {
											if (c.expressions[inSite].func.parameter != tempBag[outSite].expressions[each].func.parameter) {
												flagIn = false;
												break;
											}
										}
										else if (tempBag[outSite].expressions[each].func.parameter >= 'a' && tempBag[outSite].expressions[each].func.parameter >= 'z') {
											if (!(c.expressions[inSite].func.parameter >= 'a' && c.expressions[inSite].func.parameter <= 'z')) {
												flagIn = false;
												break;
											}
										}
								}
							else
								flagIn = false;
						else
							flagIn = false;
					else
						flagIn = false;

					// 判断是否存在一致的表达式
					if (flagIn) {
						flag[each] = flagIn;
						break;
					}
				}
			}
			bool getAns = true;
			for (int i = 0; i < (int)flag.size(); i++)
				if (!flag[i]) {
					getAns = false;
					break;
				}
			if (getAns)
				return true;// 全部存在一致的表达式
		}
	}

	return false;

}

// @function : 长度限制归结
bool clauseResolution::lengthDeal(CLAUSES& c, vector<CLAUSES>& tempBag) {
	if ((int)c.expressions.size() > LENGTHEDGE)
		return true;
	return false;
}

// @function : 子句归结
void clauseResolution::resolution(void) {

	//initialShow(); // 展示输入读取数据 for test
	initialRecord(); // 初始输入数据存储
	int lastSite = 0;

	while (true) {

		// 遍历初始化
		int len = clauseBag.size();
		vector<CLAUSES>clauseTempBag;

		// 在现有的clauseBag内两两配对计算
		for (int i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				if (j >= lastSite) {
					CLAUSES ansClause;       // 归结结果
					vector<char> record;     // 过程记录
					if (twoClauseResolu(clauseBag[i], clauseBag[j], ansClause, record)) {

						vector<char>upData;  // 更迭过程存储
						RECORD temp;         // 结果存储

						// 新子句更新
						clausesUpdate(ansClause, record, upData);

						// 存储更迭结果
						processRecord(clauseBag[i], clauseBag[j], ansClause, upData, temp);

						// 判断是否得到结果
						if (judgeAnswer(ansClause)) {

							// 得到最终结果
							answer = ansClause;

							// 显示本次更迭
							//processShow(clauseBag[i], clauseBag[j], ansClause, upData);     // for test

							// 数据结果存储
							clauseTempBag.push_back(ansClause);
							for (int i = 0; i < (int)clauseTempBag.size(); i++)
								clauseBag.push_back(clauseTempBag[i]);

							// 流程记录的添加
							recordList.push_back(temp);

							// 显示最终结果
							//cout << "answer:" << answer.expressions[0].element[0] << endl;  // for test
							//tempShow();

							return;
						}
						// 包含归结
						else if (containDeal(ansClause, clauseTempBag))
						    --countNum;
						// 长度限制
						else if (lengthDeal(ansClause, clauseTempBag))
							--countNum;
						// 等式归结
						else if (equalDeal(ansClause, clauseTempBag)) {
							// 过程记录添加
							recordList.push_back(temp);
						}
						// 子句更迭
						else {
							// 流程记录的添加
							recordList.push_back(temp);

							// 新子句添加
							clauseTempBag.push_back(ansClause);

							// 显示本次更迭
							//processShow(clauseBag[i], clauseBag[j], ansClause, upData);// for test
						}
					}
				}
			}
		}
		lastSite = len;// 记录上次长度 避免重复计算

		// 加入归结产生的新子句
		for (int i = 0; i < (int)clauseTempBag.size(); i++)
			clauseBag.push_back(clauseTempBag[i]);
	}
}

// @function : 回溯最优解的过程
void clauseResolution::traceBack(void) {
	string lastName = answer.name;

	for (int i = 0; i < (int)recordList.size(); i++)
		if (recordList[i].resultName == answer.name)
			traceBackIn(recordList[i]);
	return;
}

// @function : 寻找最优解的回溯函数
void clauseResolution::traceBackIn(RECORD& c) {

	// father1_get
	for (int i = 0; i < (int)recordList.size(); i++) {
		if (recordList[i].resultName == c.father1Name)
			traceBackIn(recordList[i]);
	}
    // father2_get
	for (int i = 0; i < (int)recordList.size(); i++) {
		if (recordList[i].resultName == c.father2Name)
			traceBackIn(recordList[i]);
	}
	// ans_get
	for (int i = 0; i < (int)recordList.size(); i++) {
		if (recordList[i].resultName == c.resultName)
			bestPath.push_back(recordList[i]);
	}
	return;
}

// @function : 记录起始过程
void clauseResolution::initialRecord(void) {
	for (int outerI = 0; outerI < (int)clauseBag.size(); outerI++) {
		RECORD temp;
		temp.change = "";
		temp.father1Name = "";
		temp.father2Name = "";

		temp.resultName = clauseBag[outerI].name;
		temp.result = "";

		for (int i = 0; i < (int)clauseBag[outerI].expressions.size(); i++) {
			if (clauseBag[outerI].expressions[i].IsNot == false)
				temp.result += "~";
			temp.result += clauseBag[outerI].expressions[i].type;
			temp.result += "(";
			for (int j = 0; j < (int)clauseBag[outerI].expressions[i].element.size(); j++) {
				if (clauseBag[outerI].expressions[i].element[j] != FUNCTION)
					temp.result += clauseBag[outerI].expressions[i].element[j];
				else
					temp.result = temp.result + clauseBag[outerI].expressions[i].func.name + "(" + clauseBag[outerI].expressions[i].func.parameter + ")";
				if (j != (int)clauseBag[outerI].expressions[i].element.size() - 1)
					temp.result += ",";
			}
			temp.result += ")";

			if (i != (int)clauseBag[outerI].expressions.size() - 1)
				temp.result += "|";
		}

		initialList.push_back(temp);
	}
	return;
}

// @function : 记录存储过程
void clauseResolution::processRecord(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& upData, RECORD& get) {
	
	// 存储结果表达式
	get.resultName = ans.name;
	get.result = "";
	for (int i = 0; i < (int)ans.expressions.size(); i++) {
		if (ans.expressions[i].IsNot == false)
			get.result+= "~";
		get.result += ans.expressions[i].type;
		get.result += "(";
		for (int j = 0; j < (int)ans.expressions[i].element.size(); j++) {
			if (ans.expressions[i].element[j] != FUNCTION)
				get.result += ans.expressions[i].element[j];
			else
				get.result =  get.result + ans.expressions[i].func.name + "(" + ans.expressions[i].func.parameter + ")";
			if (j != (int)ans.expressions[i].element.size() - 1)
				get.result += ",";
		}
		get.result += ")";

		if (i != (int)ans.expressions.size() - 1)
			get.result += "|";
	}

	// 存储递归来源
	get.father1Name = c1.name;
	get.father2Name = c2.name;

	// 存储递归替换
	get.change = "";
	for (int i = 0; i < (int)upData.size();) {
		if (upData[i] != FUNCTION) {
			get.change+= upData[i];
			i += 1;
		}
		else {
			get.change = get.change + upData[i + 1] + "(" + upData[i + 2] + ")";
			i += 3;
		}
		get.change += "-->";
		if (upData[i] != FUNCTION) {
			get.change += upData[i];
			i += 1;
		}
		else {
			get.change = get.change + upData[i + 1] + "(" + upData[i + 2] + ")";
			i += 3;
		}
		if (i < (int)upData.size() - 1)
			get.change += ";";
	}

	return;
}

// @function : 显示归结过程
void clauseResolution::allShow(void) {
	// 原始逻辑显示
	for (int i = 0; i < (int)initialList.size(); i++) {
		cout << left << setw(8)<< initialList[i].resultName;
		cout << left << setw(30) << initialList[i].result << endl;
	}
	// 归结过程显示
	for (int i = 0; i < (int)recordList.size(); i++) {
		cout << left << setw(8) << recordList[i].resultName;
		cout << left << setw(30) << recordList[i].result;
		cout << left << setw(15) << recordList[i].father1Name + '+' + recordList[i].father2Name;
		cout << left << setw(15) << recordList[i].change << endl;
	}
	return;
}

// @function : 显示最优归结
void clauseResolution::bestShow(void) {
	// 原始逻辑显示
	for (int i = 0; i < (int)initialList.size(); i++) {
		cout << left << setw(8) << initialList[i].resultName;
		cout << left << setw(30) << initialList[i].result << endl;
	}
	// 归结过程显示
	for (int i = 0; i < (int)bestPath.size(); i++) {
		cout << left << setw(8) << bestPath[i].resultName;
		cout << left << setw(30) << bestPath[i].result;
		cout << left << setw(15) << bestPath[i].father1Name + '+' + bestPath[i].father2Name;
		cout << left << setw(15) << bestPath[i].change << endl;
	}
	return;
}

// @function : 显示推断结果
void clauseResolution::ansShow(void) {
	cout << "谋杀A的人是:" << answer.expressions[0].element[0] << endl;
	return;
}


// -----------------------------
// | @NOTICE   : 以下用于测试  |
// -----------------------------
// @function : 打印归结过程
void clauseResolution::processShow(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& upData) {

	// 表达式显示
	cout << ans.name << " : ";
	for (int i = 0;i < (int)ans.expressions.size(); i++) {
		if (ans.expressions[i].IsNot == false)
			cout << "~";
		cout << ans.expressions[i].type;
		cout << "(";
		for (int j = 0; j < (int)ans.expressions[i].element.size(); j++) {
			if (ans.expressions[i].element[j] != FUNCTION)
				cout << ans.expressions[i].element[j];
			else
				cout << ans.expressions[i].func.name << "(" << ans.expressions[i].func.parameter << ")";
			if (j != (int)ans.expressions[i].element.size() - 1)
				cout << ",";
		}
		cout << ")";

		if (i != (int)ans.expressions.size() - 1)
			cout << "|";
	}

	// 显示递归来源
	cout << "   ";
	cout << "{{" << c1.name << "与" << c2.name << "归结";
	if (upData.size() != 0)
		cout << " 且 ";
	for (int i = 0; i < (int)upData.size();) {
		if (upData[i] != FUNCTION) {
			cout << upData[i];
			i += 1;
		}
		else {
			cout << upData[i + 1] << "(" << upData[i + 2] << ")";
			i += 3;
		}
		cout << "-->";
		if (upData[i] != FUNCTION) {
			cout << upData[i];
			i += 1;
		}
		else {
			cout << upData[i + 1] << "(" << upData[i + 2] << ")";
			i += 3;
		}
		if (i < (int)upData.size() - 1)
			cout << ";";
	}
	cout << "}}" << endl;

	return;
}
// @function : 打印初始逻辑
void clauseResolution::initialShow(void) {

	for (int outerI = 0; outerI < (int)clauseBag.size(); outerI++) {
		cout << clauseBag[outerI].name << " : ";
		for (int i = 0; i < (int)clauseBag[outerI].expressions.size(); i++) {
			if (clauseBag[outerI].expressions[i].IsNot == false)
				cout << "~";
			cout << clauseBag[outerI].expressions[i].type;
			cout << "(";
			for (int j = 0; j < (int)clauseBag[outerI].expressions[i].element.size(); j++) {
				if (clauseBag[outerI].expressions[i].element[j] != FUNCTION)
					cout << clauseBag[outerI].expressions[i].element[j];
				else
					cout << clauseBag[outerI].expressions[i].func.name << "(" << clauseBag[outerI].expressions[i].func.parameter << ")";
				if (j != (int)clauseBag[outerI].expressions[i].element.size() - 1)
					cout << ",";
			}
			cout << ")";

			if (i != (int)clauseBag[outerI].expressions.size() - 1)
				cout << "|";
		}

		cout << endl;
	}
	return;
}
// @function : 临时展示clauseBag数据 --> for test
void clauseResolution::tempShow(void) {
	//for (int i = 0; i < (int)clauseBag.size(); i++) {

	//	// 输出子句名
	//	cout << clauseBag[i].name<<"--";

	//	// 输出子句中间步骤
	//	for (int j = 0; j < (int)clauseBag[i].expressions.size(); j++) {
	//		cout << clauseBag[i].expressions[j].IsNot << '-';
	//		cout << clauseBag[i].expressions[j].type << '-';
	//		for (int k = 0; k < (int)clauseBag[i].expressions[j].element.size(); k++) {
	//			if (clauseBag[i].expressions[j].element[k] != FUNCTION)
	//				cout << clauseBag[i].expressions[j].element[k] << '-';
	//			else
	//				cout << clauseBag[i].expressions[j].func.name << "(" << clauseBag[i].expressions[j].func.parameter << ")";
	//		}

	//		cout << "***";
	//	}
	//	cout << endl;
	//}

	//// all record for test
	//for (int i = 0; i < (int)initialList.size(); i++) {
	//	cout << initialList[i].resultName << " " << initialList[i].result << endl;
	//}
	//for (int i = 0; i < (int)recordList.size(); i++) {
	//	cout << recordList[i].resultName << ":" << recordList[i].result << "***";
	//	cout << recordList[i].father1Name << "-" << recordList[i].father2Name << "***" << recordList[i].change << endl;
	//}

	// best record show
	//for (int i = 0; i < (int)bestPath.size(); i++) {
	//	cout << bestPath[i].resultName << ":" << bestPath[i].result << "***";
	//	cout << bestPath[i].father1Name << "-" << bestPath[i].father2Name << "***" << bestPath[i].change << endl;
	//}

	return;
}



/*****************************************************************************************/
/***************************************工具函数******************************************/
/*****************************************************************************************/

// @function : 读取数据
void dataIn(vector<string>& originalSentence) {
	string dataIn;
	while (true) {
		cin >> dataIn;
		if (dataIn == "#")
			break;
		else
			originalSentence.push_back(dataIn);
	}
	return;

}

