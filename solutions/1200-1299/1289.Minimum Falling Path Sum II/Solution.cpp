// 题目：1289. 下降路径最小和 II（Minimum Falling Path Sum II）
// 核心思路：滚动数组 DP，f[j] 表示上一行落在第 j 列的最小路径和；本行每列累加「上一行不同列的最小值」，逐行递推。
// 时间复杂度：O(n^3)，每行要对 n 列各扫 n 列；空间复杂度：O(n)，只保留上一行与当前行两组状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minFallingPathSum(vector<vector<int>>& grid) {  // grid 是 n×n 矩阵，返回下降路径最小和，且相邻两行不能选同一列
        int n = grid.size();  // n 是矩阵的边长
        vector<int> f(n);  // f[j] 表示处理到上一行、且落在第 j 列时的最小路径和，初始全 0
        const int inf = 1e9;  // inf 是一个足够大的数，用来表示「当前还没有合法前驱」
        for (const auto& row : grid) {  // 逐行向下推进动态规划
            vector<int> g = row;  // g 拷贝当前行，作为本行的 DP 结果
            for (int i = 0; i < n; ++i) {  // 枚举本行选中的列 i
                int t = inf;  // t 记录上一行中「列号不等于 i」的最小 f 值
                for (int j = 0; j < n; ++j) {  // 枚举上一行所在的列 j
                    if (j != i) {  // 只有 j != i 才可选，因为相邻两行不能选同一列
                        t = min(t, f[j]);  // 用较小值更新 t
                    }  // 结束 if 分支
                }  // 结束列枚举循环
                g[i] += (t == inf ? 0 : t);  // 把最优前驱累加到当前格子；第一行没有前驱时 t 仍为 inf，按 0 处理
            }  // 结束本行各列的枚举
            f = move(g);  // 用本行结果替换 f，move 避免一次深拷贝
        }  // 结束行循环
        return ranges::min(f);  // 最后一行里的最小值就是整条下降路径的最小和
    }  // 结束函数
};  // 结束题解类
