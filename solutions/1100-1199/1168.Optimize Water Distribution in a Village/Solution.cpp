// 题目：1168. 水资源分配优化（Optimize Water Distribution in a Village）
// 思路：建一个虚拟源点 0，在房子 i 打井等价于边 (0, i) 且代价为 wells[i]；把所有边排序后跑 Kruskal 最小生成树。
// 时间复杂度：O(E log E)，E = n + len(pipes)；空间复杂度：O(n + E)，并查集与边表都是线性规模。
class Solution {  // 题解类
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {  // 求让每个房子都通水的最小总费用
        for (int i = 0; i < n; ++i) {  // 把「在 i 号房子打井」抽象成虚拟源点 0 到 i+1 的一条边
            pipes.push_back({0, i + 1, wells[i]});  // 追加虚拟边：这条边的代价就是在该房子打井的费用
        }  // for 结束
        sort(pipes.begin(), pipes.end(), [](const vector<int>& a, const vector<int>& b) {  // 按边权升序排序，为 Kruskal 最小生成树做准备
            return a[2] < b[2];  // 比较两条边的代价（每条边是 {a, b, cost}）
        });  // 排序 lambda 结束
        int p[n + 1];  // 并查集数组，0 号是虚拟源点，所以要多开一格
        iota(p, p + n + 1, 0);  // 初始化并查集：每个节点的父亲都是自己
        function<int(int)> find = [&](int x) {  // 递归查找根节点，并沿途做路径压缩
            if (p[x] != x) {  // 父亲不是自己说明它还不是根
                p[x] = find(p[x]);  // 路径压缩：把 x 直接挂到根上，后续查找更快
            }  // if 结束
            return p[x];  // 返回所在连通块的根
        };  // find 定义结束
        int ans = 0;  // 累计最小费用
        for (const auto& x : pipes) {  // 按代价从小到大遍历所有边（Kruskal 选边）
            int pa = find(x[0]), pb = find(x[1]);  // 取这条边两个端点所在连通块的根
            if (pa == pb) {  // 两端已经连通，选它会成环
                continue;  // 跳过这条边
            }  // if 结束
            p[pa] = pb;  // 合并两个连通块
            ans += x[2];  // 采用这条边，把代价累加到答案
            if (--n == 0) {  // 还需要合并的次数减一；减到 0 说明已形成生成树
                break;  // 提前结束循环
            }  // if 结束
        }  // for 结束
        return ans;  // 返回最小总费用
    }  // 方法结束
};  // 类定义结束