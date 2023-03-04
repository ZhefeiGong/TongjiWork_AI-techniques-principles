/*
 * @author   : gonzalez
 * @time     : 2022.5.26-2022.6.2
 * @function :
 */

#include"logicalReasoning_head.h"
using namespace std;


/*****************************************************************************************/
/******************************һ���߼�����ڲ����ĺ���***********************************/
/*****************************************************************************************/

// @function : ���ʽ�Ӿ仮��
void clauseResolution::expressionInput(string& original, CLAUSES& c) {

	// ���ʽ����
	EXPRE expression;

	// �ж�����
	string getString = original;
	int st = 0;
	if (getString[0] == NOT) {
		expression.IsNot = false;
		st = 1;
	}
	else
		expression.IsNot = true;

	// ���ʽ���������
	bool hadFlag = false;
	for (int i = 0; i < (int)expressionType.size(); i++)
		if (expressionType[i] == getString[st]) {
			hadFlag = true;
			break;
		}
	if (!hadFlag)
		expressionType.push_back(getString[st]);
	expression.type = getString[st];

	// �˺������'(exprenssion)'
	++st;
	getString = getString.substr(st);

	// �ж��ڲ�����
	int num = count(getString.begin(), getString.end(), DOT);
	// ���ʽ�������ַ�
	if (num != 0) {

		// ��ʼ��
		int site = getString.find(DOT);
		string frontString = getString;
		frontString.erase(site);
		string backString = getString.substr(site + 1);
		
		// �ж�ǰ�벿
		if (count(frontString.begin(), frontString.end(), RIGHTBRACKET)) {     // ��������
			expression.element.push_back(FUNCTION);
			expression.func.name = *(frontString.begin() + 1);
			expression.func.parameter = *(frontString.begin() + 1 + 1 + 1);
		}
		else {
			char front = frontString[frontString.size() - 1];
			expression.element.push_back(front);
		}

		// �жϺ�벿
		if (count(backString.begin(), backString.end(), LEFTBRACKET)) {        // ��������
			expression.element.push_back(FUNCTION);
			expression.func.name = *(backString.begin());
			expression.func.parameter = *(backString.begin() + 1 + 1);
		}
		else {
			char back = backString[0];
			expression.element.push_back(back);
		}


	}
	// ���ʽ�ڽ�һ���ַ�
	else {
		// �ж��Ƿ�Ϊ����
		if (count(getString.begin(), getString.end(), RIGHTBRACKET) == 2) {    // ��������
			expression.element.push_back(FUNCTION);
			expression.func.name = *(getString.begin() + 1);
			expression.func.parameter = *(getString.begin() + 1 + 1 + 1);
		}
		// �жϳ��������
		else {
			char val = getString[1];
			expression.element.push_back(val);
		}
	}

	// ��Ӷ�Ӧ�Ӿ�
	c.expressions.push_back(expression);

	return;
}

// @function : �����ַ���ת�����Ӿ�
void clauseResolution::clausInput(vector<string>& originalSentence){

	int len = originalSentence.size();
	for (int i = 0; i < len; i++) {
		CLAUSES c;                                // �Ӿ��ȡ
		string temp = originalSentence[i];
		int num = count(temp.begin(), temp.end(), OR);
		for (int i = 0; i <= num; i++) {
			if (i == num)
				expressionInput(temp,c);
			else {
				int site = temp.find(OR);
				string subTemp = temp;
				subTemp.erase(site);
				temp = temp.substr(site + 1);     // ɾȥ��Ӧ��'|'
				expressionInput(subTemp,c);
			}
		}
		c.name = "c" + to_string(i + 1);          // �Ӿ����ָ�ֵ
		clauseBag.push_back(c);                   // ����Ӿ�
	}
	return;
}

