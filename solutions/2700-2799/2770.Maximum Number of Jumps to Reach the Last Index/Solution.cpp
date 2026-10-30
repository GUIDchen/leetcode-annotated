// 题目：2770. 达到末尾下标所需的最大跳跃次数（Maximum Number of Jumps to Reach the Last Index）
// 思路：记忆化 DFS，f[i] 表示从 i 跳到末尾的最大跳数；枚举所有满足 |nums[i] - nums[j]| <= target 的 j，取 1 + f[j] 的最大值。
// 时间复杂度：O(n^2)，每个状态枚举 O(n) 个后继；空间复杂度：O(n)，记忆数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumJumps(vector<int>& nums, int target) {  // nums：输入数组；target：一次跳跃允许的最大下标差值绝对值
        int n = nums.size();  // 数组长度
        int f[n];  // 记忆数组：f[i] 表示从下标 i 跳到末尾能得到的最大跳数
        memset(f, -1, sizeof(f));  // 全部置为 -1，表示该状态还没有被计算过
        auto dfs = [&](this auto&& dfs, int i) -> int {  // C++23 显式对象形参，让 lambda 能以 dfs(...) 的形式递归调用自己
            if (i == n - 1) {  // 已经在末尾，不需要再跳
                return 0;  // 剩余跳数为 0
            }  // 边界处理结束
            if (f[i] != -1) {  // 该状态之前已经算过
                return f[i];  // 直接返回记忆化的结果
            }  // 查表结束
            f[i] = -(1 << 30);  // 先置一个很小的负值，表示暂时无法到达末尾
            for (int j = i + 1; j < n; ++j) {  // 枚举所有可能的下一站 j（只能向右跳）
                if (abs(nums[i] - nums[j]) <= target) {  // 差值在允许范围内才构成一次合法跳跃
                    f[i] = max(f[i], 1 + dfs(j));  // 用 1 跳加上从 j 出发的最优解来更新 f[i]
                }  // 合法性判断结束
            }  // 后继枚举结束
            return f[i];  // 返回从 i 出发的最大跳数（可能是负值，表示不可达）
        };  // 递归 lambda 定义结束
        int ans = dfs(0);  // 从下标 0 开始跳
        return ans < 0 ? -1 : ans;  // 负数说明到不了末尾，按题目要求返回 -1
    }  // 方法结束
};  // 类定义结束
