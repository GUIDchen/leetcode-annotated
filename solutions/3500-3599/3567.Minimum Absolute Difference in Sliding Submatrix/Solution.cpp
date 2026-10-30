// 题目：3567. 子矩阵的最小绝对差（Minimum Absolute Difference in Sliding Submatrix）
// 思路：对每个 k×k 子矩阵把元素取出并排序，最小绝对差一定出现在排序后的相邻元素之间；跳过数值相等的相邻对（它们的差为 0 但不属于“不同元素”），若子矩阵内元素全相同则答案为 0。
// 时间复杂度：O(m * n * k^2 log k)，共 (m-k+1)(n-k+1) 个子矩阵，每个收集 O(k^2) 个元素并排序；空间复杂度：O(k^2)，每个子矩阵的临时数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {  // grid：原矩阵；k：滑动子矩阵的边长；返回每个 k×k 子矩阵中不同元素的最小绝对差
        int m = grid.size(), n = grid[0].size();  // 矩阵的行数与列数
        vector<vector<int>> ans(m - k + 1, vector<int>(n - k + 1, 0));  // 答案矩阵共 (m-k+1) 行 (n-k+1) 列，先全部填 0
        for (int i = 0; i <= m - k; ++i) {  // 枚举子矩阵左上角的行号
            for (int j = 0; j <= n - k; ++j) {  // 枚举子矩阵左上角的列号
                vector<int> nums;  // 收集当前 k×k 子矩阵内的全部元素
                for (int x = i; x < i + k; ++x) {  // 遍历子矩阵的每一行
                    for (int y = j; y < j + k; ++y) {  // 遍历子矩阵的每一列
                        nums.push_back(grid[x][y]);  // 把元素收进一维数组，便于排序
                    }  // 列遍历结束
                }  // 行遍历结束
                ranges::sort(nums);  // 排序后，最小绝对差一定出现在相邻元素之间
                int d = INT_MAX;  // 用最大整数作哨兵，表示还没有找到不同的元素对
                for (int t = 1; t < nums.size(); ++t) {  // 从第二个元素起，与它的前一个比较
                    if (nums[t] != nums[t - 1]) {  // 数值相等的相邻对差为 0 但不算“不同元素”，必须跳过
                        d = min(d, abs(nums[t] - nums[t - 1]));  // 用当前相邻差值更新最小值
                    }  // 比较分支结束
                }  // 相邻扫描结束
                ans[i][j] = (d == INT_MAX) ? 0 : d;  // 没有不同元素时按题意记 0，否则写入最小绝对差
            }  // 列循环结束
        }  // 行循环结束
        return ans;  // 返回答案矩阵
    }  // 方法结束
};  // 类定义结束
