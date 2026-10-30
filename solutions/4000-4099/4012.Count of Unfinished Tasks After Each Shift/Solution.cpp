// 题目：4012. 统计每个班次结束后的未完成任务数（Count of Unfinished Tasks After Each Shift）
// 思路：用前缀和 s 表示前 i 个任务的总工时；每个班次先看能否做完当前任务，能做完就在前缀和上二分定位停在哪个任务、并处理「做完一整轮则从头再来」的情况；未完成任务数恒为 m - i。
// 时间复杂度：O((m + n) log m)，每个班次至多二分一次；空间复杂度：O(m + n)，前缀和数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countTasks(vector<int>& tasks, vector<int>& shifts) {  // tasks：每个任务的工时；shifts：每个班次的工时；返回每个班次结束后的未完成任务数
        int m = tasks.size();  // m 为任务数量
        int n = shifts.size();  // n 为班次数量

        vector<long long> s(m + 1);  // 前缀和：s[i] 表示前 i 个任务的总工时，便于整段跨过任务
        for (int i = 0; i < m; i++) {  // 递推计算前缀和
            s[i + 1] = s[i] + tasks[i];  // 累加第 i 个任务的工时
        }  // 结束前缀和计算

        vector<int> ans(n);  // ans[j] 记录第 j 个班次结束后的未完成任务数

        int i = 0;  // i 是当前正在处理的任务下标
        long long cur = 0;  // cur 是当前任务上已经完成的工时

        for (int j = 0; j < n; j++) {  // 依次处理每个班次
            if (shifts[j] < tasks[i] - cur) {  // 班次工时不足以做完当前任务
                cur += shifts[j];  // 把整个班次的工时都花在当前任务上
                ans[j] = m - i;  // 未完成任务数保持不变
            } else {  // 班次工时足以做完当前任务，可能还继续往后做
                long long t = shifts[j] - (tasks[i] - cur);  // 先扣掉做完当前任务所需工时，t 为剩余的班次工时

                if (t >= s[m] - s[i + 1]) {  // 剩余工时足以做完一整轮（i 之后的所有任务）
                    i = 0;  // 一轮做完，下标回到开头的任务
                    cur = 0;  // 已完成工时清零
                } else {  // 剩余工时不足以做完一整轮，需二分定位停在哪一个任务
                    int l = i + 1, r = m;  // 在区间 [i + 1, m] 中二分，找第一个「剩余工时不够做完」的任务

                    while (l < r) {  // 二分查找
                        int mid = (l + r) >> 1;  // 取中点
                        if (t < s[mid + 1] - s[i + 1]) {  // 剩余工时小于做完到 mid 为止所需的工时，停下位置不晚于 mid
                            r = mid;  // 收缩右边界
                        } else {  // 剩余工时足够做完到 mid 为止
                            l = mid + 1;  // 收缩左边界
                        }  // 结束二分判断
                    }  // 结束二分查找

                    cur = t - (s[l] - s[i + 1]);  // 新任务上已完成的工时 = 剩余工时 - 前面整段任务的工时
                    i = l;  // 更新当前任务下标
                    ans[j] = m - i;  // 记录该班次结束后的未完成任务数
                }  // 结束「未做完一整轮」的分支
            }  // 结束班次工时是否够用的分支
        }  // 结束班次遍历

        return ans;  // 返回每个班次结束后的未完成任务数
    }  // 结束 countTasks
};  // 结束 Solution 类