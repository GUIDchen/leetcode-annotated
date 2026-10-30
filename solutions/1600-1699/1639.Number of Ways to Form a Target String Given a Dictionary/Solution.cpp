// 题目：1639. 通过给定词典构造目标字符串的方案数（Number of Ways to Form a Target String Given a Dictionary）
// 思路：预处理每一列各字母的出现次数，再按目标串位置做记忆化 DFS：跳过该列，或用该列匹配下一个目标字符。
// 时间复杂度：O(m·n·26)，预处理计数与 m×n 个状态的转移；空间复杂度：O(m·n + n·26)，记忆化数组与列计数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numWays(vector<string>& words, string target) {  // words 是长度相同的词典，target 是目标串，返回构造方案数
        const int mod = 1e9 + 7;  // 模数 1e9+7，防止计数溢出
        int m = target.size(), n = words[0].size();  // m 是目标串长度，n 是词典中单词长度（也是可用列数）
        vector<vector<int>> cnt(n, vector<int>(26));  // cnt[j][c]：第 j 列上字母 c 出现的次数（26 个字母表）
        for (auto& w : words) {  // 遍历词典里的每个单词
            for (int j = 0; j < n; ++j) {  // 遍历该单词的每一列
                ++cnt[j][w[j] - 'a'];  // 第 j 列上字母 w[j] 的计数加一（减去 'a' 映射到 0~25）
            }  // 列循环结束
        }  // 单词循环结束
        int f[m][n];  // 记忆化数组：f[i][j] 表示「还需匹配 target[i..] 且从第 j 列开始」的方案数
        memset(f, -1, sizeof(f));  // memset 按字节置 -1，对 int 而言正好得到 -1，表示该状态尚未计算
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 定义递归函数对象：i 是目标串进度，j 是当前列
            if (i >= m) {  // 目标串已经全部匹配完成，这是一种合法方案
                return 1;  // 返回 1 累加方案数
            }  // if 结束
            if (j >= n) {  // 列已经用完但目标串还没匹配完，该分支无解
                return 0;  // 返回 0 表示此路不通
            }  // if 结束
            if (f[i][j] != -1) {  // 该状态已经算过，直接返回缓存值（记忆化避免重复计算）
                return f[i][j];  // 返回缓存中的方案数
            }  // if 结束
            int ans = dfs(i, j + 1);  // 方案一：不匹配这一列，直接跳到下一列
            ans = (ans + 1LL * dfs(i + 1, j + 1) * cnt[j][target[i] - 'a']) % mod;  // 方案二：用这一列的字母匹配 target[i]，方案数为「剩余部分的方案数 × 该列上该字母的个数」
            return f[i][j] = ans;  // 把结果写入 f[i][j] 并返回
        };  // lambda 定义结束
        return dfs(0, 0);  // 从「目标串下标 0、第 0 列」开始求解
    }  // numWays 方法结束
};  // 题解类定义结束
