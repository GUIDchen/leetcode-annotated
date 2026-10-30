// 题目：2684. 矩阵中移动的最大次数（Maximum Number of Moves in a Grid）
// 思路：按列做 BFS，用集合 q 记录上一列可以到达的行；逐列向右侧三个方向扩展严格更大的格子，集合为空时当前列号就是答案。
// 时间复杂度：O(m*n)，每个格子最多被访问常数次；空间复杂度：O(m)，两个集合最多存 m 行。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxMoves(vector<vector<int>>& grid) {  // grid：行列递增移动的矩阵
        int m = grid.size(), n = grid[0].size();  // m、n 分别是行数与列数
        unordered_set<int> q, t;  // q：当前列可达的行集合；t：下一列可达的行集合
        for (int i = 0; i < m; ++i) {  // 第 0 列任意一行都可以作为起点
            q.insert(i);  // 把所有行号放进起始集合
        }  // 起点集合初始化完成
        for (int j = 0; j < n - 1; ++j) {  // 逐列向右推进，最多走到倒数第二列
            t.clear();  // 清空上一轮收集的下一列集合
            for (int i : q) {  // 遍历当前列所有可达的行
                for (int k = i - 1; k <= i + 1; ++k) {  // 尝试右下、右、右上三个方向
                    if (k >= 0 && k < m && grid[i][j] < grid[k][j + 1]) {  // 行号不越界且目标格严格更大才能移动
                        t.insert(k);  // 记录下一列可达的行
                    }  // 分支结束
                }  // 三个方向尝试完毕
            }  // 当前行处理完毕
            if (t.empty()) {  // 下一列一个格子都到不了，说明走不动了
                return j;  // 已经走了 j 步，返回 j
            }  // 分支结束
            q.swap(t);  // 把下一列集合并入当前集合，继续推进
        }  // 列循环结束
        return n - 1;  // 一直走到最后一列，共走了 n-1 步
    }  // 方法结束
};  // 类定义结束