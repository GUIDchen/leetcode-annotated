// 题目：1751. 最多可以参加的会议数目 II（Maximum Number of Events That Can Be Attended II）
// 核心思路：会议按开始时间排序后做记忆化搜索，dfs(i, k) 表示从第 i 个会议起、还能参加 k 场时的最大收益；每个会议有「不参加」和「参加后跳到第一个开始时间晚于其结束时间的会议」两种决策，取较大值。
// 时间复杂度：O(n·k·log n)，共 n·k 个状态、每次用二分找后继；空间复杂度：O(n·k)，记忆数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxValue(vector<vector<int>>& events, int k) {  // events 每项是 [开始, 结束, 价值]，k 是最多能参加的会议数
        ranges::sort(events);  // 按开始时间（并列再按结束、价值）字典序排序，使后续下标单调、可二分
        int n = events.size();  // 会议总数，作为递归的越界判定
        int f[n][k + 1];  // 记忆数组：f[i][k] 表示从第 i 个会议起、还剩 k 个名额时的最大收益
        memset(f, 0, sizeof(f));  // 全部清零，0 同时充当「尚未计算」的标记（收益恒为正，不会混淆）
        auto dfs = [&](this auto&& dfs, int i, int k) -> int {  // 递归 lambda：显式对象参数 this auto&& 让闭包能引用自身实现递归
            if (i >= n || k <= 0) {  // 边界：会议已经全部考虑完，或名额用尽
                return 0;  // 无法再获得收益
            }  // 边界判断结束
            if (f[i][k] > 0) {  // 该状态已经算过，直接复用记忆结果
                return f[i][k];  // 返回缓存值
            }  // 缓存判断结束

            int ed = events[i][1], val = events[i][2];  // 当前会议的结束时间与价值
            vector<int> t = {ed};  // 二分查找的哨兵：用一个只含结束时间的数组去比较开始时间

            int p = upper_bound(events.begin() + i + 1, events.end(), t,  // 在 i 之后找第一个开始时间严格大于 ed 的会议，即参加当前会议后的下一个可选会议
                        [](const auto& a, const auto& b) { return a[0] < b[0]; })  // 自定义比较：只比较开始时间 a[0]，因为要与只含结束时间的哨兵同序比较
                - events.begin();  // 迭代器相减得到下标

            f[i][k] = max(dfs(i + 1, k), dfs(p, k - 1) + val);  // 两种决策取较大值：跳过当前会议，或参加它并消耗一个名额后跳到 p
            return f[i][k];  // 返回并缓存该状态的最优值
        };  // lambda 定义结束

        return dfs(0, k);  // 从第一个会议、k 个名额开始搜索
    }  // 方法结束
};  // 题解类结束
