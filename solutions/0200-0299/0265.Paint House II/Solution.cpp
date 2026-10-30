// 题目：265. 粉刷房子 II（Paint House II）
// 思路：f[j] 表示刷到当前房子、最后一间用颜色 j 的最小花费；换房时对每种颜色 j 取上一行除 j 外的最小值累加。
// 时间复杂度：O(n·k²)，每间房每种颜色都要扫一遍 k 种颜色；空间复杂度：O(k)，只需保存相邻两层的 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    int minCostII(vector<vector<int>>& costs) {  // costs[i][j] 是把第 i 间房刷成颜色 j 的花费
        int n = costs.size(), k = costs[0].size();  // n 为房子数，k 为颜色数
        vector<int> f = costs[0];  // f 记录刷完第 0 间房、最后一间用各颜色的最小花费，初始就是第 0 行的花费
        for (int i = 1; i < n; ++i) {  // 从第 1 间房开始逐间向后推
            vector<int> g = costs[i];  // g 是当前行的花费副本，避免直接覆盖原始输入
            for (int j = 0; j < k; ++j) {  // 枚举当前房子要刷的颜色 j
                int t = INT_MAX;  // t 记录上一行里除颜色 j 以外的最小花费
                for (int h = 0; h < k; ++h) {  // 枚举上一间房用过的颜色 h
                    if (h != j) {  // 相邻房子颜色不能相同，所以跳过 h == j
                        t = min(t, f[h]);  // 在合法颜色里取最小花费
                    }  // 颜色不合法时的判断结束
                }  // 内层颜色枚举结束
                g[j] += t;  // 当前颜色 j 的花费 = 本行花费 + 上一行除 j 外的最小花费
            }  // 颜色枚举结束
            f = move(g);  // 用本行结果替换上一行，move 避免多余拷贝，滚动数组把空间压到 O(k)
        }  // 房子枚举结束
        return *min_element(f.begin(), f.end());  // 最后一间房用哪种颜色都行，取最小值即总最小花费
    }  // 方法结束
};  // 类定义结束