// @function : �����Ӿ���й��
bool clauseResolution::twoClauseResolu(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& record) {

	bool flag = false;
	for (int c1i = 0; c1i < (int)c1.expressions.size(); c1i++) {
		for (int c2j = 0; c2j < (int)c2.expressions.size(); c2j++) {
			flag = true;
			if (c1.expressions[c1i].type == c2.expressions[c2j].type) {                                   // ���ʽ����һ��
				if (c1.expressions[c1i].IsNot != c2.expressions[c2j].IsNot) {                             // ���ʽ�����෴
					if (c1.expressions[c1i].element.size() == c2.expressions[c2j].element.size()) {       // ��������һ��
						vector<char> recordTemp;                                                          // ��ʱ���й��洢
						// �жϾ�������Ƿ��ܺ�һ�û�
						for (int k = 0; k < (int)c1.expressions[c1i].element.size(); k++) {
							//// Ϊ���ں��������
							//if(c1.expressions[c1i].element[k]==FUNCTION)
							//	if (c1.expressions[c1i].func.parameter >= 'A' && c1.expressions[c1i].func.parameter <= 'Z')
							//		if (c2.expressions[c2j].element[k] >= 'A' && c2.expressions[c2j].element[k] <= 'Z') {
							//			flag = false;                                                     // ���ɽ��й��
							//			break;
							//		}
							//if (c2.expressions[c1i].element[k] == FUNCTION)
							//	if (c2.expressions[c1i].func.parameter >= 'A' && c2.expressions[c1i].func.parameter <= 'Z')
							//		if (c1.expressions[c2j].element[k] >= 'A' && c1.expressions[c2j].element[k] <= 'Z') {
							//			flag = false;                                                     // ���ɽ��й��
							//			break;
							//		}
							//// ��Ϊ����
							//if ((c1.expressions[c1i].element[k] >= 'A' && c1.expressions[c1i].element[k] <= 'Z') &&
							//	(c2.expressions[c2j].element[k] >= 'A' && c2.expressions[c2j].element[k] <= 'Z')) {
							//	if (c1.expressions[c1i].element[k] != c2.expressions[c2j].element[k]) {
							//		flag = false;                                                         // ���ɽ��й��
							//		break;
							//	}
							//}
							
							// ����һ������||�����������  -->  �ɹ��
							if ((c1.expressions[c1i].element[k] >= 'a' && c1.expressions[c1i].element[k] < 'z') ||
								(c2.expressions[c2j].element[k] >= 'a' && c2.expressions[c2j].element[k] < 'z') ||
								(c1.expressions[c1i].element[k] == c2.expressions[c2j].element[k]))
								flag = true;
							else {
								flag = false;
								break;
							}
							recordTemp.push_back(c1.expressions[c1i].element[k]);// ������ͳ��
							if (c1.expressions[c1i].element[k] == FUNCTION) {
								recordTemp.push_back(c1.expressions[c1i].func.name);
								recordTemp.push_back(c1.expressions[c1i].func.parameter);
							}
							recordTemp.push_back(c2.expressions[c2j].element[k]);// ������ͳ��
							if (c2.expressions[c2j].element[k] == FUNCTION) {
								recordTemp.push_back(c2.expressions[c2j].func.name);
								recordTemp.push_back(c2.expressions[c2j].func.parameter);
							}
						}
						// ���й��
						if (flag) {
							// ���Ӿ�����
							ans.name = "T" + to_string(++countNum);

							// ���ԭ���Ӿ�
							for (int tempi = 0; tempi < (int)c1.expressions.size(); tempi++) {
								if (tempi != c1i)
									ans.expressions.push_back(c1.expressions[tempi]);
							}
							// ���ԭ���Ӿ�
							for (int tempj = 0; tempj < (int)c2.expressions.size(); tempj++) {
								if (tempj != c2j)
									ans.expressions.push_back(c2.expressions[tempj]);
							}
							// ��һ�û���ʽ���
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

// @function : ���Ӿ��ʶ������
bool clauseResolution::clausesUpdate(CLAUSES& ans, vector<char>& record, vector<char>& upData) {

	for (int i = 0; i < (int)record.size();) {

		// ����������ȡ
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
		
		// ��ʱ�����滻���-->��1����/1����/1���� ���� 1����
		if ((get1[0] >= 'a' && get1[0] <= 'z') || (get2[0] >= 'a' && get2[0] <= 'z')) {

			// ȷ���滻��ͱ��滻��
			char cans, para;
			if ((get1[0] >= 'a' && get1[0] <= 'z')) {
				para = get1[0];
				cans = get2[0];
			}
			else {
				para = get2[0];
				cans = get1[0];
			}

			// �仯����ͬ������
			for (int ini = 0; ini < (int)upData.size(); ini++)
				if (upData[ini] == para)
					upData[ini] = cans;

			// upData����׷��
			upData.push_back(para);//���滻����
			upData.push_back(cans);//���滻����
			// ��������׷��
			FUNC temp = { '\0','\0' };
			if (get1[0] == FUNCTION) {
				upData.push_back(get1[1]);//��������
				temp.name = get1[1];
				upData.push_back(get1[2]);//��������
				temp.parameter = get1[2];
			}
			else if (get2[0] == FUNCTION) {
				upData.push_back(get2[1]);//��������
				temp.name = get2[1];
				upData.push_back(get2[2]);//��������
				temp.parameter = get2[2];
			}

			// ��ʼ���µ�ǰ���Ӿ���Ϣ
			for (int i = 0; i < (int)ans.expressions.size(); i++) {
				for (int j = 0; j < (int)ans.expressions[i].element.size(); j++) {
					// ��������
					if (para == ans.expressions[i].element[j]) {
						ans.expressions[i].element[j] = cans;
						ans.expressions[i].func.name = temp.name;
						ans.expressions[i].func.parameter = temp.parameter;
					}
					// ������������
					if (para == ans.expressions[i].func.parameter)
						ans.expressions[i].func.parameter = cans;
				}
			}

			// �仯����ͬ������
			for (int ini = i; ini < (int)record.size(); ini++)
				if (record[ini] == para)
					record[ini] = cans;
		}
	}
	return true;

}

// @function : �ж��Ƿ��ᵽ��ֹ��
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
// * @NOTICE   : �Ż��Ľ�����  *
// *****************************

// @function : EQUAL��ʽ���
bool clauseResolution::equalDeal(CLAUSES& c,vector<CLAUSES>& tempBag) {
	if (c.expressions.size() == 1) {
		if (c.expressions[0].IsNot == true) {
			if (c.expressions[0].type == EQUAL) {
				char ori = c.expressions[0].element[0];
				char sub = c.expressions[0].element[1];
				FUNC func;
				func.name = c.expressions[0].func.name;
				func.parameter = c.expressions[0].func.parameter;
				// ��ʼȫ���滻
				if (((ori >= 'A' && ori <= 'Z') || (ori == FUNCTION && func.parameter >= 'A' && func.parameter <= 'Z'))
					&& ((sub > 'A' && sub <= 'Z') || (ori == FUNCTION && func.parameter >= 'A' && func.parameter <= 'Z'))) {

					// clauseBag�����滻
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

					// tempBag�����滻
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

// @function : ���ݹ�ắ��
bool clauseResolution::containDeal(CLAUSES& c, vector<CLAUSES>& tempBag) {

	// ���볤�ȳ�ʼ��
	int len = c.expressions.size();
	
	// ԭclauseBag���Ƿ���ڰ����Ӿ�
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
									// ��Ϊ����
									if (clauseBag[outSite].expressions[each].element[k] >= 'A' && clauseBag[outSite].expressions[each].element[k] <= 'Z')
										if (clauseBag[outSite].expressions[each].element[k] != c.expressions[inSite].element[k]) {
											flagIn = false;
											break;
										}
									// ��Ϊ����
									if (clauseBag[outSite].expressions[each].element[k] >= 'a' && clauseBag[outSite].expressions[each].element[k] <= 'z')
										if (!(c.expressions[inSite].element[k] >= 'a' && c.expressions[inSite].element[k] <= 'z')) {
											flagIn = false;
											break;
										}
									// ��Ϊ����
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

					// �ж��Ƿ����һ�µı��ʽ
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
				return true;// ȫ������һ�µı��ʽ
		}
	}

	// tempBag���Ƿ���ڰ����Ӿ�
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
									// ��Ϊ����
									if (tempBag[outSite].expressions[each].element[k] >= 'A' && tempBag[outSite].expressions[each].element[k] <= 'Z')
										if (tempBag[outSite].expressions[each].element[k] != c.expressions[inSite].element[k]) {
											flagIn = false;
											break;
										}
									// ��Ϊ����
									if (tempBag[outSite].expressions[each].element[k] >= 'a' && tempBag[outSite].expressions[each].element[k] <= 'z')
										if (!(c.expressions[inSite].element[k] >= 'a' && c.expressions[inSite].element[k] <= 'z')) {
											flagIn = false;
											break;
										}
									// ��Ϊ����
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

					// �ж��Ƿ����һ�µı��ʽ
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
				return true;// ȫ������һ�µı��ʽ
		}
	}

	return false;

}

// @function : �������ƹ��
bool clauseResolution::lengthDeal(CLAUSES& c, vector<CLAUSES>& tempBag) {
	if ((int)c.expressions.size() > LENGTHEDGE)
		return true;
	return false;
}

// @function : �Ӿ���
void clauseResolution::resolution(void) {

	//initialShow(); // չʾ�����ȡ���� for test
	initialRecord(); // ��ʼ�������ݴ洢
	int lastSite = 0;

	while (true) {

		// ������ʼ��
		int len = clauseBag.size();
		vector<CLAUSES>clauseTempBag;

		// �����е�clauseBag��������Լ���
		for (int i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				if (j >= lastSite) {
					CLAUSES ansClause;       // �����
					vector<char> record;     // ���̼�¼
					if (twoClauseResolu(clauseBag[i], clauseBag[j], ansClause, record)) {

						vector<char>upData;  // �������̴洢
						RECORD temp;         // ����洢

						// ���Ӿ����
						clausesUpdate(ansClause, record, upData);

						// �洢�������
						processRecord(clauseBag[i], clauseBag[j], ansClause, upData, temp);

						// �ж��Ƿ�õ����
						if (judgeAnswer(ansClause)) {

							// �õ����ս��
							answer = ansClause;

							// ��ʾ���θ���
							//processShow(clauseBag[i], clauseBag[j], ansClause, upData);     // for test

							// ���ݽ���洢
							clauseTempBag.push_back(ansClause);
							for (int i = 0; i < (int)clauseTempBag.size(); i++)
								clauseBag.push_back(clauseTempBag[i]);

							// ���̼�¼�����
							recordList.push_back(temp);

							// ��ʾ���ս��
							//cout << "answer:" << answer.expressions[0].element[0] << endl;  // for test
							//tempShow();

							return;
						}
						// �������
						else if (containDeal(ansClause, clauseTempBag))
						    --countNum;
						// ��������
						else if (lengthDeal(ansClause, clauseTempBag))
							--countNum;
						// ��ʽ���
						else if (equalDeal(ansClause, clauseTempBag)) {
							// ���̼�¼���
							recordList.push_back(temp);
						}
						// �Ӿ����
						else {
							// ���̼�¼�����
							recordList.push_back(temp);

							// ���Ӿ����
							clauseTempBag.push_back(ansClause);

							// ��ʾ���θ���
							//processShow(clauseBag[i], clauseBag[j], ansClause, upData);// for test
						}
					}
				}
			}
		}
		lastSite = len;// ��¼�ϴγ��� �����ظ�����

		// ��������������Ӿ�
		for (int i = 0; i < (int)clauseTempBag.size(); i++)
			clauseBag.push_back(clauseTempBag[i]);
	}
}

// @function : �������Ž�Ĺ���
void clauseResolution::traceBack(void) {
	string lastName = answer.name;

	for (int i = 0; i < (int)recordList.size(); i++)
		if (recordList[i].resultName == answer.name)
			traceBackIn(recordList[i]);
	return;
}

// @function : Ѱ�����Ž�Ļ��ݺ���
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

// @function : ��¼��ʼ����
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

// @function : ��¼�洢����
void clauseResolution::processRecord(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& upData, RECORD& get) {
	
	// �洢������ʽ
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

	// �洢�ݹ���Դ
	get.father1Name = c1.name;
	get.father2Name = c2.name;

	// �洢�ݹ��滻
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

// @function : ��ʾ������
void clauseResolution::allShow(void) {
	// ԭʼ�߼���ʾ
	for (int i = 0; i < (int)initialList.size(); i++) {
		cout << left << setw(8)<< initialList[i].resultName;
		cout << left << setw(30) << initialList[i].result << endl;
	}
	// ��������ʾ
	for (int i = 0; i < (int)recordList.size(); i++) {
		cout << left << setw(8) << recordList[i].resultName;
		cout << left << setw(30) << recordList[i].result;
		cout << left << setw(15) << recordList[i].father1Name + '+' + recordList[i].father2Name;
		cout << left << setw(15) << recordList[i].change << endl;
	}
	return;
}

// @function : ��ʾ���Ź��
void clauseResolution::bestShow(void) {
	// ԭʼ�߼���ʾ
	for (int i = 0; i < (int)initialList.size(); i++) {
		cout << left << setw(8) << initialList[i].resultName;
		cout << left << setw(30) << initialList[i].result << endl;
	}
	// ��������ʾ
	for (int i = 0; i < (int)bestPath.size(); i++) {
		cout << left << setw(8) << bestPath[i].resultName;
		cout << left << setw(30) << bestPath[i].result;
		cout << left << setw(15) << bestPath[i].father1Name + '+' + bestPath[i].father2Name;
		cout << left << setw(15) << bestPath[i].change << endl;
	}
	return;
}

// @function : ��ʾ�ƶϽ��
void clauseResolution::ansShow(void) {
	cout << "ıɱA������:" << answer.expressions[0].element[0] << endl;
	return;
}


// -----------------------------
// | @NOTICE   : �������ڲ���  |
// -----------------------------
// @function : ��ӡ������
void clauseResolution::processShow(CLAUSES& c1, CLAUSES& c2, CLAUSES& ans, vector<char>& upData) {

	// ���ʽ��ʾ
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

	// ��ʾ�ݹ���Դ
	cout << "   ";
	cout << "{{" << c1.name << "��" << c2.name << "���";
	if (upData.size() != 0)
		cout << " �� ";
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
// @function : ��ӡ��ʼ�߼�
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
// @function : ��ʱչʾclauseBag���� --> for test
void clauseResolution::tempShow(void) {
	//for (int i = 0; i < (int)clauseBag.size(); i++) {

	//	// ����Ӿ���
	//	cout << clauseBag[i].name<<"--";

	//	// ����Ӿ��м䲽��
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
/***************************************���ߺ���******************************************/
/*****************************************************************************************/

// @function : ��ȡ����
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

