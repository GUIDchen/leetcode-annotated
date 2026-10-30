// 题目：2371. 最小化网格中的最大值（Minimize Maximum Value in a Grid）
// 核心思路：把格子按原值升序排序，依次贪心填入 max(本行已填最大值, 本列已填最大值) + 1，既能保持行列大小关系，又能让整体最大值尽量小。
// 时间复杂度：O(mn log(mn))，排序主导；空间复杂度：O(mn)，排序数组与答案矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> minScore(vector<vector<int>>& grid) {  // grid：带重复值的非负整数矩阵，返回同形状的新矩阵
        vector<tuple<int, int, int>> nums;  // 把每个格子打包成三元组 (原值, 行号, 列号)，方便排序后还原位置
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        for (int i = 0; i < m; ++i) {  // 枚举每一行
            for (int j = 0; j < n; ++j) {  // 枚举该行的每一列
                nums.push_back({grid[i][j], i, j});  // 把「值 + 位置」存起来；值放第一位，排序时就会按值比较
            }  // 本行枚举结束
        }  // 所有格子都已打包完成
        sort(nums.begin(), nums.end());  // 按原值升序排列：值相同的格子之间按行列再定序，结果依然合法
        vector<int> rowMax(m);  // rowMax[i]：第 i 行目前填过的最大值，初始为 0
        vector<int> colMax(n);  // colMax[j]：第 j 列目前填过的最大值，初始为 0
        vector<vector<int>> ans(m, vector<int>(n));  // 答案矩阵，先全部置 0，之后按排序顺序填数
        for (auto [_, i, j] : nums) {  // 按原值从小到大填格子：轮到我时，比我小的格子都已经填好且已更新行、列最大值
            ans[i][j] = max(rowMax[i], colMax[j]) + 1;  // 必须同时大于本行与本列已有的最大值，取两者较大者加一，且保持原来的严格大小关系
            rowMax[i] = colMax[j] = ans[i][j];  // 填完后同步刷新行最大值与列最大值，供后面更大的格子使用
        }  // 所有格子填完
        return ans;  // 返回构造出的矩阵
    }  // 方法结束
};  // 类定义结束