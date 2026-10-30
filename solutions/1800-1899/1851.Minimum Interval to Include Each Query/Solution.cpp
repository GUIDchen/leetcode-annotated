// 题目：1851. 包含每个查询的最小区间（Minimum Interval to Include Each Query）
// 思路：区间按左端点排序、查询按值排序后离线扫描；把左端点不超过当前查询的区间按长度入最小堆，弹出右端点过期的，堆顶即答案。
// 时间复杂度：O((n+m)log n)，排序加上每个区间至多进出堆一次；空间复杂度：O(n+m)，堆与排序数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {  // intervals：闭区间数组；queries：待查询的点
        int n = intervals.size(), m = queries.size();  // n 是区间个数，m 是查询个数
        sort(intervals.begin(), intervals.end());  // 区间按左端点升序，方便按查询值从小到大依次加入
        using pii = pair<int, int>;  // 简写“值对”类型，后面记录长度和右端点、以及查询值和原下标
        vector<pii> qs;  // 把查询和它的原始下标打包，避免排序后丢失输出位置
        for (int i = 0; i < m; ++i) {  // 逐个打包查询
            qs.emplace_back(queries[i], i);  // 记录查询值与它在原数组中的下标
        }  // 结束 for
        sort(qs.begin(), qs.end());  // 查询按值升序，这样已入堆的区间不会因为查询变大而失效
        vector<int> ans(m, -1);  // 答案数组，找不到覆盖该点的区间时保持 -1
        priority_queue<pii, vector<pii>, greater<pii>> pq;  // 小顶堆：按区间长度排序，堆顶就是当前最小区间
        int i = 0;  // 区间数组的游标，只会单调前进
        for (auto& [x, j] : qs) {  // 按查询值从小到大处理每个查询（x 是查询值，j 是原下标）
            while (i < n && intervals[i][0] <= x) {  // 把所有左端点不超过 x 的区间纳入候选
                int a = intervals[i][0], b = intervals[i][1];  // 取出当前区间的左端点和右端点
                pq.emplace(b - a + 1, b);  // 入堆键是长度，附带右端点用于判断过期
                ++i;  // 游标后移，已入堆的区间不再重复处理
            }  // 结束 while
            while (!pq.empty() && pq.top().second < x) {  // 右端点小于 x 的区间已经覆盖不到当前查询，弹掉
                pq.pop();  // 弹出堆顶的过期区间
            }  // 结束 while
            if (!pq.empty()) {  // 堆非空说明还有区间覆盖 x
                ans[j] = pq.top().first;  // 堆顶长度就是覆盖 x 的最小区间长度
            }  // 结束 if
        }  // 结束 for
        return ans;  // 按原查询顺序返回答案
    }  // 结束 minInterval
};  // 结束 Solution 类