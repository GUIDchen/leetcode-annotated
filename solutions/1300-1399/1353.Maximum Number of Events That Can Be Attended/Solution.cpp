// 题目：1353. 最多可以参加的会议数目（Maximum Number of Events That Can Be Attended）
// 思路：把会议按开始日装进哈希桶，从最早开始日逐天向后推进；用最小堆维护「当前可参加会议」的结束日，每天贪心地参加结束最早的一场，过期会议直接丢弃。
// 时间复杂度：O(n log n + D log n)，D 为日期跨度、n 为会议数；空间复杂度：O(n)，用来分桶与存堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxEvents(vector<vector<int>>& events) {  // events[i] = [开始日, 结束日]，每天最多只能参加一场会议
        unordered_map<int, vector<int>> g;  // 哈希桶：键是开始日，值是该天开始的所有会议的结束日
        int l = INT_MAX, r = 0;  // l 记录最早开始日、r 记录最晚结束日，用来确定需要扫描的日期区间
        for (auto& event : events) {  // 第一遍遍历：完成分桶，同时求出扫描区间端点
            int s = event[0], e = event[1];  // s 是开始日，e 是结束日
            g[s].push_back(e);  // 把这场会议挂到它的开始日上
            l = min(l, s);  // 维护最早开始日
            r = max(r, e);  // 维护最晚结束日
        }  // 分桶与区间统计完成
        priority_queue<int, vector<int>, greater<int>> pq;  // 小根堆：存放「已经可以参加」的会议的结束日，结束越早越靠前
        int ans = 0;  // 已参加的会议数量
        for (int s = l; s <= r; ++s) {  // 从最早开始日逐天推进到最晚结束日
            while (!pq.empty() && pq.top() < s) {  // 堆顶会议的结束日早于今天，说明它已经彻底过期
                pq.pop();  // 丢掉这场不可能再参加的会议
            }  // 所有过期会议清理完毕
            for (int e : g[s]) {  // 把今天新开始的会议放进候选池
                pq.push(e);  // 结束日入堆，由堆自动按结束日排序
            }  // 今天开始的会议全部入池
            if (!pq.empty()) {  // 候选池非空，说明今天一定有会可参加
                pq.pop();  // 贪心策略：今天参加结束最早的那一场，给后面留出更多余地
                ++ans;  // 参加数加一
            }  // 今天的决策完成
        }  // 逐天扫描结束
        return ans;  // 返回最多能参加的会议数目
    }  // maxEvents 结束
};  // 类定义结束
