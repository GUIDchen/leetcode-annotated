// 题目：3205. 最大数组跳跃得分 I（Maximum Array Hopping Score I）
// 思路：从下标 0 跳到末尾，每次跳跃得分 (j - i) * nums[j]；用记忆化 DFS 枚举所有落点并取最大值，f[i] 缓存从 i 出发的最优解。
// 时间复杂度：O(n²)，每个状态枚举 O(n) 个落点；空间复杂度：O(n)，记忆化数组与递归栈。
class Solution {  // LeetCode 题解类，固定入口名
public:  // 解法方法对外可见
    int maxScore(vector<int>& nums) {  // 返回从下标 0 跳到末尾的最大得分；nums 为跳跃数组
        int n = nums.size();  // n 为数组长度
        vector<int> f(n);  // 记忆化数组：f[i] 存从下标 i 出发的最大得分，0 表示尚未计算
        auto dfs = [&](this auto&& dfs, int i) -> int {  // 递归 lambda（C++23 的 deducing this）：求从下标 i 出发的最大得分
            if (f[i]) {  // 如果 f[i] 已经算过（记忆化命中）
                return f[i];  // 直接返回缓存值，避免重复递归
            }  // 记忆化分支结束
            for (int j = i + 1; j < n; ++j) {  // 枚举所有可落点 j，一次跳跃的得分与跨过的距离成正比
                f[i] = max(f[i], (j - i) * nums[j] + dfs(j));  // 得分 = (j - i) * nums[j] + 从 j 继续跳的最优得分，取最大
            }  // 落点枚举结束
            return f[i];  // 返回从 i 出发的最优得分
        };  // lambda 定义结束
        return dfs(0);  // 从下标 0 出发求答案
    }  // 方法结束
};  // 题解类结束
