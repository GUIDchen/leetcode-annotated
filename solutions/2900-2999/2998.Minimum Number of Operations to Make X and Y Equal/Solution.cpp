// 题目：2998. 使 X 和 Y 相等的最少操作次数（Minimum Number of Operations to Make X and Y Equal）
// 思路：记忆化 DFS。从 x 出发枚举「减 1」以及「先补到 5 / 11 的倍数再整除」这几类操作，取步数最小者。
// 时间复杂度：O(log x) 个可达状态、每个状态 5 种转移；空间复杂度：O(log x)，记忆化哈希表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumOperationsToMakeEqual(int x, int y) {  // x：起始值；y：目标值；返回把 x 变成 y 的最少操作次数
        unordered_map<int, int> f;  // memo：记录某个数值已经算好的最少操作次数，避免重复搜索
        function<int(int)> dfs = [&](int x) {  // 递归 lambda：求把参数 x 变成 y 的最少操作次数
            if (y >= x) {  // 递归边界：x 已经不大于 y，继续除或加 1 只会更远
                return y - x;  // 只能一路减 1，步数就是差值 y - x
            }
            if (f.count(x)) {  // 该数值已经算过，直接复用结果
                return f[x];  // 返回记忆化的答案
            }
            int a = x % 5 + 1 + dfs(x / 5);  // 方案一：先减 x % 5 步补到 5 的倍数，再花 1 步除以 5
            int b = 5 - x % 5 + 1 + dfs(x / 5 + 1);  // 方案二：先加 5 - x % 5 步补到上一个 5 的倍数，再花 1 步除以 5
            int c = x % 11 + 1 + dfs(x / 11);  // 方案三：先减 x % 11 步补到 11 的倍数，再花 1 步除以 11
            int d = 11 - x % 11 + 1 + dfs(x / 11 + 1);  // 方案四：先加 11 - x % 11 步补到上一个 11 的倍数，再花 1 步除以 11
            return f[x] = min({x - y, a, b, c, d});  // 五种走法（含完全不除只减 1）取最小，写入 memo 后返回
        };  // 递归 lambda 定义结束
        return dfs(x);  // 从起点 x 开始求解
    }
};