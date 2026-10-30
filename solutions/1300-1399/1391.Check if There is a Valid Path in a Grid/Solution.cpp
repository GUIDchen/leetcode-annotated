// 题目：1391. 检查网格中是否存在有效路径（Check if There is a Valid Path in a Grid）
// 思路：并查集；对每个格子按其管道类型检查左右上下四个邻居是否有能对接的开口，能对接就合并，最后判断起点与终点是否同属一个集合。
// 时间复杂度：O(m*n*α(m*n))，带路径压缩的 find 近似常数；空间复杂度：O(m*n)，并查集父数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> p;  // 并查集父数组，下标是格子编号 i * n + j

    bool hasValidPath(vector<vector<int>>& grid) {  // grid：每个格子存放管道类型 1~6
        int m = grid.size();  // 行数
        int n = grid[0].size();  // 列数
        p.resize(m * n);  // 并查集大小等于格子总数
        for (int i = 0; i < p.size(); ++i) p[i] = i;  // 初始化：让每个格子先自成一个集合
        auto left = [&](int i, int j) {  // 尝试把当前格与左邻居合并
            if (j > 0 && (grid[i][j - 1] == 1 || grid[i][j - 1] == 4 || grid[i][j - 1] == 6)) {  // 左邻居存在，且它的右侧有开口（类型 1、4、6 才有右出口）
                p[find(i * n + j)] = find(i * n + j - 1);  // 合并当前格与左邻居所在集合
            }  // if 结束
        };  // lambda left 定义结束
        auto right = [&](int i, int j) {  // 尝试把当前格与右邻居合并
            if (j < n - 1 && (grid[i][j + 1] == 1 || grid[i][j + 1] == 3 || grid[i][j + 1] == 5)) {  // 右邻居存在，且它的左侧有开口（类型 1、3、5 才有左出口）
                p[find(i * n + j)] = find(i * n + j + 1);  // 合并当前格与右邻居所在集合
            }  // if 结束
        };  // lambda right 定义结束
        auto up = [&](int i, int j) {  // 尝试把当前格与上邻居合并
            if (i > 0 && (grid[i - 1][j] == 2 || grid[i - 1][j] == 3 || grid[i - 1][j] == 4)) {  // 上邻居存在，且它的下方有开口（类型 2、3、4 才有下出口）
                p[find(i * n + j)] = find((i - 1) * n + j);  // 合并当前格与上邻居所在集合
            }  // if 结束
        };  // lambda up 定义结束
        auto down = [&](int i, int j) {  // 尝试把当前格与下邻居合并
            if (i < m - 1 && (grid[i + 1][j] == 2 || grid[i + 1][j] == 5 || grid[i + 1][j] == 6)) {  // 下邻居存在，且它的上方有开口（类型 2、5、6 才有上出口）
                p[find(i * n + j)] = find((i + 1) * n + j);  // 合并当前格与下邻居所在集合
            }  // if 结束
        };  // lambda down 定义结束
        for (int i = 0; i < m; ++i) {  // 逐行遍历网格
            for (int j = 0; j < n; ++j) {  // 逐列遍历网格
                int e = grid[i][j];  // 当前格子的管道类型
                if (e == 1) {  // 类型 1：左右直通
                    left(i, j);  // 与左邻居连通
                    right(i, j);  // 与右邻居连通
                } else if (e == 2) {  // 类型 2：上下直通
                    up(i, j);  // 与上邻居连通
                    down(i, j);  // 与下邻居连通
                } else if (e == 3) {  // 类型 3：左 + 下
                    left(i, j);  // 与左邻居连通
                    down(i, j);  // 与下邻居连通
                } else if (e == 4) {  // 类型 4：右 + 下
                    right(i, j);  // 与右邻居连通
                    down(i, j);  // 与下邻居连通
                } else if (e == 5) {  // 类型 5：左 + 上
                    left(i, j);  // 与左邻居连通
                    up(i, j);  // 与上邻居连通
                } else {  // 类型 6：右 + 上
                    right(i, j);  // 与右邻居连通
                    up(i, j);  // 与上邻居连通
                }  // if-else 链结束
            }  // 内层列循环结束
        }  // 外层行循环结束
        return find(0) == find(m * n - 1);  // 起点 0 与终点 m*n-1 在同一集合，说明存在有效路径
    }

    int find(int x) {  // 并查集查找根节点，带路径压缩
        if (p[x] != x) p[x] = find(p[x]);  // x 不是根节点时，递归找到根并让路径上的点直接挂在根上
        return p[x];  // 返回根节点下标
    }
};