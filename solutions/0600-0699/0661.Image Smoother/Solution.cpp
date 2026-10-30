// 题目：661. 图片平滑器（Image Smoother）
// 核心思路：对每个格子枚举 3x3 邻域，统计合法邻居的和与个数，用整数除法向下取整。
// 时间复杂度：O(m * n)（每个格子固定检查 9 个位置）；空间复杂度：O(m * n) 存结果。
class Solution {  // LeetCode 约定的题解类
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {  // 把每个格子的值换成它 3x3 邻域（含自身）的平均值，向下取整
        int m = img.size(), n = img[0].size();  // m 是行数，n 是列数
        vector<vector<int>> ans(m, vector<int>(n));  // 结果矩阵，尺寸与输入相同
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                int s = 0, cnt = 0;  // s 累积邻域和，cnt 记录实际参与平均的格子数
                for (int x = i - 1; x <= i + 1; ++x) {  // 邻域行范围 [i-1, i+1]
                    for (int y = j - 1; y <= j + 1; ++y) {  // 邻域列范围 [j-1, j+1]
                        if (x < 0 || x >= m || y < 0 || y >= n) {  // 坐标越界的邻居直接跳过（边界格子的邻居不足 9 个）
                            continue;  // 跳过越界坐标
                        }
                        ++cnt;  // 合法邻居计数加一
                        s += img[x][y];  // 累加该邻居的值
                    }
                }
                ans[i][j] = s / cnt;  // 整数除法天然向下取整，符合题目要求
            }
        }
        return ans;  // 返回平滑后的矩阵
    }
};  // 题解类定义结束
