// 题目：2466. 统计构造好字符串的方案数（Count Ways To Build Good Strings）
// 核心思路：记忆化搜索统计方案数。dfs(i) 表示当前串长度为 i 时能补出的好字符串个数；若 i 已在 [low, high] 内，当前串自身算 1 种，再分别追加 zero 个 0 与 one 个 1 递归累加。
// 时间复杂度：O(high)，每个长度状态只计算一次；空间复杂度：O(high)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int mod = 1e9 + 7;  // 取模常量，防止方案数溢出

    int countGoodStrings(int low, int high, int zero, int one) {  // low/high：合法长度区间；zero/one：每次追加的 0 与 1 的个数
        vector<int> f(high + 1, -1);  // 记忆化数组：f[i] 表示长度为 i 时的方案数，-1 表示尚未计算
        function<int(int)> dfs = [&](int i) -> int {  // 递归函数 dfs(i)：当前串长度为 i 时，后续能构造出的好字符串个数
            if (i > high) return 0;  // 长度超过上界，这条构造路径非法，贡献 0 种方案
            if (f[i] != -1) return f[i];  // 已经算过就直接复用，避免重复搜索
            long ans = i >= low && i <= high;  // 当前长度落在 [low, high] 内则自身算一种好字符串（bool 隐式转成 0/1）
            ans += dfs(i + zero) + dfs(i + one);  // 末尾追加 zero 个 '0' 或 one 个 '1'，两条分支的方案数相加
            ans %= mod;  // 对大数取模，保证结果落在 int 范围内
            f[i] = ans;  // 写入记忆化数组，供同一状态直接复用
            return ans;  // 返回长度为 i 的方案数
        };  // 结束 lambda 的定义
        return dfs(0);  // 空串长度为 0，从长度 0 开始构造
    }  // 结束 countGoodStrings 方法
};  // 结束 Solution 类
