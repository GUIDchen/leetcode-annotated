// 题目：1654. 到家的最少跳跃次数（Minimum Jumps to Reach Home）
// 思路：BFS 按跳跃次数分层搜索，状态为 (位置, 状态位)，状态位区分上一步是前进还是后退；位置限制在 [0, 6000) 内避免无限搜索。
// 时间复杂度：O(n)，n 为位置上界 6000，每个状态最多入队一次；空间复杂度：O(n)，visited 数组与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {  // forbidden 是禁区，a 前进距离，b 后退距离，x 是目标位置
        unordered_set<int> s(forbidden.begin(), forbidden.end());  // 把禁区放进哈希集合，便于 O(1) 判禁
        queue<pair<int, int>> q;  // BFS 队列，元素是 (位置, 状态位)
        q.emplace(0, 1);  // 起点：位置 0，状态位 1 表示下一步允许后退
        const int n = 6000;  // 位置上界：超过它的状态不会更优，用它限制搜索范围
        bool vis[n][2];  // vis[i][k]：位置 i 在状态 k 下是否访问过
        memset(vis, false, sizeof(vis));  // 初始化为未访问
        vis[0][1] = true;  // 起点标记为已访问
        for (int ans = 0; q.size(); ++ans) {  // 按层 BFS，ans 正是当前层的跳跃次数
            for (int t = q.size(); t; --t) {  // 当前层还剩 t 个状态待处理
                auto [i, k] = q.front();  // 取出队头状态，结构化绑定解包
                q.pop();  // 弹出队头
                if (i == x) {  // 到达目标位置
                    return ans;  // 当前层数就是最少跳跃次数
                }  // 判断结束
                vector<pair<int, int>> nxts = {{i + a, 1}};  // 候选下一步：总能前进到 i+a，状态位重置为 1（前进后允许后退）
                if (k & 1) {  // 状态位为奇数说明上一步是前进，这一步才允许后退
                    nxts.emplace_back(i - b, 0);  // 追加后退到 i-b，状态位 0 表示下一步不能再后退
                }  // 判断结束
                for (auto [j, l] : nxts) {  // 枚举所有候选位置
                    if (j >= 0 && j < n && !s.count(j) && !vis[j][l]) {  // 位置合法：非负、未越上界、不是禁区、该状态没访问过
                        vis[j][l] = true;  // 标记该状态已访问，防止重复入队
                        q.emplace(j, l);  // 入队，等下一层处理
                    }  // 判断结束
                }  // 候选遍历结束
            }  // 本层遍历结束
        }  // 按层循环结束，ans 由 for 头部的 ++ans 递增
        return -1;  // 队列空了仍未到家，说明不可达
    }  // 方法结束
};  // Solution 类定义结束