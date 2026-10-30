// 题目：3239. 最少翻转次数使二进制矩阵回文 I（Minimum Number of Flips to Make Binary Grid Palindromic I）
// 思路：题目只要求行回文或列回文之一，分别统计两种方案需要的翻转次数再取较小值；每对不对称的格子至少翻一次，翻一次即可。
// 时间复杂度：O(m × n)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minFlips(vector<vector<int>>& grid) {  // grid：0/1 组成的矩阵
        int m = grid.size(), n = grid[0].size();  // m 行数，n 列数
        int cnt1 = 0, cnt2 = 0;  // cnt1：让每一行都回文所需的翻转数；cnt2：让每一列都回文所需的翻转数
        for (const auto& row : grid) {  // 第一遍：逐行检查左右对称的两个格子
            for (int j = 0; j < n / 2; ++j) {  // 只看前一半列，与对称列 n-j-1 配对
                if (row[j] != row[n - j - 1]) {  // 对称位置的值不同，必须翻转其中一个
                    ++cnt1;  // 计入「行回文」的代价
                }  // if 结束
            }  // 内层 for 结束
        }  // 外层 for 结束
        for (int j = 0; j < n; ++j) {  // 第二遍：逐列检查上下对称的两个格子
            for (int i = 0; i < m / 2; ++i) {  // 只看前一半行，与对称行 m-i-1 配对
                if (grid[i][j] != grid[m - i - 1][j]) {  // 对称位置的值不同，必须翻转其中一个
                    ++cnt2;  // 计入「列回文」的代价
                }  // if 结束
            }  // 内层 for 结束
        }  // 外层 for 结束
        return min(cnt1, cnt2);  // 两种方案取代价较小者
    }  // 方法结束
};  // 类结束
