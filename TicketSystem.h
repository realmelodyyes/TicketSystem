#ifndef TICKETSYSTEM_H
#define TICKETSYSTEM_H

#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>  
#include <algorithm> 
#include <ctime>     

using namespace std;
const int MAX_TICKET_NUM = 300;  // 最大编号


class TicketSystem {
private:
    deque<int> waitQueue;       // 双端队列
    vector<string> saleLog;     // 记录日志

	int soldCountMin;           // 最小编号窗口销量
	int soldCountMax;           // 最大编号窗口销量

    void addLog(string record); // 添加日志

public:
    TicketSystem();

	string getLastLog();   // 获取最新一条日志
    void initQueue(int n); // 初始化队列
    bool serveMin();       // 最小编号购票
	bool serveMax();       // 最大编号购票

	bool isEmpty();        // 判断是否队空
	int getQueueSize();    // 获取队列大小
	void printQueueStatus();  // 打印队列状态
	void autoSimulate(int instructionCount);  // 自动模拟
	void showStatistics();    // 显示销售统计报表

	void saveToFile(string filename);  // 保存记录到文件
	void queryTicket(int num); // 查找指定编号
};

#endif