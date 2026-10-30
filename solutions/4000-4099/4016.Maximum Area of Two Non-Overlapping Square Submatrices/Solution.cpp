// 题目：4016. 两个不重叠子正方形的最大面积（Maximum Area of Two Non-Overlapping Square Submatrices）
// 思路：枚举两个正方形被一条水平线或竖直线分开。水平情况用两次 DP 分别求出切线上方与下方各自能放下的最大全 1 正方形边长，取两者较小值 t 即为两半可同时容纳的边长，面积 t²；竖直情况把矩阵转置后复用同一函数，最后取两种切法的最大值。
// 时间复杂度：O(m·n)，两次 DP 加一次转置都是线性扫描；空间复杂度：O(m·n)，两张 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxArea(vector<vector<int>>& mat) {  // mat：只含 0/1 的矩阵；返回两个等大且不重叠的全 1 正方形中单个正方形的最大面积
        return max(calc(mat), calc(transpose(mat)));  // calc 处理横切（上下两块），转置后同一函数即可处理竖切（左右两块），取两种切法的最优
    }  // maxArea 结束

private:  // 以下为内部辅助函数，不对外暴露
    int calc(const vector<vector<int>>& mat) {  // 横切情况：把矩阵切成上下两半，各取能放下的最大正方形边长，再取较小值
        int m = mat.size(), n = mat[0].size();  // 矩阵共 m 行 n 列

        vector<vector<int>> f(m + 1, vector<int>(n + 1));  // f[i][j]：以 (i, j) 为左上角的最大全 1 正方形边长（多开一行一列作为 0 边界）
        vector<int> g(m + 1), suf(m + 1);  // g[i]：上边界恰在第 i 行的最大正方形边长；suf[i]：完全落在第 i..m-1 行内的最大正方形边长

        for (int i = m - 1; i > 0; i--) {  // 自下而上枚举行；i 不从 0 开始，保证切线上方至少留一行
            for (int j = n - 1; j >= 0; j--) {  // 自右向左枚举列，依靠右侧、下方、右下三个已算好的状态递推
                if (mat[i][j]) {  // 格子可用才可能成为某个正方形的左上角
                    f[i][j] = min({f[i + 1][j],  // 候选一：下方相邻格的最大边长 f[i+1][j]
                                  f[i][j + 1],  // 候选二：右侧相邻格的最大边长 f[i][j+1]
                                  f[i + 1][j + 1]})  // 候选三：右下对角格的最大边长 f[i+1][j+1]
                        + 1;  // 三邻居取最小再加 1，即为以 (i, j) 为左上角的最大正方形边长
                    g[i] = max(g[i], f[i][j]);  // 更新「上边界在第 i 行」的最大边长
                }  // 当前格子处理完毕
            }  // 该行处理完毕
            suf[i] = max(suf[i + 1], g[i]);  // 后缀最大值：第 i 行及其下方能放下的最大正方形边长
        }  // 自下而上的 DP 结束

        f.assign(m + 1, vector<int>(n + 1));  // 清空 DP 表，改用「右下角」为基准的状态定义
        g.assign(m + 1, 0);  // 重置每行的最大边长
        vector<int> pre(m + 1);  // pre[i]：完全落在前 i 行（1-based 的 1..i 行）内的最大正方形边长

        for (int i = 1; i <= m; i++) {  // 用 1-based 下标自上而下枚举行
            for (int j = 1; j <= n; j++) {  // 自上而下、自左向右枚举列
                if (mat[i - 1][j - 1]) {  // 映射回 0-based 下标，判断格子是否可用
                    f[i][j] = min({f[i - 1][j],  // 候选一：上方相邻格的最大边长 f[i-1][j]
                                  f[i][j - 1],  // 候选二：左方相邻格的最大边长 f[i][j-1]
                                  f[i - 1][j - 1]})  // 候选三：左上对角格的最大边长 f[i-1][j-1]
                        + 1;  // 三邻居取最小再加 1，得到以 (i-1, j-1) 为右下角的最大正方形边长
                    g[i] = max(g[i], f[i][j]);  // 更新「下边界恰在第 i 行」的最大边长
                }  // 当前格子处理完毕
            }  // 该行处理完毕
            pre[i] = max(pre[i - 1], g[i]);  // 前缀最大值：前 i 行内能放下的最大正方形边长
        }  // 自左上角的 DP 结束

        int ans = 0;  // 答案（单个正方形的面积）；找不到两个正方形时保持 0
        for (int i = 1; i < m; i++) {  // 枚举水平切线：切在 1-based 第 i 行之后，上方为 1..i 行、下方为 i+1..m 行
            int t = min(pre[i], suf[i]);  // 两半都能放下边长 t 的正方形，t 取两半中较小的那个
            ans = max(ans, t * t);  // 两个正方形等大，单个面积 t²，取全局最大值
        }  // 所有切线枚举完毕

        return ans;  // 返回单个正方形的最大面积
    }  // calc 结束

    vector<vector<int>> transpose(const vector<vector<int>>& mat) {  // 矩阵转置：行列互换，把「竖切」问题转化为「横切」问题
        int m = mat.size(), n = mat[0].size();  // 原矩阵是 m 行 n 列

        vector<vector<int>> ans(n, vector<int>(m));  // 转置结果共有 n 行 m 列

        for (int i = 0; i < m; i++) {  // 遍历原矩阵的每一行
            for (int j = 0; j < n; j++) {  // 遍历该行的每一列
                ans[j][i] = mat[i][j];  // 行列交换：原矩阵的 (i, j) 放到新矩阵的 (j, i)
            }  // 该行转置完毕
        }  // 全部转置完毕

        return ans;  // 返回转置后的矩阵
    }  // transpose 结束
};  // 类定义结束