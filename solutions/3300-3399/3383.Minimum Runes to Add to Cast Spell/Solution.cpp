// 题目：3383. 施法所需最低符文数量（Minimum Runes to Add to Cast Spell）
// 思路：有向边表示符文的流动；先从晶体做多源 BFS 标记免费可达点，再对剩余点 DFS 求逆后序，按「上游优先」的顺序逐个补符文并 BFS 扩散计数。
// 时间复杂度：O(n + m)，每个点最多入队/访问一次；空间复杂度：O(n + m)，存邻接表、访问标记与拓扑序列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> vis;  // 访问状态：0=未点亮，1=已点亮（晶体可达），2=DFS 标记的待补符文点
    vector<vector<int>> g;  // 邻接表：g[a] 保存从 a 能流到的所有符文
    vector<int> seq;  // DFS 的后序序列，反转后即「上游在前」的处理顺序

    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {  // n：符文总数；crystals：初始晶体；flowFrom/flowTo：有向流动边
        g.resize(n);  // 按符文数量开好邻接表
        for (int i = 0; i < flowFrom.size(); ++i) {  // 枚举每一条流动边
            g[flowFrom[i]].push_back(flowTo[i]);  // 建图：flowFrom[i] 可以直接流到 flowTo[i]
        }

        deque<int> q;  // BFS 队列，存放「已经能被点亮」的符文
        vis.resize(n, 0);  // 初始化所有符文都未点亮
        for (int i : crystals) {  // 晶体本身天生可用，作为多源 BFS 的起点
            vis[i] = 1;  // 晶体直接标记为已点亮
            q.push_back(i);  // 入队，稍后从它向外扩散
        }
        bfs(q);  // 第一轮扩散：算出不花任何符文就能点亮的集合

        for (int i = 0; i < n; ++i) {  // 枚举每一个符文
            if (vis[i] == 0) {  // 仍然点不亮的符文构成若干互不相通的块
                dfs(i);  // 对该块做 DFS，把节点按后序压入 seq
            }
        }

        int ans = 0;  // ans：需要新增的最少符文数量
        for (int i = seq.size() - 1; i >= 0; --i) {  // 逆着后序走：反转后每个块的「源头」排在前面
            int a = seq[i];  // 取出当前判断的节点
            if (vis[a] == 2) {  // 只处理 DFS 之后仍是状态 2 的节点
                vis[a] = 1;  // 在这里补一个符文：把它当作新的晶体起点
                q.clear();  // 复用队列，先清掉上一轮的残留
                q.push_back(a);  // 新起点入队
                bfs(q);  // 从新起点再扩散一次，可能点亮同块更多节点
                ++ans;  // 花费加一
            }
        }
        return ans;  // 返回最少需要新增的符文数量
    }

private:  // 以下为内部辅助函数
    void bfs(deque<int>& q) {  // 多源 BFS：把队列中节点能流到且未点亮的点全部标成 1
        while (!q.empty()) {  // 队列非空就继续扩散
            int a = q.front();  // 取队首节点
            q.pop_front();  // 出队
            for (int b : g[a]) {  // 遍历 a 的所有出边邻居
                if (vis[b] == 1) {  // 已经点亮过就不再重复处理
                    continue;  // 跳过，保证每个点最多入队一次
                }
                vis[b] = 1;  // 标记 b 已点亮
                q.push_back(b);  // 入队，继续向后扩散
            }
        }
    }

    void dfs(int a) {  // DFS：给未点亮的点标 2，并按后序把点写进 seq
        vis[a] = 2;  // 状态 2 表示「该点仍需补符文」且已访问过
        for (int b : g[a]) {  // 遍历邻居
            if (vis[b] > 0) {  // 已访问过（1 或 2）就剪枝
                continue;  // 跳过，避免重复访问或走回已点亮区域
            }
            dfs(b);  // 递归深入
        }
        seq.push_back(a);  // 后序写入：下游先入列、上游后入列，所以反转后上游在前
    }
};  // 题解类定义结束
