// 题目：2867. 统计树中的合法路径数目（Count Valid Paths in a Tree）
// 思路：先埃氏筛出素数表；把所有「两端都非素数」的边用并查集合并成块。再枚举每个素数节点作为路径上唯一的素数，把它的各个非素数邻居块的大小两两配对累加。
// 时间复杂度：O(n α(n) + mx log log mx)，并查集近线性加筛法；空间复杂度：O(n + mx)，邻接表、并查集与素数表。
const int mx = 1e5 + 10;  // 节点数上限为 1e5，这里多留 10 个余量
bool prime[mx + 1];  // 素数标记：prime[i] 为 true 表示 i 是素数
int init = []() {  // 全局对象在程序启动时初始化，用它跑一次筛法把素数表准备好
    for (int i = 2; i <= mx; ++i) prime[i] = true;  // 先把 2..mx 全部当作素数
    for (int i = 2; i <= mx; ++i) {  // 从小到大枚举用来筛的素因子
        if (prime[i]) {  // 只有素数才需要去筛掉它的倍数
            for (int j = i + i; j <= mx; j += i) {  // 从 2*i 开始，把 i 的所有倍数标记为合数
                prime[j] = false;  // j 能被 i 整除，因此不是素数
            }
        }
    }
    return 0;  // lambda 必须返回 int 才能用来初始化 init
}();

class UnionFind {  // 并查集：维护所有非素数节点之间的连通块
public:
    UnionFind(int n) {  // n 是节点总数，内部使用 0..n-1，编号 0 的槽位实际空着
        p = vector<int>(n);  // 父节点数组，长度为 n
        size = vector<int>(n, 1);  // 每个连通块的节点数，初始各自为 1
        iota(p.begin(), p.end(), 0);  // 让每个节点的父节点先指向自己
    }

    bool unite(int a, int b) {  // 合并 a、b 所在集合，返回是否真的发生了合并
        int pa = find(a), pb = find(b);  // 分别找出两个节点所在集合的根
        if (pa == pb) {  // 本来就在同一集合里
            return false;  // 无需合并，告诉调用方没有变化
        }
        if (size[pa] > size[pb]) {  // 按大小合并：把小集合挂到大集合下面
            p[pb] = pa;  // b 的根改为指向 a 的根
            size[pa] += size[pb];  // 合并后集合大小累加
        } else {  // 否则把 a 挂到 b 下面
            p[pa] = pb;  // a 的根改为指向 b 的根
            size[pb] += size[pa];  // 合并后集合大小累加
        }
        return true;  // 合并成功
    }

    int find(int x) {  // 查 x 所在集合的根，同时做路径压缩
        if (p[x] != x) {  // 当前节点还不是根
            p[x] = find(p[x]);  // 递归找根，并把沿途节点直接挂到根上
        }
        return p[x];  // 返回根节点
    }

    int getSize(int x) {  // 取 x 所在连通块的节点个数
        return size[find(x)];  // 先找到根，再读根上记录的大小
    }

private:
    vector<int> p, size;  // p：父节点数组；size：以根为代表记录的连通块大小
};

class Solution {  // LeetCode 约定的题解类
public:
    long long countPaths(int n, vector<vector<int>>& edges) {  // n 个节点，edges 是 n-1 条无向边
        vector<int> g[n + 1];  // 邻接表，节点编号是 1..n，所以开 n+1 个位置
        UnionFind uf(n + 1);  // 并查集同样按 1..n 编号，0 号位闲置
        for (auto& e : edges) {  // 逐条处理树上的边
            int u = e[0], v = e[1];  // 取出边的两个端点
            g[u].push_back(v);  // 在 u 的邻接表里记录 v
            g[v].push_back(u);  // 无向图，反方向也要记录
            if (!prime[u] && !prime[v]) {  // 两端都不是素数，这条边属于同一个非素数块
                uf.unite(u, v);  // 把两个端点合并进同一个集合
            }
        }
        long long ans = 0;  // 累加合法路径数，答案可能超过 int
        for (int i = 1; i <= n; ++i) {  // 枚举路径上唯一的那个素数节点
            if (prime[i]) {  // 只把素数节点当作路径的枢纽
                long long t = 0;  // 已经统计过的其它非素数块的节点数之和
                for (int j : g[i]) {  // 遍历素数节点 i 的所有邻居
                    if (!prime[j]) {  // 素数—素数边会带来两个素数，不合法，跳过
                        long long cnt = uf.getSize(j);  // j 所在非素数连通块的节点数
                        ans += cnt;  // 以 i 为一端、块内任一节点为另一端的路径
                        ans += cnt * t;  // 这块与之前统计过的块配对，路径穿过 i
                        t += cnt;  // 把这块的节点数并入累计，供后面的块配对
                    }
                }
            }
        }
        return ans;  // 返回合法路径总数
    }
};