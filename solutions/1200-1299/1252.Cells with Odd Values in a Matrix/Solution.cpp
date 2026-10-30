// 题目：1252. 奇数值单元格的数目（Cells with Odd Values in a Matrix）
// 思路：按题意直接开一个 m×n 矩阵，每个索引把对应整行与整列各加一，最后统计值为奇数的格子数。
// 时间复杂度：O(k(m+n)+mn)，k 为索引个数；空间复杂度：O(mn)，用于存放矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int oddCells(int m, int n, vector<vector<int>>& indices) {  // m 行 n 列；indices 中每个 [r, c] 表示第 r 行与第 c 列各加 1；返回值为奇数的格子数
        vector<vector<int>> g(m, vector<int>(n));  // 直接按题意开 m×n 矩阵，初值全 0；数据规模很小，模拟即可
        for (auto& e : indices) {  // 逐条取出加一操作（e 是形如 [r, c] 的二元组）
            int r = e[0], c = e[1];  // 拆出本条操作的行号 r 和列号 c
            for (int i = 0; i < m; ++i) {  // 先把第 c 列整列加一
                ++g[i][c];  // 列上第 i 行的格子加一
            }
            for (int j = 0; j < n; ++j) {  // 再把第 r 行整行加一
                ++g[r][j];  // 行上第 j 列的格子加一
            }
        }
        int ans = 0;  // ans 用来统计最终值为奇数的格子个数
        for (auto& row : g) {  // 遍历矩阵的每一行
            for (int v : row) {  // 遍历该行里的每个格子值 v
                ans += v % 2;  // v 为奇数时 v % 2 == 1、为偶数时为 0，直接累加即完成计数
            }
        }
        return ans;  // 返回奇数值格子的总数
    }
};