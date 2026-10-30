// 题目：2432. 处理用时最长的那个任务的员工（The Employee That Worked on the Longest Task）
// 思路：日志按完成时刻升序给出，相邻两条的时间差即本次任务用时；遍历时维护最长用时与对应员工编号。
// 时间复杂度：O(n)，只扫一遍日志；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int hardestWorker(int n, vector<vector<int>>& logs) {  // n：员工总数；logs：每条日志为 {员工编号, 任务完成时刻}
        int ans = 0, mx = 0, last = 0;  // ans：答案员工编号；mx：最长用时；last：上一条日志的完成时刻
        for (auto& log : logs) {  // 按时间顺序逐条扫描日志
            int uid = log[0], t = log[1];  // uid：本条日志的员工编号；t 先取任务完成时刻
            t -= last;  // 用当前时刻减去上一条完成时刻，得到本次任务实际用时
            if (mx < t || (mx == t && ans > uid)) {  // 用时更长，或用时相同但员工编号更小（题目要求编号最小）
                mx = t;  // 更新最长用时
                ans = uid;  // 更新答案员工编号
            }
            last += t;  // 累加耗时，把 last 推进到当前日志的完成时刻，供下一轮使用
        }
        return ans;  // 返回用时最长的员工编号
    }
};