// 题目：861. 翻转矩阵后的得分（Score After Flipping Matrix）
// 思路：首位是 0 的行先整行翻转，保证最高位全为 1；再逐列比较 0 与 1 的个数，1 少就整列翻转，使每列 1 的数量尽量多。
// 时间复杂度：O(m·n)，需要遍历矩阵两遍；空间复杂度：O(1)，直接在原矩阵上翻转。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int matrixScore(vector<vector<int>>& grid) {  // grid：只含 0/1 的矩阵，返回翻转行和列后能得到的最大二进制得分
        int m = grid.size(), n = grid[0].size();  // m、n 分别是矩阵的行数与列数
        for (int i = 0; i < m; ++i) {  // 逐行检查首位
            if (grid[i][0] == 0) {  // 首位为 0 时整行翻转，保证最高位贡献最大
                for (int j = 0; j < n; ++j) {  // 遍历这一行的每一列
                    grid[i][j] ^= 1;  // 按位异或 1 实现 0/1 取反
                }  // 内层 for 结束
            }  // if 分支结束
        }  // 外层 for 结束
        int ans = 0;  // 累加最终得分
        for (int j = 0; j < n; ++j) {  // 逐列确定这一列是否翻转
            int cnt = 0;  // 统计这一列中 1 的个数
            for (int i = 0; i < m; ++i) {  // 遍历每一行取该列的取值
                cnt += grid[i][j];  // 累加该列 1 的个数
            }  // 内层 for 结束
            ans += max(cnt, m - cnt) * (1 << (n - j - 1));  // 取 1 与 0 中较多的个数，乘以该列对应的二进制权重
        }  // 外层 for 结束
        return ans;  // 返回最大得分
    }  // matrixScore 方法结束
};  // Solution 类定义结束