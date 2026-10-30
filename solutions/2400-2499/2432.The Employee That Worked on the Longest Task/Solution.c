// 题目：2432. 处理用时最长的那个任务的员工（The Employee That Worked on the Longest Task）
// 思路：日志按完成时刻升序给出，相邻两条的时间差就是本次任务用时；遍历时维护最长用时与对应员工编号。
// 时间复杂度：O(n)，只需扫一遍日志；空间复杂度：O(1)，只用了几个计数与临时变量。
#define min(a, b) (((a) < (b)) ? (a) : (b))  // 宏：取两个值中的较小者（与仓库原文件保持一致，未新增头文件）

int hardestWorker(int n, int** logs, int logsSize, int* logsColSize) {  // n：员工总数；logs：每条日志为 {员工编号, 任务完成时刻}
    int res = 0;  // 记录答案员工编号，初始为 0（题面员工编号从 0 开始）
    int max = 0;  // 记录目前找到的最长单次任务用时
    int pre = 0;  // 上一条日志的完成时刻，用来算本次任务用时
    for (int i = 0; i < logsSize; i++) {  // 按时间顺序逐条扫描日志
        int t = logs[i][1] - pre;  // 本次任务用时 = 当前时刻 - 上一条完成时刻
        if (t > max || (t == max && res > logs[i][0])) {  // 用时更长，或用时相同但员工编号更小（题目要求编号最小）
            res = logs[i][0];  // 更新答案员工编号
            max = t;  // 更新最长用时
        }
        pre = logs[i][1];  // 把当前完成时刻记为下一轮的基准时刻
    }
    return res;  // 返回用时最长的员工编号
}