// 题目：4085. 找到颜色树的根（Find Root of a Colored Tree）
// 核心思路：先把颜色映射成 0/1/2 并用边建出无向邻接表，再逐个节点检验能否作为根：度数不能超过 3；某节点的邻居中不能出现与自己同色的点，也不能有两个「另一种」颜色的邻居；真正满足「度数小于 3 且缺少那种颜色的邻居」的点就是合法根。
// 复杂度：时间 O(n)，建图与逐点检验各一遍；空间 O(n)，邻接表与常数级计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 公开接口
    int findColoredRoot(vector<vector<int>>& edges, string colors) {  // edges：树的边；colors：每个节点的颜色字符；返回合法根的编号，不存在则返回 -1
        int d[128]{};  // d 把颜色字符映射成 0/1/2 的下标，用 128 覆盖所有 ASCII 码
        d['W'] = 0;  // 白色记作 0
        d['R'] = 1;  // 红色记作 1
        d['B'] = 2;  // 蓝色记作 2
        int n = colors.size();  // n 为节点个数，节点编号 0 ~ n-1
        vector<vector<int>> g(n);  // g 为无向邻接表
        for (auto& e : edges) {  // 逐条边建图
            int u = e[0], v = e[1];  // 取出这条边的两个端点
            g[u].push_back(v);  // 把 v 加入 u 的邻居列表
            g[v].push_back(u);  // 把 u 加入 v 的邻居列表（无向图两个方向都要加）
        }  // 建图结束
        int ans = -1;  // ans 记录找到的根，初始为「不存在」
        for (int u = 0; u < n; ++u) {  // 枚举每个节点作为候选根
            auto& vs = g[u];  // vs 引用 u 的邻居列表，避免反复拷贝
            if (vs.size() > 3) {  // 度数超过 3 的节点不可能是合法根
                return -1;  // 直接判定整体无解
            }  // 度数判断结束
            int cnt[3]{};  // cnt 统计邻居中三种颜色各出现了多少次
            for (int v : vs) {  // 遍历 u 的全部邻居
                ++cnt[d[colors[v]]];  // 对应颜色的计数加一
            }  // 邻居颜色统计结束
            int c = d[colors[u]];  // c 为 u 自己的颜色编号
            if (cnt[c] > 0 || cnt[(c + 2) % 3] > 1) {  // 存在同色邻居，或者「另一种」颜色邻居多于一个，都不合法
                return -1;  // 判定整体无解
            }  // 合法性检查结束
            if (vs.size() < 3 && cnt[(c + 2) % 3] == 0) {  // 度数小于 3 且没有那种被禁止的邻居颜色，u 可以作根
                ans = u;  // 更新答案为该节点
            }  // 根判定结束
        }  // 候选根枚举结束
        return ans;  // 返回找到的根，找不到则为 -1
    }  // findColoredRoot 结束
};  // Solution 类结束
