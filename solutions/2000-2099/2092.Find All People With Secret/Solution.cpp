// 题目：2092. 找出知晓秘密的所有专家（Find All People With Secret）
// 思路：按会议时间升序分组，逐个时间片建临时图，从「已知情」的人做 BFS 向同一时间片的人传播秘密。
// 时间复杂度：O(m log m + m)，排序 m 场会议后每场只处理常数次；空间复杂度：O(n + m)，vis 数组与时间片临时图。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {  // n：人数；meetings：{a, b, t} 三元组；firstPerson：第一个得知秘密的人
        vector<bool> vis(n);  // vis[i] 表示编号 i 是否已知晓秘密，默认全为 false
        vis[0] = vis[firstPerson] = true;  // 0 号本人与 firstPerson 一开始就知情
        sort(meetings.begin(), meetings.end(), [&](const auto& x, const auto& y) {  // 按时间字段升序排序，让同一时刻的会议相邻，便于成组处理
            return x[2] < y[2];  // 直接比较第 3 个字段（时间）
        });  // 排序结束
        for (int i = 0, m = meetings.size(); i < m;) {  // 外层循环以「时间相同的一段」为处理单元，i 是该段起点
            int j = i;  // j 用来向右寻找同一时间的段尾
            for (; j + 1 < m && meetings[j + 1][2] == meetings[i][2];) {  // 下一场会议时间仍相同就继续右扩
                ++j;  // 段尾右移，循环结束后 [i, j] 内会议时间全相等
            }
            unordered_map<int, vector<int>> g;  // 本时间片的临时邻接表：只装这一时间段内的边
            unordered_set<int> s;  // 本时间片出现过的人员集合，用来挑 BFS 的种子
            for (int k = i; k <= j; ++k) {  // 遍历本时间片的每一场会议
                int x = meetings[k][0], y = meetings[k][1];  // 取出参会两人的编号
                g[x].push_back(y);  // 建 x -> y 的无向边
                g[y].push_back(x);  // 建 y -> x 的无向边
                s.insert(x);  // 记录 x 属于本时间片
                s.insert(y);  // 记录 y 属于本时间片
            }
            queue<int> q;  // BFS 队列：只从本时间片内已知情的人开始扩散
            for (int u : s) {  // 枚举本时间片涉及的所有人员
                if (vis[u]) {  // 此前已知情的人才能作为种子
                    q.push(u);  // 入队作为 BFS 起点
                }
            }
            while (!q.empty()) {  // 在本时间片的图里做一次 BFS
                int u = q.front();  // 取队首人员
                q.pop();  // 出队
                for (int v : g[u]) {  // 枚举与 u 在同一时间片开过会的人
                    if (!vis[v]) {  // 只有还没被告知的人才需要更新
                        vis[v] = true;  // 标记为已知情
                        q.push(v);  // 继续向外扩散
                    }
                }
            }
            i = j + 1;  // 跳过本时间片，处理下一个时间段
        }  // 所有时间段处理完毕
        vector<int> ans;  // 收集答案
        for (int i = 0; i < n; ++i) {  // 按编号从小到大枚举所有人
            if (vis[i]) {  // 已知情则计入答案
                ans.push_back(i);  // 追加编号，答案天然有序
            }
        }
        return ans;  // 返回所有最终知晓秘密的人的编号
    }
};
