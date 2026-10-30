// 题目：2906. 构造乘积矩阵（Construct Product Matrix）
// 核心思路：第一遍逆序扫描，把每个位置「右下方所有元素（不含自身）」的乘积前缀写进答案；第二遍正序扫描，再乘上「左上方所有元素」的乘积，两半相乘即为除自身外全部元素之积，全程对 12345 取模。
// 时间复杂度：O(n*m)，每个格子只被常数次访问；空间复杂度：O(n*m)，额外只使用答案矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {  // grid 是 n 行 m 列的矩阵，返回值是同形状的乘积矩阵
        const int mod = 12345;  // 题目指定的取模常量
        int n = grid.size(), m = grid[0].size();  // 取出行数 n 与列数 m
        vector<vector<int>> p(n, vector<int>(m));  // 答案矩阵 p，尺寸与 grid 相同，先全部置 0
        long long suf = 1;  // suf 表示「当前格子之后所有元素」的乘积，空乘积为 1
        for (int i = n - 1; i >= 0; --i) {  // 第一遍：从最后一行开始逆序扫描
            for (int j = m - 1; j >= 0; --j) {  // 列也逆序遍历，保证 suf 确实是右下方全部元素的积
                p[i][j] = suf;  // 先把后缀乘积写进答案（此时还缺左上方的部分）
                suf = suf * grid[i][j] % mod;  // 再把当前元素累进后缀，供更靠左上方的位置使用
            }  // 列循环结束
        }  // 行循环结束
        long long pre = 1;  // pre 表示「当前格子之前所有元素」的乘积，空乘积为 1
        for (int i = 0; i < n; ++i) {  // 第二遍：正序扫描，把左侧乘积补上
            for (int j = 0; j < m; ++j) {  // 正序遍历每一列
                p[i][j] = p[i][j] * pre % mod;  // 后缀乘前缀正好是「除自身外所有元素」的积，边乘边取模防溢出
                pre = pre * grid[i][j] % mod;  // 把当前元素累进前缀，供右侧的位置使用
            }  // 列循环结束
        }  // 行循环结束
        return p;  // 返回构造完成的乘积矩阵
    }  // 方法结束
};  // 类定义结束