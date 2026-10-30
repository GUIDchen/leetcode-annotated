// 题目：2428. 沙漏的最大总和（Maximum Sum of an Hourglass）
// 核心思路：枚举每个可能的沙漏中心，累加 3x3 方块后减去中间行左右两格，取最大值。
// 时间复杂度：O(m*n)，每个中心只做 9 次累加；空间复杂度：O(1)，只用常数个临时变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSum(vector<vector<int>>& grid) {  // grid 是输入矩阵，返回所有沙漏中的最大总和
        int m = grid.size(), n = grid[0].size();  // m 是行数，n 是列数（题面保证矩阵非空）
        int ans = 0;  // ans 记录当前见过的最大沙漏总和；总和非负，初值 0 安全
        for (int i = 1; i < m - 1; ++i) {  // 沙漏中心不能落在首行或末行，所以行下标从 1 枚举到 m-2
            for (int j = 1; j < n - 1; ++j) {  // 沙漏中心不能落在首列或末列，所以列下标从 1 枚举到 n-2
                int s = -grid[i][j - 1] - grid[i][j + 1];  // 先减去中间行的左右两格，它们不属于沙漏形状
                for (int x = i - 1; x <= i + 1; ++x) {  // 遍历以 (i, j) 为中心的上、中、下三行
                    for (int y = j - 1; y <= j + 1; ++y) {  // 遍历以 (i, j) 为中心的左、中、右三列
                        s += grid[x][y];  // 把 3x3 方形内的这一格累加进来
                    }  // 内层列循环结束
                }  // 外层行循环结束
                ans = max(ans, s);  // 用当前沙漏的总和更新答案
            }  // 列中心枚举结束
        }  // 行中心枚举结束
        return ans;  // 返回最大沙漏总和
    }  // maxSum 方法结束
};  // Solution 类定义结束