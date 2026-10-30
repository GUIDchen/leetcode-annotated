// 题目：1135. 最低成本连通所有城市（Connecting Cities With Minimum Cost）
// 思路：Kruskal 最小生成树：把所有边按成本升序排序，用并查集逐条试边，只保留两端点不同集合的边。
// 时间复杂度：O(m log m) 排序 + O(m α(n)) 并查集；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCost(int n, vector<vector<int>>& connections) {  // n 是城市个数，connections 每项是 [城市1, 城市2, 成本]（城市编号从 1 开始），返回把所有城市连通的最小成本，做不到返回 -1
        vector<int> p(n);  // 并查集的父节点数组，p[i] 表示城市 i 的父节点
        iota(p.begin(), p.end(), 0);  // 初始时每个城市自成一个连通块，父节点都指向自己（iota 从 0 连续填充）
        sort(connections.begin(), connections.end(), [](auto& a, auto& b) { return a[2] < b[2]; });  // Kruskal 第一步：按成本从小到大排序，贪心时永远先挑最便宜的边
        int ans = 0;  // 累计已被选入生成树的边的总成本
        function<int(int)> find = [&](int x) -> int {  // 递归版的并查集查找，返回 x 所在连通块的根
            if (p[x] != x) {  // 父节点不是自己，说明还没走到根
                p[x] = find(p[x]);  // 路径压缩：递归找到根后把 x 直接挂到根上，后续查询几乎 O(1)
            }  // 分支结束，此时 p[x] 已经是根
            return p[x];  // 返回根节点（根同时代表整个连通块）
        };  // 查找函数定义结束
        for (auto& e : connections) {  // 按成本递增的顺序逐条考察边
            int x = e[0] - 1, y = e[1] - 1, cost = e[2];  // 把题目的 1..n 编号转成 0..n-1，才能直接做数组下标
            if (find(x) == find(y)) {  // 两端点已在同一连通块，加这条边会形成环，最小生成树里必须排除
                continue;  // 跳过这条边，继续看下一条
            }  // 分支结束
            p[find(x)] = find(y);  // 合并两个连通块：把一个根挂到另一个根下面
            ans += cost;  // 这条边入选生成树，累加它的成本
            if (--n == 1) {  // 每成功合并一次连通块数量就减 1，只剩 1 块即生成树已完成（这里复用参数 n 计数）
                return ans;  // 提前返回，此时累加值就是最小总成本
            }  // 判断结束
        }  // 所有边都考察完毕
        return -1;  // 边用完了仍有多个连通块，说明图不连通，按题意返回 -1
    }  // 方法结束
};  // 类定义结束