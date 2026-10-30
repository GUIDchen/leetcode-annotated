// 题目：2373. 矩阵中的局部最大值（Largest Local Values in a Matrix）
// 核心思路：对每个左上角 (i, j) 直接枚举 3×3 窗口取最大值，填进尺寸为 (n-2)×(n-2) 的答案矩阵。
// 时间复杂度：O(n²)，共 (n-2)² 个窗口、每窗口固定 9 个元素；空间复杂度：O(n²)，存放答案矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {  // grid：n×n 的方阵，返回每个 3×3 子矩阵最大值组成的 (n-2)×(n-2) 矩阵
        int n = grid.size();  // 矩阵边长为 n，子矩阵左上角只能取到 n-3，所以答案维度是 n-2
        vector<vector<int>> ans(n - 2, vector<int>(n - 2));  // 答案矩阵按 (n-2)×(n-2) 预分配，元素默认是 0
        for (int i = 0; i < n - 2; ++i) {  // 枚举每个窗口的左上角行号 i
            for (int j = 0; j < n - 2; ++j) {  // 枚举每个窗口的左上角列号 j
                for (int x = i; x <= i + 2; ++x) {  // 遍历 3×3 窗口的三行
                    for (int y = j; y <= j + 2; ++y) {  // 遍历 3×3 窗口的三列
                        ans[i][j] = max(ans[i][j], grid[x][y]);  // 用窗口内元素不断刷新最大值；初值 0 不大于任何非负元素，因此不会影响结果
                    }  // 该窗口的列枚举完毕
                }  // 该窗口的行枚举完毕
            }  // 第 i 行所有窗口处理完
        }  // 所有窗口处理完
        return ans;  // 返回每个 3×3 局部的最大值矩阵
    }  // 方法结束
};  // 类定义结束