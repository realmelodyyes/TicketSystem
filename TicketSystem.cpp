#include "TicketSystem.h"
#include <cstdlib>   
#include <iomanip> 

// 构造函数
TicketSystem::TicketSystem() {
	soldCountMin = 0;
	soldCountMax = 0;
	// 初始化随机数种子
	srand((unsigned)time(NULL));
}

// 添加日志 
void TicketSystem::addLog(string record) {
	saleLog.push_back(record);
}

// 获取最新一条日志
string TicketSystem::getLastLog() {
	if (saleLog.empty()) {
		return "系统已启动";
	}
	return saleLog.back();
}

// 初始化队列
void TicketSystem::initQueue(int n) {
	if (n > MAX_TICKET_NUM) {
		n = MAX_TICKET_NUM;
		addLog("Warning: 排队人数超过最大编号限制，已截断为 " + to_string(n) + " 人。");
	}

	// 重置状态
	waitQueue.clear();
	saleLog.clear();
	soldCountMin = 0;
	soldCountMax = 0;

	// 生成票数量的编号
	vector<int> number;
	for (int i = 1; i <= MAX_TICKET_NUM; i++) {
		number.push_back(i);
	}

	// 打乱编号顺序
	random_shuffle(number.begin(), number.end());

	// 取前 n 个编号给排队的人
	vector<int> temp;
	for (int i = 0; i < n; i++) {
		temp.push_back(number[i]);
	}

	// 重新排序有效编号
	sort(temp.begin(), temp.end());

	// 将有序编号转入双端队列
	for (int num : temp) {
		waitQueue.push_back(num);
	}

	addLog("初始化成功：" + to_string(n) + " 名购票者已取号并排序入队。");
}

// 最小端购票
bool TicketSystem::serveMin() {
	if (isEmpty()) return false;

	int ticketNum = waitQueue.front();  // 取头
	waitQueue.pop_front();  // 删头
	soldCountMin++;

	// 补零格式化: 5 -> 005
	string numStr = to_string(ticketNum);
	if (ticketNum < 10) numStr = "00" + numStr;
	else if (ticketNum < 100) numStr = "0" + numStr;

	addLog("编号【" + numStr + "】已从窗口 0 购票");
	return true;
}

// 最大端购票
bool TicketSystem::serveMax() {
	if (isEmpty()) return false;

	int ticketNum = waitQueue.back();
	waitQueue.pop_back();
	soldCountMax++;

	string numStr = to_string(ticketNum);
	if (ticketNum < 10) numStr = "00" + numStr;
	else if (ticketNum < 100) numStr = "0" + numStr;

	addLog("编号【" + numStr + "】已从窗口 1 购票");
	return true;
}

bool TicketSystem::isEmpty() {
	return waitQueue.empty();
}

int TicketSystem::getQueueSize() {
	return (int)waitQueue.size();  // vector.size() 返回 size_t 类型
}

// 打印队列状态
void TicketSystem::printQueueStatus() {
	if (waitQueue.empty()) {
		cout << "【队伍为空，请选择功能 1 进行初始化】" << endl;
		return;
	}

	// Lambda表达式定义打印单个编号的格式
	auto printNum = [](int n) {
		if (n < 10) cout << "(00" << n << ") ";
		else if (n < 100) cout << "(0" << n << ") ";
		else cout << "(" << n << ") ";
		};

	cout << "【窗口0】 <--- ";

	int size = (int)waitQueue.size();
	// 数量多于20个时只输出前后各10个
	if (size <= 20) {
		for (int num : waitQueue) {
			printNum(num);
		}
	}
	else {
		for (int i = 0; i < 10; i++) printNum(waitQueue[i]);
		cout << " ...... ";
		for (int i = size - 10; i < size; i++)
			printNum(waitQueue[i]);
	}
	cout << "---> 【窗口1】" << endl;
}

// 自动模拟
void TicketSystem::autoSimulate(int cnt) {
	addLog(">>> 自动模拟启动，计划执行 " + to_string(cnt) + " 次操作...");

	for (int i = 0; i < cnt; i++) {
		int window = rand() % 2; // 随机生成 0 或 1
		bool success; // 判断操作是否成功

		if (window == 0) success = serveMin();
		else success = serveMax();

		cout << "【实时动态】 >> " << getLastLog() << endl;

		// 队空提前终止
		if (!success) {
			addLog(">>> 模拟中断：队伍已清空。");
			break;
		}
	}
	addLog(">>> 自动模拟结束。");
}

// 显示销售统计报表
void TicketSystem::showStatistics() {
	int totalSold = soldCountMin + soldCountMax;

	cout << "+------------------------------------------+" << endl;
	cout << "|              销售数据统计报表            |" << endl;
	cout << "+------------------------------------------+" << endl;
	cout << "|  总售出票数   : " << left << setw(5) << totalSold << endl;
	cout << "|  窗口0 (Min)  : " << setw(5) << soldCountMin << endl;
	cout << "|  窗口1 (Max)  : " << setw(5) << soldCountMax << endl;
	cout << "|  剩余排队人数 : " << setw(5) << waitQueue.size() << endl;
	cout << "+------------------------------------------+" << endl;
}

//  保存记录到文件
void TicketSystem::saveToFile(string filename) {
	if (saleLog.empty()) {
		cout << " >>> 暂无销售记录，无需导出。" << endl;
		return;
	}

	cout << endl << "正在导出数据... 记录预览：" << endl;
	cout << "---------------------------------" << endl;

	int total = (int)saleLog.size();
	int showCount = 5; // 显示的记录数

	int start = total - showCount;
	if (start < 0) start = 0;

	if (start > 0) {
		cout << "  ... (前 " << start << " 条记录已省略)" << endl;
	}

	for (int i = start; i < total; i++) {
		cout << "  " << saleLog[i] << endl;
	}
	cout << "---------------------------------" << endl;
	cout << "  (日志共计 " << total << " 条记录)" << endl;

	// 写入文件
	ofstream file(filename);
	if (!file) {
		cout << "Error: 无法写入文件 " << filename << endl;
		return;
	}

	file << "========= 世界杯门票销售记录 =========" << endl;
	for (const string& log : saleLog) {
		file << log << endl;
	}
	file << "======================================" << endl;

	file.close();
	addLog("数据已成功导出至文件：" + filename);
}

// 查找指定编号
void TicketSystem::queryTicket(int num) {
	if (waitQueue.empty()) {
		cout << " >>> 队伍为空，无法查询。" << endl;
		return;
	}

	auto it = find(waitQueue.begin(), waitQueue.end(), num);

	if (it != waitQueue.end()) {
		int index = (int)(it - waitQueue.begin()); // 计算下标
		int totalSize = (int)waitQueue.size();

		int frontPeople = index;                // 前面的人数
		int backPeople = totalSize - 1 - index; // 后面的人数 = 总数 - 自己 - 前面的人

		cout << " ----------------------------------" << endl;
		cout << "  查询结果：编号 <" << num << "> 正在排队中。" << endl;
		cout << "  当前位置：第 " << (index + 1) << " 位" << endl;
		cout << "  排队详情：前面还有 " << frontPeople << " 人" << endl;
		cout << "              后面还有 " << backPeople << " 人" << endl;
		cout << " ----------------------------------" << endl;
	}
	else {
		cout << " ----------------------------------" << endl;
		cout << "  查询结果：编号 <" << num << "> 不在队伍中。" << endl;
		cout << "  (可能已购票离开，或从未入队)" << endl;
		cout << " ----------------------------------" << endl;
	}
}