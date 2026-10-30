// 题目：2508. 添加边使所有节点度数都为偶数（Add Edges to Make Degrees of All Nodes Even）
// 思路：统计当前度数为奇数的节点集合，最多只能加两条边；奇度点为 0 个直接成立，2 个可一条边相连或隔一个中转点连两条，4 个则检查三种两两配对的边是否都不存在。
// 时间复杂度：O(n + m) 建图与枚举，n 为节点数、m 为边数；空间复杂度：O(n + m) 存邻接表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPossible(int n, vector<vector<int>>& edges) {  // n：节点数（编号 1..n）；edges：已有的无向边
        vector<unordered_set<int>> g(n + 1);  // 邻接表：g[i] 存节点 i 的邻居，用哈希集合便于 O(1) 判断某条边是否存在
        for (auto& e : edges) {  // 逐条读入已有的边
            int a = e[0], b = e[1];  // 一条边的两个端点
            g[a].insert(b);  // 把 b 登记为 a 的邻居
            g[b].insert(a);  // 无向边需要双向登记
        }
        vector<int> vs;  // 收集所有「当前度数为奇数」的节点
        for (int i = 1; i <= n; ++i) {  // 遍历全部节点（编号从 1 开始）
            if (g[i].size() % 2) {  // 度数为奇数，需要被新增的边「翻转」成偶数
                vs.emplace_back(i);  // 记录这个奇度节点
            }
        }
        if (vs.size() == 0) {  // 没有奇度节点，一条边都不用加
            return true;  // 已经满足所有节点度数为偶数
        }
        if (vs.size() == 2) {  // 恰好两个奇度节点：可以一条边直连，或用两条边经中转点
            int a = vs[0], b = vs[1];  // 取出这两个奇度节点
            if (!g[a].count(b)) return true;  // a、b 之间原本没有边，直接连一条即可
            for (int c = 1; c <= n; ++c) {  // 否则尝试所有可能的中转点 c，加 a-c 与 c-b 两条边
                if (a != b && b != c && !g[a].count(c) && !g[c].count(b)) {  // 中转点不能是端点自身，且两条新边都必须不存在
                    return true;  // 找到合法中转方案，返回可以
                }
            }
            return false;  // 所有中转点都不行，无法只用两条边修正
        }
        if (vs.size() == 4) {  // 四个奇度节点：两条新边必须两两配对，共三种配对方式
            int a = vs[0], b = vs[1], c = vs[2], d = vs[3];  // 取出四个奇度节点
            if (!g[a].count(b) && !g[c].count(d)) return true;  // 配对 (a,b) 与 (c,d)，且这两条边都还不存在
            if (!g[a].count(c) && !g[b].count(d)) return true;  // 配对 (a,c) 与 (b,d)
            if (!g[a].count(d) && !g[b].count(c)) return true;  // 配对 (a,d) 与 (b,c)
            return false;  // 三种配对都被已有边占用，无法完成
        }
        return false;  // 奇度节点数不是 0/2/4，两条边无法全部消掉，返回不可能
    }
};