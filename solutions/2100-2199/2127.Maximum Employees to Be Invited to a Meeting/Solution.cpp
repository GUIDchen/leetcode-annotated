// 题目：2127. 参加会议的最多员工数（Maximum Employees to Be Invited to a Meeting）
// 核心思路：每个点出度为 1，图是基环树森林。答案 = max(长度 ≥ 3 的最大纯环环长, 所有二元互惠环两侧最长链长度之和 的总和)。
// 时间复杂度：O(n)，每个员工只被访问常数次；空间复杂度：O(n)，vis / indeg / dist 与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumInvitations(vector<int>& favorite) {  // favorite[i] 表示员工 i 最想邀请的人；返回最多能邀请的员工数
        return max(maxCycle(favorite), topologicalSort(favorite));  // 两种情况取最大：长度 ≥ 3 的纯环取环长；二元互惠环则把所有「一对 + 两侧最长链」拼起来
    }

    int maxCycle(vector<int>& fa) {  // 求出所有纯环（长度 ≥ 3）中的最大环长
        int n = fa.size();  // n 是员工总数
        vector<bool> vis(n);  // vis[i] 标记员工 i 是否已被扫过，保证每个点只处理一次
        int ans = 0;  // ans 保存当前找到的最大环长
        for (int i = 0; i < n; ++i) {  // 枚举每个可能的起点
            if (vis[i]) continue;  // 已经访问过就跳过，否则会重复处理同一条链/环
            vector<int> cycle;  // cycle 按访问顺序记录本次走过的路径
            int j = i;  // j 表示当前走到的员工，从起点 i 出发
            while (!vis[j]) {  // 顺着 favorite 指针一直走，直到遇到已访问的点（说明绕进了环）
                cycle.push_back(j);  // 把当前员工记入路径
                vis[j] = true;  // 标记为已访问
                j = fa[j];  // 沿「最喜欢的人」再走一步
            }
            for (int k = 0; k < cycle.size(); ++k) {  // 在本次路径中定位环的入口，即终点 j 出现的位置
                if (cycle[k] == j) {  // cycle[k] == j 说明从下标 k 开始进入环，k 就是环入口
                    ans = max(ans, (int) cycle.size() - k);  // 环长为整条路径长度减去入口之前的那段长度
                    break;  // 一个起点最多只形成一个环，找到后即可跳出内层循环
                }
            }
        }
        return ans;  // 返回整个图的最大纯环长度
    }

    int topologicalSort(vector<int>& fa) {  // 统计所有「二元互惠环 + 其两侧最长链」能坐下的人数总和
        int n = fa.size();  // n 是员工总数
        vector<int> indeg(n);  // indeg[i]：有多少人把 i 当作最喜欢的人（入度）
        vector<int> dist(n, 1);  // dist[i]：以 i 为起点的最长链长度，初始只有自己，长度为 1
        for (int v : fa) ++indeg[v];  // 遍历 favorite 数组累计每个点的入度
        queue<int> q;  // 拓扑排序用的队列
        for (int i = 0; i < n; ++i)  // 入度为 0 的点是链的末端（没有人喜欢他），从这里开始向上推进
            if (indeg[i] == 0) q.push(i);  // 把链末端入队，作为拓扑排序的起点
        while (!q.empty()) {  // 不断删边并向「上级」推进，直到所有非环部分都被处理完
            int i = q.front();  // 取出队首员工
            q.pop();  // 队首出队
            dist[fa[i]] = max(dist[fa[i]], dist[i] + 1);  // 用 i 的链长加 1 去更新它的上级 fa[i] 的最长链长
            if (--indeg[fa[i]] == 0) q.push(fa[i]);  // 删掉 i 指向 fa[i] 的一条入边；入度变 0 说明下游都处理完，可以入队
        }
        int ans = 0;  // ans 汇总所有二元互惠环贡献的人数
        for (int i = 0; i < n; ++i)  // 遍历每一个员工
            if (i == fa[fa[i]]) ans += dist[i];  // i 与 fa[i] 互相喜欢（二元环），累加 i 这一侧的最长链长；另一侧会在 fa[i] 身上统计
        return ans;
    }
};