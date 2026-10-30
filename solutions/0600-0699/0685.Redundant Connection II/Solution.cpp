// 题目：685. 冗余连接 II（Redundant Connection II）
// 思路：先判断是否存在入度为 2 的节点；若存在，多余边必在其两条入边中，先删较晚的一条并检查是否仍成环；若不存在，则同 684 用并查集找出成环的边。
// 时间复杂度：O(n α(n))，并查集操作近似常数；空间复杂度：O(n)，入度数组与父数组。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {  // edges：按顺序给出的有向边
        int n = edges.size();  // 节点数等于边数
        vector<int> ind(n);  // 入度数组：ind[i] 表示节点 i+1 的入度
        for (const auto& e : edges) {  // 遍历所有边统计入度
            ++ind[e[1] - 1];  // 边 e 的终点入度加 1
        }
        vector<int> dup;  // 保存所有指向「入度为 2 的节点」的边下标
        for (int i = 0; i < n; ++i) {  // 逐条检查每条边
            if (ind[edges[i][1] - 1] == 2) {  // 该边终点入度为 2，说明它是候选的多余边
                dup.push_back(i);  // 记下这条边的下标
            }
        }
        vector<int> p(n);  // 并查集父数组
        iota(p.begin(), p.end(), 0);  // 初始时每个节点各自构成一个集合
        function<int(int)> find = [&](int x) {  // 递归找根，同时做路径压缩
            return x == p[x] ? x : p[x] = find(p[x]);  // 自己是根就返回，否则把父指针直接指向根
        };
        if (!dup.empty()) {  // 情况一：存在某个节点有两条入边
            for (int i = 0; i < n; ++i) {  // 先假设删掉较晚的那条入边 dup[1]
                if (i == dup[1]) {  // 跳过 dup[1] 这条边
                    continue;  // 相当于把它删掉
                }
                int pu = find(edges[i][0] - 1);  // 起点所在集合的根（1-based 转下标）
                int pv = find(edges[i][1] - 1);  // 终点所在集合的根
                if (pu == pv) {  // 删掉 dup[1] 后仍有环，说明删错了边
                    return edges[dup[0]];  // 应该删的是较早的那条入边
                }
                p[pu] = pv;  // 合并两个集合
            }
            return edges[dup[1]];  // 删掉 dup[1] 后无环，它就是多出来的边
        }
        for (int i = 0;; ++i) {  // 情况二：没有入度为 2 的节点，多余边一定在环上
            int pu = find(edges[i][0] - 1);  // 起点所在集合的根
            int pv = find(edges[i][1] - 1);  // 终点所在集合的根
            if (pu == pv) {  // 两端点已连通，这条边构成环
                return edges[i];  // 它就是多余的边
            }
            p[pu] = pv;  // 合并两个集合
        }
    }
};
