#include "TicketSystem.h"
#include "tools.h"

int main() {
	TicketSystem sys;
	int choice;

	while (true) {
		// 清屏
		system("cls");

		// 显示菜单
		cout << "=============================" << endl;
		cout << "      世界杯门票销售系统     " << endl;
		cout << "=============================" << endl;

		sys.printQueueStatus();
		cout << endl;
		cout << "【系统消息】 >> " << sys.getLastLog() << endl;
		cout << "-----------------------------" << endl;

		cout << "1. 初始化排队" << endl;
		cout << "2. 窗口购票" << endl;
		cout << "3. 自动模拟" << endl;
		cout << "4. 导出记录" << endl;
		cout << "5. 售出统计" << endl;
		cout << "6. 查询号码" << endl;
		cout << "0. 退出系统" << endl;
		cout << "-----------------------------" << endl;
		choice = safeInputInt("请输入选项: ", 0, 6);

		switch (choice) {
		case 1: {
			// 如果队伍不为空
			if (!sys.isEmpty()) {
				cout << " >>> warning：当前队伍中还有 " << sys.getQueueSize() << " 人。" << endl;
				cout << " >>> 重新初始化将清空当前数据。" << endl;
				int confirm = safeInputInt(" >>> 确认继续吗？(1:确认 / 0:取消): ", 0, 1);
				if (confirm == 0) break;
			}

			string tip = " >> 请输入购票人数(1-" + to_string(MAX_TICKET_NUM) + "): ";
			int n = safeInputInt(tip, 1, MAX_TICKET_NUM);
			sys.initQueue(n);
			break;
		}
		case 2: {
			if (sys.isEmpty()) {
				cout << " >>> error：队伍为空！请先执行功能 [1] 进行初始化。" << endl;
				pressEnterToReturn();
				break;
			}

			int side;
			while (true) {
				system("cls");
				cout << "========【 购票模式 】========" << endl;
				sys.printQueueStatus();
				cout << endl;
				cout << "【最新动态】 >> " << sys.getLastLog() << endl;
				cout << "--------------------------------" << endl;
				
				// 队空后自动退出购票模式
				if (sys.isEmpty()) {
					cout << " >>> 提示：队伍已清空。" << endl;
					cout << " >>> 即将自动返回主菜单..." << endl;
					pressEnterToReturn();
					break; 
				}
				
				cout << " 输入 0 : 最小端购票" << endl;
				cout << " 输入 1 : 最大端购票" << endl;
				cout << " 输入 -1: 返回主菜单" << endl;
				cout << "--------------------------------" << endl;

				side = safeInputInt(" >> 请输入指令: ", -1, 1);

				if (side == -1) break;
				else if (side == 0) sys.serveMin();
				else if (side == 1) sys.serveMax();
			}
			break;
		}
		case 3: {
			if (sys.isEmpty()) {
				cout << " >>> error：队伍为空，无法模拟！请先执行功能 [1] 进行初始化。" << endl;
				pressEnterToReturn();
				break;
			}
			// 模拟次数要小于等于当前队伍人数
			int size = sys.getQueueSize();
			string tip = " >> 请输入模拟次数(1-" + to_string(size) + "): ";
			int count = safeInputInt(tip, 1, size);

			sys.autoSimulate(count);
			pressEnterToReturn();
			break;
		}
		case 4:
			sys.saveToFile("SalesLog.txt");
			if (!sys.getLastLog().empty())
				pressEnterToReturn();
			break;
		case 5:
			cout << endl;
			sys.showStatistics();
			pressEnterToReturn();
			break;
		case 6: {
			if (sys.isEmpty()) {
				cout << " >>> error：队伍为空，无法模拟！请先执行功能 [1] 进行初始化。" << endl;
				pressEnterToReturn();
				break;
			}
			string tip = " >> 请输入要查询的编号(1-" + to_string(MAX_TICKET_NUM) + "): ";
			int n = safeInputInt(tip, 1, MAX_TICKET_NUM);
			sys.queryTicket(n);
			pressEnterToReturn();
			break;
		}

		case 0:
			cout << endl << " >>> 感谢使用，系统已退出。<<<" << endl;
			return 0;
		}
	}
	return 0;
}