// 题目：3225. 网格图操作后的最大分数（Maximum Score From Grid Operations）
// 思路：用 k[j] 表示第 j 列染黑的高度，第 j 列贡献 max(0, s[j][max(k[j-1],k[j+1])] - s[j][k[j]])，按列做 DP，并用前缀/后缀最大值把每层转移从 O(n^2) 降到 O(n)。
// 时间复杂度：O(n^3)，n 层状态 × O(n^2) 转移；空间复杂度：O(n^2)，存列前缀和与两层 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    long long maximumScore(vector<vector<int>>& grid) {  // grid：n x n 网格；返回操作后能得到的最大总分
        int n = grid.size();  // 网格边长
        const long long inf = LLONG_MIN / 2;  // 表示「不可达」的极小值，取一半是为了加法时不至于下溢
        vector<vector<long long>> s(n, vector<long long>(n + 1));  // s[j][h]：第 j 列前 h 个格子的前缀和
        for (int j = 0; j < n; ++j) {  // 逐列做预处理
            for (int i = 0; i < n; ++i) {  // 沿列自上而下累加
                s[j][i + 1] = s[j][i] + grid[i][j];  // 一维前缀和：第 j 列前 i+1 行之和
            }  // 行循环结束
        }  // 列循环结束
        vector<vector<long long>> f(n + 1, vector<long long>(n + 1, inf));  // f[h1][h2]：当前列高度 h1、前一列高度 h2 时的最大得分
        for (int h = 0; h <= n; ++h) {  // 第 0 列左边没有列，前一列高度按 0 处理
            f[h][0] = 0;  // 高度为 h 的第 0 列此时还没有来自邻居的加成
        }  // 第 0 列的初始状态初始化完成
        for (int j = 0; j < n - 1; ++j) {  // 逐列向右转移，每轮固定第 j 列、枚举它左右两侧的高度
            vector<vector<long long>> g(n + 1, vector<long long>(n + 1, inf));  // 下一层状态 g[下一列高度 hp][当前列高度 h1]
            for (int h1 = 0; h1 <= n; ++h1) {  // 枚举当前列高度 h1（即 k[j]）
                vector<long long> pre(n + 2, inf), suf(n + 2, inf);  // pre 存前缀最大值、suf 存后缀最大值，都多开一位作哨兵
                pre[0] = f[h1][0];  // 前缀最大值的起点
                for (int h2 = 1; h2 <= n; ++h2) {  // 从左往右构建 h2 的前缀最大值
                    pre[h2] = max(pre[h2 - 1], f[h1][h2]);  // pre[h2] = max_{h2' <= h2} f[h1][h2']
                }  // 前缀最大值构建完成
                for (int h2 = n; h2 >= 0; --h2) {  // 从右往左构建 h2 的后缀最大值
                    long long v = f[h1][h2] == inf ? inf : f[h1][h2] + max(0LL, s[j][h2] - s[j][h1]);  // max(h2,hp)=h2 分支的候选值：加上当前列多出来的白格前缀和
                    suf[h2] = max(suf[h2 + 1], v);  // suf[h2] = max_{h2' >= h2}（f[h1][h2'] + 加成）
                }  // 后缀最大值构建完成
                for (int hp = 0; hp <= n; ++hp) {  // 枚举下一列（第 j+1 列）的高度 hp
                    long long add = max(0LL, s[j][hp] - s[j][h1]);  // 下一列更高时，当前列高出的白格也能计分
                    long long v1 = pre[hp] == inf ? inf : pre[hp] + add;  // h2 <= hp 时用前缀最大值转移
                    g[hp][h1] = max(v1, suf[hp + 1]);  // h2 > hp 时加成已包含在 suf 中，两部分取大即最优
                }  // hp 枚举结束
            }  // h1 枚举结束
            f.swap(g);  // 滚动：新状态换进 f，g 留作下一层复用
        }  // 各列转移完成
        long long ans = 0;  // 最后一列没有右邻居，总分至少为 0
        for (int h1 = 0; h1 <= n; ++h1) {  // 枚举最后一列高度 h1（即 k[n-1]）
            for (int h2 = 0; h2 <= n; ++h2) {  // 枚举倒数第二列高度 h2（即 k[n-2]）
                if (f[h1][h2] != inf) {  // 跳过不可达状态
                    ans = max(ans, f[h1][h2] + max(0LL, s[n - 1][h2] - s[n - 1][h1]));  // 补上最后一列只受左邻居影响的贡献
                }  // h2 枚举结束
            }  // h1 枚举结束
        }  // 答案计算完成
        return ans;  // 返回最大总分
    }  // 方法结束
};
