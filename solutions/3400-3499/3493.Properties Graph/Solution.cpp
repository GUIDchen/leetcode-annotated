// 3493. Properties Graph / 3493. 属性图
// 核心思路：把每个数组去重成集合，两两求交集，交集大小至少为 k 的两点连边，最后用 DFS 统计连通分量个数。
// 复杂度：时间 O(n^2 * m)，其中 m 为单个属性数组长度上界；空间 O(n^2)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    int numberOfComponents(vector<vector<int>>& properties, int k) {  // properties 为各点的属性数组，k 为连边所需的公共属性数
        int n = properties.size();  // 点的个数
        unordered_set<int> ss[n];  // ss[i] 保存第 i 个点去重后的属性集合
        vector<int> g[n];  // 邻接表，g[i] 存放与 i 公共属性数达到 k 的点
        for (int i = 0; i < n; ++i) {  // 逐点构造属性集合
            for (int x : properties[i]) {  // 遍历该点的每个属性
                ss[i].insert(x);  // 插入集合，自动去重
            }
        }
        for (int i = 0; i < n; ++i) {  // 枚举点对中较大的下标 i
            auto& s1 = ss[i];  // 取 i 的属性集合引用，避免拷贝
            for (int j = 0; j < i; ++j) {  // 只枚举 j < i，保证每对点只处理一次
                auto& s2 = ss[j];  // 取 j 的属性集合引用
                int cnt = 0;  // 记录两个集合的公共属性个数
                for (int x : s1) {  // 遍历 s1 中的每个属性
                    if (s2.contains(x)) {  // 该属性同时出现于 s2 中
                        ++cnt;  // 公共属性计数加一
                    }
                }
                if (cnt >= k) {  // 公共属性数达到 k，两点之间建双向边
                    g[i].push_back(j);  // 从 i 连向 j
                    g[j].push_back(i);  // 从 j 连向 i
                }
            }
        }
        int ans = 0;  // 连通分量计数
        vector<bool> vis(n);  // vis[i] 标记点 i 是否已被访问
        auto dfs = [&](this auto&& dfs, int i) -> void {  // 递归 DFS，遍历并标记 i 所在的整个连通分量
            vis[i] = true;  // 标记当前点已访问
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (!vis[j]) {  // 邻居未被访问才继续递归
                    dfs(j);  // 深入该邻居
                }
            }
        };
        for (int i = 0; i < n; ++i) {  // 枚举每个点作为连通分量的起点
            if (!vis[i]) {  // 发现未访问的点，说明是一个新分量
                dfs(i);  // 标记整个分量
                ++ans;  // 分量计数加一
            }
        }
        return ans;  // 返回连通分量个数
    }
};
