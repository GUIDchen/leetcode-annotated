// 3683. Earliest Time to Finish One Task（3683. 完成一个任务的最早时间）
// 核心思路：每个任务的完成时刻等于开始时刻加耗时，取所有任务完成时刻的最小值即为最早时间。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 题解类
public:  // 公有接口，供判题器调用
    int earliestTime(vector<vector<int>>& tasks) {  // 返回最早完成一个任务的时刻
        int ans = 200;  // 题目时间上限，作为初始的最大值哨兵
        for (const auto& task : tasks) {  // 遍历每个任务
            ans = min(ans, task[0] + task[1]);  // task[0] 是开始时刻，task[1] 是耗时，两者相加为完成时刻
        }
        return ans;  // 返回最小的完成时刻
    }
};
