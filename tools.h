#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// 安全输入整数
int safeInputInt(string tip, int min, int max) {
	int num;
	while (true) {
		cout << tip;

		// 尝试读取一个整数
		if (cin >> num) {
			// 检查缓冲区下一个字符是否为 换行符、空格、制表符或结束符
			char nextChar = cin.peek();
			if (nextChar != '\n' && nextChar != ' ' && nextChar != '\t' && nextChar != EOF) {
				cout << " >>> 输入错误，请输入整数（不能包含小数或字母）！" << endl;
				cin.clear(); // 重置输入流状态
				cin.ignore(1000, '\n'); // 清除缓冲区
				continue;
			}
			// 检查范围
			if (num < min || num > max) {
				cout << " >>> 输入错误，范围应在 " << min << "~" << max << " 之间！" << endl;
				cin.ignore(1000, '\n'); // 清除回车符
			}
			// 输入合法
			else {
				cin.ignore(1000, '\n');
				return num;
			}
		}
		// 未读取到数字
		else {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " >>> 输入错误，请输入整数（不能包含小数或字母）！" << endl;
		}
	}
}

// 按回车键返回
void pressEnterToReturn() {
	cout << " 按回车键返回主菜单...";
	cin.clear(); // 清除可能存在的错误状态
	string words;
	getline(cin, words);
}

#endif