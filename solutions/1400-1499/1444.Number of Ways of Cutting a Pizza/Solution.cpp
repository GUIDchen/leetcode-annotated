// 题目：1444. 切披萨的方案数（Number of Ways of Cutting a Pizza）
// 思路：二维前缀和 O(1) 统计区域苹果数，记忆化搜索「剩下左上角为 (i,j) 的块、还要切 k 刀」的方案数。
// 时间复杂度：O(k·m·n·(m+n))；空间复杂度：O(m·n·k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int ways(vector<string>& pizza, int k) {  // pizza 是每行一个字符串的披萨，k 是要切成的块数
        const int mod = 1e9 + 7;  // 结果需要对 1e9+7 取模
        int m = pizza.size(), n = pizza[0].size();  // m 是行数，n 是列数
        // f 的下标不会越界：递归中 i<m、j<n，k 递减到 0 就停
        vector<vector<vector<int>>> f(m, vector<vector<int>>(n, vector<int>(k, -1)));  // 记忆化表：f[i][j][k] 表示剩下 (i,j) 为左上角、还要切 k 刀的方案数，-1 表示尚未计算
        // 多开一行一列，让 s[0][*] 与 s[*][0] 天然为 0，省去边界判断
        vector<vector<int>> s(m + 1, vector<int>(n + 1));  // 二维前缀和：s[i][j] 表示左上角 i 行 j 列区域内的苹果个数
        for (int i = 1; i <= m; ++i) {  // 外层按行推进前缀和
            for (int j = 1; j <= n; ++j) {  // 内层按列推进前缀和
                int x = pizza[i - 1][j - 1] == 'A' ? 1 : 0;  // 当前格子是苹果记 1，否则记 0
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + x;  // 容斥计算前缀和：上 + 左 - 左上角重复部分 + 当前格
            }
        }
        function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int {  // 递归 lambda（用 function 包住才能自我调用）；i,j 是当前块左上角，k 是还要切的刀数
            if (k == 0) {  // 不能再切了，剩下的这一整块必须自己带苹果
                return s[m][n] - s[i][n] - s[m][j] + s[i][j] > 0 ? 1 : 0;  // 用前缀和求剩余区域苹果数，大于 0 记 1 种方案，否则为 0
            }
            if (f[i][j][k] != -1) {  // 该状态之前算过，直接复用，避免重复搜索
                return f[i][j][k];  // 返回记忆化表里的值
            }
            int ans = 0;  // 当前状态的方案数
            for (int x = i + 1; x < m; ++x) {  // 枚举横切位置 x：把 x 以上部分切给当前这一块
                if (s[x][n] - s[i][n] - s[x][j] + s[i][j] > 0) {  // 横切后上方那块必须含有苹果，仍是完整的剩余块才有意义
                    ans = (ans + dfs(x, j, k - 1)) % mod;  // 下方剩余部分继续切 k-1 刀，方案数累加后取模
                }
            }  // 横切枚举结束
            for (int y = j + 1; y < n; ++y) {  // 枚举竖切位置 y：把 y 以左部分切给当前这一块
                if (s[m][y] - s[i][y] - s[m][j] + s[i][j] > 0) {  // 竖切后左侧那块必须含有苹果
                    ans = (ans + dfs(i, y, k - 1)) % mod;  // 右侧剩余部分继续切 k-1 刀，方案数累加后取模
                }
            }  // 所有切法枚举完毕
            return f[i][j][k] = ans;  // 写入记忆化表并返回当前状态的方案数
        };
        return dfs(0, 0, k - 1);  // 整块披萨作为初始块；要切成 k 块，只需再切 k-1 刀
    }
};