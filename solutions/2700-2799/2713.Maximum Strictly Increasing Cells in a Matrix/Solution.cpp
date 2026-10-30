// 题目：2713. 矩阵中严格递增的单元格数（Maximum Strictly Increasing Cells in a Matrix）
// 思路：按数值从小到大分组处理；dp[i][j] = 1 + max(该行历史最大值, 该列历史最大值)，同值单元格先全部算完再统一回写行列最大值，避免同值互相转移。
// 时间复杂度：O(mn log(mn))，排序分组为主；空间复杂度：O(mn)，存放分组坐标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxIncreasingCells(vector<vector<int>>& mat) {  // mat：m 行 n 列的整数矩阵，返回最长严格递增路径的单元格数
        int m = mat.size(), n = mat[0].size();  // m 为行数，n 为列数
        map<int, vector<pair<int, int>>> g;  // 按数值分组：键是单元格的值，值是所有取该值的单元格坐标，map 保证按键升序遍历
        for (int i = 0; i < m; ++i) {  // 遍历每一行
            for (int j = 0; j < n; ++j) {  // 遍历每一列
                g[mat[i][j]].emplace_back(i, j);  // 把坐标 (i, j) 归入它对应数值的分组
            }
        }
        vector<int> rowMax(m);  // rowMax[i]：第 i 行当前能接出的最长递增路径长度
        vector<int> colMax(n);  // colMax[j]：第 j 列当前能接出的最长递增路径长度
        int ans = 0;  // ans：全局最长长度，即最终答案
        for (auto& [_, pos] : g) {  // 按数值从小到大处理每个分组，保证转移来源的值都更小
            vector<int> mx;  // 暂存本组每个单元格的 dp 值，避免同值之间错误地互相转移
            for (auto& [i, j] : pos) {  // 第一轮：只根据更小值留下的行列最大值计算 dp
                mx.push_back(max(rowMax[i], colMax[j]) + 1);  // 从同行最大值或同列最大值接过来，再把自己算作一格，所以 +1
                ans = max(ans, mx.back());  // 顺带用本组最新结果刷新全局答案
            }
            for (int k = 0; k < mx.size(); ++k) {  // 第二轮：本组 dp 全部算完后，才统一写回行列最大值
                auto& [i, j] = pos[k];  // 取出第 k 个单元格的坐标
                rowMax[i] = max(rowMax[i], mx[k]);  // 用本格 dp 更新所在行的最大值
                colMax[j] = max(colMax[j], mx[k]);  // 用本格 dp 更新所在列的最大值
            }
        }
        return ans;  // 返回最长严格递增路径包含的单元格个数
    }
};