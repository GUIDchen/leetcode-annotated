// 题目：1719. 重构一棵树的方案数（Number Of Ways To Reconstruct A Tree）难度：困难
// 思路：pairs 给出树上的“祖先关系”边。先建邻接表并按度数（祖先个数）升序自底向上扫描，每个点 x 后面第一个与它相邻的点 y 就是它的父亲；若 x 的某个邻居 z 不是 y 的邻居，说明祖先关系自相矛盾返回 0；若某对父子度数相同则方案数至少为 2；找不到父亲的点（根）多于 1 个也返回 0。
// 时间复杂度：O(m^2)，m = 510 为编号上界（建矩阵、排序、逐点校验邻居）；空间复杂度：O(m^2)，邻接矩阵与邻接表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int checkWays(vector<vector<int>>& pairs) {  // pairs：祖先关系边集，返回 0/1/2 种重构方案数
        vector<vector<bool>> g(510, vector<bool>(510));  // 邻接布尔矩阵：g[a][b] 表示 a 与 b 之间有祖先关系边
        vector<vector<int>> v(510);  // v[a]：a 的所有祖先（图中与 a 相邻的点）
        for (auto& p : pairs) {  // 逐条边建图
            int x = p[0], y = p[1];  // 取出这条边的两个端点
            g[x][y] = g[y][x] = 1;  // 邻接矩阵双向标记
            v[x].push_back(y);  // x 的祖先列表加入 y
            v[y].push_back(x);  // y 的祖先列表加入 x
        }
        vector<int> nodes;  // 记录所有出现过的编号
        for (int i = 1; i <= 500; ++i) {  // 题目给出的编号范围是 1..500
            if (v[i].size()) {  // 只统计出现在 pairs 里的点
                nodes.push_back(i);  // 收集该点
                g[i][i] = 1;  // 自己也算自己的祖先，方便后面做“包含”判断
            }
        }
        sort(nodes.begin(), nodes.end(), [&](int x, int y) -> bool { return v[x].size() < v[y].size(); });  // 按度数升序：祖先少的点在树中层级更低，先处理
        bool equal = 0;  // 是否存在一对度数相同的父子（此时至少有两棵树都合法）
        int root = 0;  // 找不到父亲的点数，即候选根的数量
        for (int i = 0; i < nodes.size(); ++i) {  // 自底向上为每个点确定父亲
            int x = nodes[i];  // 当前正在确定父亲的点
            int j = i + 1;  // 从度数比它大的点开始找父亲
            for (; j < nodes.size() && !g[x][nodes[j]]; ++j)  // 一直往后跳到第一个与 x 相邻的点（父亲候选）
                ;  // 空循环体：所有推进逻辑都写在循环头里
            if (j < nodes.size()) {  // 找到了父亲候选 y
                int y = nodes[j];  // y 就是 x 的父亲
                if (v[x].size() == v[y].size()) equal = 1;  // 父子度数相同：两者可互换，方案不止一种
                for (int z : v[x])  // 遍历 x 的每个祖先 z
                    if (!g[y][z])  // z 也必须是 y 的祖先，否则祖先关系矛盾
                        return 0;  // 无法构树
            } else  // 后面没有相邻点，说明 x 是候选根
                ++root;  // 根的数量加一
        }
        if (root > 1) return 0;  // 根多于一个：图不连通，无法构成一棵树
        if (equal) return 2;  // 存在可互换的父子，两种方案都合法
        return 1;  // 否则方案唯一
    }  // checkWays 方法结束
};  // Solution 类结束