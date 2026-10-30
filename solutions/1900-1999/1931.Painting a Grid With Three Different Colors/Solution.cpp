// 题目：1931. 用三种不同颜色为网格涂色（Painting a Grid With Three Different Colors）
// 思路：把每列压成三进制编码，筛出列内合法编码并两两判断能否相邻，再逐列做转移计数 DP。
// 时间复杂度：O(n·9^m)，合法编码至多 3^m 个；空间复杂度：O(3^m + 转移边数)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int colorTheGrid(int m, int n) {  // m 行 n 列，返回合法涂色方案数
        auto f1 = [&](int x) {  // lambda：判断单列编码 x 是否满足列内相邻格子颜色不同
            int last = -1;  // 上一个格子的颜色，-1 表示还没有
            for (int i = 0; i < m; ++i) {  // 逐行检查，每行对应三进制的一位
                if (x % 3 == last) {  // 当前位颜色与上一位相同，则该列不合法
                    return false;  // 提前返回不合法
                }  // if 结束
                last = x % 3;  // 更新「上一个颜色」
                x /= 3;  // 右移一位三进制，处理下一行
            }  // for 结束
            return true;  // 整列相邻格子颜色都不同，该编码合法
        };  // lambda 结束
        auto f2 = [&](int x, int y) {  // lambda：判断相邻两列编码 x、y 是否没有同一行同色
            for (int i = 0; i < m; ++i) {  // 逐行比较两列的颜色
                if (x % 3 == y % 3) {  // 同一行颜色相同，两列无法相邻
                    return false;  // 提前返回不可相邻
                }  // if 结束
                x /= 3;  // x 右移一位三进制
                y /= 3;  // y 右移一位三进制
            }  // for 结束
            return true;  // 每一行颜色都不同，可以相邻
        };  // lambda 结束

        const int mod = 1e9 + 7;  // 取模常量
        int mx = pow(3, m);  // 一列的所有编码数量：3^m
        unordered_set<int> valid;  // 合法列编码集合
        vector<int> f(mx);  // DP 数组：f[i] 表示当前层以列编码 i 结尾的方案数
        for (int i = 0; i < mx; ++i) {  // 枚举所有 0 .. 3^m-1 的列编码
            if (f1(i)) {  // 该编码自身是一列合法涂色
                valid.insert(i);  // 加入合法集合，避免后面重复枚举
                f[i] = 1;  // 第一列每种合法编码各贡献 1 种方案
            }  // if 结束
        }  // for 结束
        unordered_map<int, vector<int>> d;  // 邻接表：d[i] 保存所有可以与列 i 相邻的列编码
        for (int i : valid) {  // 枚举左列编码
            for (int j : valid) {  // 枚举右列编码
                if (f2(i, j)) {  // 两列在每一行都不同色，可以相邻
                    d[i].push_back(j);  // 记录一条转移边 i -> j
                }  // if 结束
            }  // 内层 for 结束
        }  // 外层 for 结束
        for (int k = 1; k < n; ++k) {  // 从左往右逐列递推，第一列已初始化所以只推 n-1 次
            vector<int> g(mx);  // 下一层的 DP 数组
            for (int i : valid) {  // 枚举当前列编码
                for (int j : d[i]) {  // 枚举可以转移到它的上一列编码
                    g[i] = (g[i] + f[j]) % mod;  // 累加方案数并取模
                }  // 内层 for 结束
            }  // 外层 for 结束
            f = move(g);  // 滚动：把下一层当作当前层
        }  // for 结束
        int ans = 0;  // 答案累加器
        for (int x : f) {  // 汇总最后一列所有编码的方案数
            ans = (ans + x) % mod;  // 累加并取模
        }  // for 结束
        return ans;  // 返回总方案数
    }  // 方法结束
};  // 类结束