// 题目：3092. 最高频率的 ID（Most Frequent IDs）
// 思路：cnt 记录每个 ID 的当前频次，大根堆保存出现过的所有频次；用 lazy 做延迟删除：更新前把旧频次登记为「待删」，堆顶是已失效的旧频次时就弹出。
// 时间复杂度：O(n log n)，每次压入/弹出都是堆操作；空间复杂度：O(n)，cnt、lazy 与堆最多各存 O(n) 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {  // nums 是 ID 序列，freq 是对应的频次增量
        unordered_map<int, long long> cnt;  // ID -> 当前频次（频次会累加得很大，所以用 long long）
        unordered_map<long long, int> lazy;  // 频次值 -> 该值在堆里已失效的次数（延迟删除计数）
        int n = nums.size();  // 操作次数
        vector<long long> ans(n);  // 每次操作后的最大频次
        priority_queue<long long> pq;  // 大根堆，堆顶是候选的最大频次

        for (int i = 0; i < n; ++i) {  // 依次处理每一次操作
            int x = nums[i], f = freq[i];  // 本次操作的 ID 与频次增量
            lazy[cnt[x]]++;  // 旧频次即将失效，先登记一次「待删除」
            cnt[x] += f;  // 更新该 ID 的真实频次
            pq.push(cnt[x]);  // 新频次入堆，成为新的候选
            while (!pq.empty() && lazy[pq.top()] > 0) {  // 堆顶若是已失效的旧频次就弹掉
                lazy[pq.top()]--;  // 消耗一次待删除标记
                pq.pop();  // 弹出失效的堆顶
            }
            ans[i] = pq.empty() ? 0 : pq.top();  // 堆顶即当前最大频次；堆空说明所有 ID 频次都是 0
        }

        return ans;  // 返回每次操作后的最大频次数组
    }
};