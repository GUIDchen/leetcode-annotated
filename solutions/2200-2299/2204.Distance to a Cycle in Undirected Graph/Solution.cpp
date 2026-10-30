// 题目：2204. 无向图中到环的距离（Distance to a Cycle in Undirected Graph）
// 核心思路：拓扑剥离所有度数为 1 的叶子结点，剩下的点恰好构成唯一的环；剥离时记下每个点的父结点，最后按剥离顺序逆序沿父指针递推距离。
// 时间复杂度：O(n + m)，n 个点、m 条边各被处理常数次；空间复杂度：O(n + m)，邻接表、队列与若干 O(n) 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {  // n 是结点数，edges 是无向边列表
        unordered_set<int> g[n];  // 邻接表：g[v] 存与 v 相邻的结点集合，便于 O(1) 删除一条边
        for (auto& e : edges) {  // 逐条无向边建图
            int a = e[0], b = e[1];  // 取出边的两个端点
            g[a].insert(b);  // 记录 a 的邻居 b
            g[b].insert(a);  // 无向图要双向登记
        }
        queue<int> q;  // BFS 队列：存放当前度数为 1 的叶子结点
        for (int i = 0; i < n; ++i) {  // 扫描所有结点
            if (g[i].size() == 1) {  // 度数为 1 说明是叶子，不可能落在环上
                q.push(i);  // 叶子入队，准备被剥离
            }
        }
        int f[n];  // f[v] 记录 v 被剥离时唯一的邻居，也就是它在树上的父结点
        int seq[n];  // seq 按剥离顺序保存所有非环节点
        int k = 0;  // k 表示 seq 中已经保存的元素个数
        while (!q.empty()) {  // 不断剥离叶子，直到队列为空、只剩下环
            int i = q.front();  // 取出队首叶子
            q.pop();  // 出队
            seq[k++] = i;  // 记录剥离顺序，最后要按逆序递推距离
            for (int j : g[i]) {  // 遍历叶子 i 当前仅存的邻居（正常只有一个）
                g[j].erase(i);  // 把 i 从 j 的邻接表中删掉，模拟剥离这条边
                f[i] = j;  // i 的父结点是 j，i 的距离将由 j 推出
                if (g[j].size() == 1) {  // j 删边后度数变成 1，成为新的叶子
                    q.push(j);  // 新叶子入队，等下一轮剥离
                }
            }
            g[i].clear();  // 清空 i 的邻接表，标记它已经不在图中
        }
        vector<int> ans(n);  // ans[v] 是 v 到环的距离；环上结点保持默认值 0
        for (; k; --k) {  // 逆序（从环向外）递推，循环本身也在消耗 k
            int i = seq[k - 1];  // 取出最近一次被剥离的结点 i
            ans[i] = ans[f[i]] + 1;  // i 比父结点 f[i] 多走一条边，所以距离加 1
        }
        return ans;  // 返回每个结点到环的距离
    }
};