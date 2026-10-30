// 题目：964. 表示数字的最少运算符（Least Operators to Express Number）
// 思路：记忆化搜索。找出不小于 v 的最小 x 的幂 x^k，最优解取自「用 k-1 次乘法凑出 v - x^(k-1)」与「用 x^k 减去差额」两者较小值。
// 时间复杂度：O(log_x target) 个递归状态，每个状态常数工作量；空间复杂度：O(log_x target)，记忆化哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int leastOpsExpressTarget(int x, int target) {  // x 是允许使用的底数，target 是要表示的目标数
        unordered_map<int, int> f;  // 记忆化表：键是待表示的数值，值是所需的最少运算符个数
        function<int(int)> dfs = [&](int v) -> int {  // 递归函数 dfs(v)：表示出数值 v 需要的最少运算符个数
            if (x >= v) {  // 边界：v 不超过 x 时可以直接用加减逼近
                return min(v * 2 - 1, 2 * (x - v));  // 方案一：v 个 1 相加再补符号，需 v*2-1 个运算符；方案二：用 x 减去差额，需 2*(x-v) 个
            }  // 边界分支结束
            if (f.count(v)) {  // 该状态已经算过，直接查表
                return f[v];  // 返回记忆化结果
            }  // 查表判断结束
            int k = 2;  // k 是 x 的幂次，从 x^2 开始向上找
            long long y = x * x;  // y = x^k，用 long long 防止溢出
            while (y < v) {  // 不断乘 x，直到 y >= v
                y *= x;  // 幂次升高一阶，y 同步乘 x
                ++k;  // 指数加一
            }  // 循环结束：y 是不小于 v 的最小 x 的幂，k 是对应指数
            int ans = k - 1 + dfs(v - y / x);  // 方案一：先凑出 x^(k-1)（用 k-1 次乘法），再从 v 中减掉这一部分递归求解
            if (y - v < v) {  // 只有用 x^k 减去差额更省时才考虑方案二
                ans = min(ans, k + dfs(y - v));  // 方案二：用 k 次乘法凑出 x^k，再减去 y - v
            }  // 方案比较结束
            f[v] = ans;  // 记录该状态的最优解
            return ans;  // 返回当前状态的答案
        };  // 递归 lambda 定义结束
        return dfs(target);  // 从目标数 target 开始搜索
    }  // 方法结束
};  // 题解类结束