// 题目：486. 预测赢家（Predict the Winner）
// 思路：区间博弈 DP。dfs(i, j) 返回“当前玩家在 nums[i..j] 上先手能领先对手的分数”，取左端或右端时要用自己的得分减去对手在剩余区间的领先值，最后看整体分差是否不小于 0。
// 时间复杂度：O(n²)，共 n² 个区间且每个只算一次；空间复杂度：O(n²)，记忆化数组 f 的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的题解方法
    bool predictTheWinner(vector<int>& nums) {  // nums 是可选分数序列，返回先手是否能赢（分数不少于对手即为赢）
        int n = nums.size();  // 区间长度上界
        vector<vector<int>> f(n, vector<int>(n));  // 记忆化数组：f[i][j] 保存区间 [i, j] 上先手的最大分差，0 表示尚未计算
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // 递归 lambda：this auto&& 让 lambda 能递归调用自己，i、j 是当前区间两端
            if (i > j) {  // 区间为空（i 越过 j）时没有分数可得
                return 0;  // 空区间返回 0
            }  // 结束 if
            if (f[i][j]) {  // 该区间已经算过就直接复用
                return f[i][j];  // 返回记忆化结果，避免重复搜索
            }  // 结束 if
            return f[i][j] = max(nums[i] - dfs(i + 1, j), nums[j] - dfs(i, j - 1));  // 两种选法取更优：选左端 nums[i] 后减去对手在 [i+1, j] 的领先值，或选右端 nums[j] 后减去对手在 [i, j-1] 的领先值；同时写回 f 作为记忆化
        };  // 结束递归 lambda 的定义
        return dfs(0, n - 1) >= 0;  // 整个区间的分差 ≥ 0 说明先手不会输，即可以赢
    }  // 结束题解方法
};  // 结束题解类