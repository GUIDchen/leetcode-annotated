// 题目：1449. 数位成本和为目标值的最大数字（Form Largest Integer With Digits That Add up to Target）
// 核心思路：完全背包 DP。f[i][j] 表示只用数字 1..i、总成本恰好为 j 时能凑出的最大位数，g 记录回溯路径；位数越多数字越大，位数相同时降序拼接的数字最大。
// 时间复杂度：O(9 * target)，即数字种类数乘以容量；空间复杂度：O(9 * target)，两张 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string largestNumber(vector<int>& cost, int target) {  // 返回成本恰好为 target 的最大数字（字符串形式），无解返回 "0"
        const int inf = 1 << 30;  // inf 表示「负无穷」，用来标记不可达状态
        vector<vector<int>> f(10, vector<int>(target + 1, -inf));  // f[i][j]：只使用数字 1..i、总成本恰好为 j 时能得到的最大位数，初始全为不可达
        vector<vector<int>> g(10, vector<int>(target + 1));  // g[i][j]：回溯用，记录在状态 (i, j) 上「不使用数字 i」时对应的成本
        f[0][0] = 0;  // 不选任何数字、成本为 0 时位数为 0，这是唯一的合法起点
        for (int i = 1; i <= 9; ++i) {  // 按数字 1..9 的顺序逐个加入物品（数字就是物品）
            int c = cost[i - 1];  // cost[i-1] 是数字 i 的代价（cost 下标从 0 开始）
            for (int j = 0; j <= target; ++j) {  // j 从小到大遍历，保证同一数字可以被重复使用（完全背包）
                if (j < c || f[i][j - c] + 1 < f[i - 1][j]) {  // 成本不够用不了数字 i，或者不用它位数更长，则选择不使用数字 i
                    f[i][j] = f[i - 1][j];  // 继承不使用数字 i 时的最优解
                    g[i][j] = j;  // g 记录 j 本身，表示这一层没有消耗数字 i 的成本
                } else {  // 否则说明多用一个数字 i 能得到更多位数
                    f[i][j] = f[i][j - c] + 1;  // 在成本 j-c 的基础上再加一位数字 i
                    g[i][j] = j - c;  // g 记录加上这一位之前的成本，供回溯使用
                }  // if-else 分支结束
            }  // 内层循环（成本 j）结束
        }  // 外层循环（数字 i）结束
        if (f[9][target] < 0) {  // 最大位数为负说明无法恰好凑出 target
            return "0";  // 按题意无解时返回字符串 "0"
        }  // if 分支结束
        string ans;  // 结果字符串，回溯时按数字从大到小拼接
        for (int i = 9, j = target; i;) {  // 从最大的数字 9 和总成本 target 开始回溯，i 减到 0 时结束
            if (g[i][j] == j) {  // g[i][j] == j 说明这一层的数字 i 没有被使用
                --i;  // 跳过数字 i，继续看更小的数字
            } else {  // 否则说明数字 i 被使用了一次
                ans += '0' + i;  // 追加数字 i 对应的字符，从 9 到 1 顺序拼接即为降序（同位数的最大值）
                j = g[i][j];  // 把成本回退到加上这一位之前的状态
            }  // if-else 分支结束
        }  // while 回溯结束
        return ans;  // 返回拼好的最大数字
    }  // largestNumber 方法结束
};  // 类定义结束（源文件此处无结尾换行，保持原样）