// 题目：2101. 引爆最多的炸弹（Detonate the Maximum Bombs）
// 思路：若 i 的爆炸范围覆盖 j 就从 i 向 j 连一条有向边建图，然后对每个点做一次 BFS，统计能到达的炸弹数并取最大值。
// 时间复杂度：O(n^3)，建图 O(n^2) 加 n 次 BFS；空间复杂度：O(n^2)，邻接表最坏存 n(n-1) 条边。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumDetonation(vector<vector<int>>& bombs) {  // bombs[i] = {x, y, r}，返回一次引爆能波及的最多炸弹数
        int n = bombs.size();  // 炸弹总数
        vector<int> g[n];  // 邻接表：g[i] 保存 i 被引爆后会直接连锁引爆的炸弹编号
        for (int i = 0; i < n - 1; ++i) {  // 枚举每一对炸弹，只取 i < j 避免重复计算距离
            for (int j = i + 1; j < n; ++j) {  // 枚举与 i 配对的另一颗炸弹 j
                auto& p1 = bombs[i];  // 引用取出第 i 颗炸弹的坐标与半径，避免拷贝
                auto& p2 = bombs[j];  // 引用取出第 j 颗炸弹的数据
                auto dist = hypot(p1[0] - p2[0], p1[1] - p2[1]);  // 两炸弹圆心之间的欧氏距离
                if (dist <= p1[2]) {  // 距离不超过 i 的爆炸半径，说明 i 能引爆 j
                    g[i].push_back(j);  // 加一条 i → j 的有向边
                }  // if 分支结束
                if (dist <= p2[2]) {  // 反向判断：j 的爆炸范围是否也覆盖 i
                    g[j].push_back(i);  // 若是则加一条 j → i 的有向边
                }  // if 分支结束
            }
        }
        int ans = 0;  // 记录所有起点中最多能引爆的炸弹数
        bool vis[n];  // BFS 访问标记，每个起点开始前都要重置
        for (int k = 0; k < n; ++k) {  // 依次以每颗炸弹作为最初引爆点
            memset(vis, false, sizeof(vis));  // 清空访问标记，保证本次 BFS 独立
            queue<int> q;  // BFS 队列，存放待扩散的炸弹编号
            q.push(k);  // 起点入队
            vis[k] = true;  // 起点标记为已引爆
            int cnt = 0;  // 本轮能引爆的炸弹计数
            while (!q.empty()) {  // 队列非空就继续向外扩散
                int i = q.front();  // 取出队头炸弹
                q.pop();  // 弹出队头
                ++cnt;  // 这颗炸弹已被引爆，计数加一
                for (int j : g[i]) {  // 遍历它能直接引爆的炸弹
                    if (!vis[j]) {  // 只有还没被引爆过的才处理，避免重复入队
                        vis[j] = true;  // 标记已访问
                        q.push(j);  // 入队，等待继续向外连锁扩散
                    }
                }  // 内层 for 结束
            }
            if (cnt == n) {  // 已经能引爆全部炸弹，不可能有更优答案
                return n;  // 提前返回 n，省掉剩余的计算
            }
            ans = max(ans, cnt);  // 用本轮的引爆数更新最大值
        }
        return ans;  // 返回所有起点中的最大引爆数
    }
};