// 题目：2464. 有效分割中的最少子数组数目（Minimum Subarrays in a Valid Split）
// 核心思路：记忆化搜索。每一段必须首尾元素的最大公约数大于 1；dfs(i) 枚举以 nums[i] 开头的所有合法段尾 j，答案为 1 + dfs(j + 1) 的最小值，f[i] 缓存已算状态。
// 时间复杂度：O(n^2 log V)，共 n 个状态、每个状态枚举 n 个段尾并做一次 gcd；空间复杂度：O(n)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int inf = 0x3f3f3f3f;  // 无穷大哨兵，表示「这个位置无法继续分割」
    int validSubarraySplit(vector<int>& nums) {  // nums：待分割数组；返回最少子数组数目，无解返回 -1
        int n = nums.size();  // 数组长度，递归里多处复用
        vector<int> f(n);  // 记忆化数组：f[i] 表示从下标 i 开始最少能切几段；0 表示尚未计算
        function<int(int)> dfs = [&](int i) -> int {  // 递归函数 dfs(i)：求后缀 nums[i..] 的最少分割段数
            if (i >= n) return 0;  // 下标越界说明剩余元素为空，无需再切，段数为 0
            if (f[i]) return f[i];  // 算过就直接复用，避免指数级重复搜索
            int ans = inf;  // 先假设当前后缀无法完成分割
            for (int j = i; j < n; ++j) {  // 枚举这一段的最后一个位置 j；段非空，所以从 i 开始
                if (__gcd(nums[i], nums[j]) > 1) {  // 合法段要求段首与段尾元素的最大公约数大于 1
                    ans = min(ans, 1 + dfs(j + 1));  // 当前这一段算 1 段，再加上剩余部分的最优解
                }  // 结束 gcd 合法性判断
            }  // 结束段尾枚举
            f[i] = ans;  // 结果写入记忆化数组，供同一状态直接复用
            return ans;  // 返回当前后缀的最优值
        };  // 结束 lambda 的定义
        int ans = dfs(0);  // 从下标 0 开始分割整个数组
        return ans < inf ? ans : -1;  // 仍是 inf 说明不存在合法分割，按题意返回 -1
    }  // 结束 validSubarraySplit 方法
};  // 结束 Solution 类
