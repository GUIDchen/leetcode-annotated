// 题目：1311. 获取你好友已观看的视频（Get Watched Videos by Your Friends）
// 核心思路：先做 level 层 BFS，找到距离 id 恰好为 level 的所有人；统计这些人看过的视频出现次数，
//           最后按「出现次数升序、次数相同按字典序」排序输出。
// 时间复杂度：O(n + e + V log V)，BFS 与统计为线性，V 是候选视频数；空间复杂度：O(n + V)，队列、访问数组与计数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {  // watchedVideos 是每人看过的视频，friends 是朋友邻接表
        queue<int> q{{id}};  // BFS 队列，初始放在起点 id
        int n = friends.size();  // 总人数，用于创建访问数组
        vector<bool> vis(n);  // 访问标记，默认全为 false，避免重复入队
        vis[id] = true;  // 起点标记为已访问
        while (level--) {  // 逐层扩展，循环结束后队列里恰好是第 level 层朋友
            for (int k = q.size(); k; --k) {  // 固定当前层的节点数，逐个处理完这一整层
                int i = q.front();  // 取出队首节点
                q.pop();  // 弹出队首
                for (int j : friends[i]) {  // 遍历该节点的所有朋友
                    if (!vis[j]) {  // 对方还没被访问过
                        vis[j] = true;  // 标记为已访问
                        q.push(j);  // 加入队列，成为下一层
                    }
                }
            }
        }
        unordered_map<string, int> cnt;  // 视频名 → 在第 level 层朋友中出现的次数
        while (!q.empty()) {  // 队列里剩下的就是距离恰好为 level 的人
            int i = q.front();  // 取出一个人
            q.pop();  // 弹出
            for (const auto& v : watchedVideos[i]) {  // 遍历他看过的每个视频
                cnt[v]++;  // 出现次数加一
            }
        }
        vector<string> ans;  // 存放待排序的视频名
        for (const auto& [key, _] : cnt) {  // 结构化绑定遍历哈希表
            ans.push_back(key);  // 只取视频名放进答案
        }
        sort(ans.begin(), ans.end(), [&cnt](const string& a, const string& b) {  // 按题目要求排序
            return cnt[a] == cnt[b] ? a < b : cnt[a] < cnt[b];  // 次数相同按字典序，否则次数少的在前
        });
        return ans;  // 返回排好序的视频列表
    }
};
