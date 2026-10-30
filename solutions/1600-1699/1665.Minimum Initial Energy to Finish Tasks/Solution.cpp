// 题目：1665. 完成所有任务的最少初始能量（Minimum Initial Energy to Finish Tasks）
// 思路：把任务按 (最低需求 m - 实际消耗 a) 升序排序后依次执行；当前剩余能量不足 m 时补齐差额并累加到答案。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，排序原地进行，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumEffort(vector<vector<int>>& tasks) {  // tasks[i] = [实际消耗 a, 最低启动能量 m]，返回最少初始能量
        sort(tasks.begin(), tasks.end(), [&](const auto& a, const auto& b) { return a[0] - a[1] < b[0] - b[1]; });  // 按 (a - m) 升序排序：消耗相对门槛更大的任务先做，这样要预支的能量最少
        int ans = 0, cur = 0;  // ans：需要补进初始能量的总量；cur：当前剩余能量
        for (auto& task : tasks) {  // 依次执行每个任务
            int a = task[0], m = task[1];  // a：本任务的实际消耗；m：开始本任务前必须达到的能量门槛
            if (cur < m) {  // 当前能量不足以启动本任务
                ans += m - cur;  // 差额就是必须额外补充进初始能量的部分
                cur = m;  // 补足后当前能量抬升到门槛 m
            }  // 能量补足逻辑结束
            cur -= a;  // 完成任务，扣掉实际消耗 a
        }  // 遍历结束
        return ans;  // 返回最少需要的初始能量
    }  // 方法结束
};  // 类定义结束