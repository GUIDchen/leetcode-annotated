// 3613. Minimize Maximum Component Cost / 最小化连通分量的最大成本
// 核心思路：把边按权值升序做 Kruskal 合并，连通块数首次降到 k 时最后加入的边权即最小可能的最大分量成本。
// 复杂度：时间复杂度 O(E log E)，空间复杂度 O(n)，E 为边数。
class Solution {  // 定义题解类
public:  // 公有成员：对外提供 minCost
    int minCost(int n, vector<vector<int>>& edges, int k) {  // 求把图分成至多 k 个连通块时，各块内最贵边权的最小上界
        if (k == n) {  // 特判：若每个点自成一 块
            return 0;  // 无需任何边，成本为 0
        }  // 结束特判
        vector<int> p(n);  // 并查集父数组，初始每个点独立
        ranges::iota(p, 0);  // 初始化 p[i] = i
        ranges::sort(edges, {}, [](const auto& e) { return e[2]; });  // 按边权升序排序，为 Kruskal 做准备
        auto find = [&](this auto&& find, int x) -> int {  // 递归 find：带路径压缩，this auto&& 让 Lambda 可以递归调用自身
            if (p[x] != x) {  // 未指向自己说明还没到根
                p[x] = find(p[x]);  // 递归压缩，并把父指针直接更新到根
            }  // 结束递归分支
            return p[x];  // 返回根节点
        };  // find 闭包定义结束
        int cnt = n;  // cnt 记录当前连通块数量，初始 n 块
        for (const auto& e : edges) {  // 依次尝试加入每条边
            int u = e[0], v = e[1], w = e[2];  // 取出边的两个端点和权值
            int pu = find(u), pv = find(v);  // 找到两个端点所在集合的根
            if (pu != pv) {  // 只有端点属于不同连通块才合并
                p[pu] = pv;  // 合并两个集合
                if (--cnt <= k) {  // 块数减一后若已不超过 k
                    return w;  // 当前边权就是最大分量成本
                }  // 结束块数判断
            }  // 结束合并分支
        }  // 结束遍历
        return 0;  // 兜底返回 0
    }  // 方法结束
};  // 类定义结束