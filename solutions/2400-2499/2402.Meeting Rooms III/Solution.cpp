// 题目：2402. 会议室 III（Meeting Rooms III）
// 思路：按开始时间排序后模拟，用两个小顶堆分别维护空闲会议室编号与「结束时间, 会议室编号」，无空闲时延迟到最早散场的会议室。
// 时间复杂度：O(m log m + m log n)，排序 m 个会议并做 m 次堆操作；空间复杂度：O(n + m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int mostBooked(int n, vector<vector<int>>& meetings) {  // n：会议室数量；meetings：每个会议的开始与结束时间
        sort(meetings.begin(), meetings.end());  // 按开始时间升序排序，保证会议按时间先后依次安排
        using pli = pair<long long, int>;  // 别名：结束时间 + 会议室编号
        priority_queue<pli, vector<pli>, greater<pli>> busy;  // 忙碌堆，按结束时间最早优先出堆
        priority_queue<int, vector<int>, greater<int>> idle;  // 空闲堆，按会议室编号最小优先出堆
        for (int i = 0; i < n; ++i) {  // 初始时所有会议室都空闲
            idle.push(i);  // 把编号 i 的会议室放进空闲堆
        }
        vector<int> cnt(n);  // cnt[i] 记录第 i 个会议室被使用的次数
        for (auto& v : meetings) {  // 依次安排每一个会议
            int s = v[0], e = v[1];  // s：会议开始时间；e：会议结束时间
            while (!busy.empty() && busy.top().first <= s) {  // 结束时间不晚于 s 的会议已经散场
                idle.push(busy.top().second);  // 该会议室重新空闲，放回空闲堆
                busy.pop();  // 从忙碌堆中移除
            }
            int i = 0;  // i 记录本次会议分配到的会议室编号
            if (!idle.empty()) {  // 还有空闲会议室，优先使用编号最小的那个
                i = idle.top();  // 取出编号最小的空闲会议室
                idle.pop();  // 从空闲堆中移除
                busy.push({e, i});  // 会议在原定的 e 时刻结束，登记进忙碌堆
            } else {  // 没有空闲会议室，需要等最早散场的会议室空出来再延迟开始
                auto x = busy.top();  // 取出结束时间最早的忙碌会议室
                busy.pop();  // 先弹出，稍后按新的结束时间重新入堆
                i = x.second;  // 沿用这个会议室
                busy.push({x.first + e - s, i});  // 整体延后开始，会议时长仍是 e - s
            }
            ++cnt[i];  // 该会议室的使用次数加一
        }
        int ans = 0;  // ans 记录使用次数最多的会议室编号
        for (int i = 0; i < n; ++i) {  // 遍历所有会议室比使用次数
            if (cnt[ans] < cnt[i]) {  // 严格大于才更新，次数相同时保留编号更小的会议室
                ans = i;  // 更新答案编号
            }
        }
        return ans;  // 返回被使用次数最多的会议室编号
    }
};
