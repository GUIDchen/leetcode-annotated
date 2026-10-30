// 题目：436. 寻找右区间（Find Right Interval）
// 思路：把（左端点, 原下标）排序后，对每个区间的右端点做 lower_bound，找到第一个左端点 ≥ 该右端点的区间，其原下标就是答案。
// 时间复杂度：O(n log n)，一次排序加 n 次二分；空间复杂度：O(n)，辅助数组 arr 与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    vector<int> findRightInterval(vector<vector<int>>& intervals) {  // 为每个区间找出右区间的下标；不存在右区间时该位置填 -1
        int n = intervals.size();  // 区间总数
        vector<pair<int, int>> arr;  // 辅助数组，存 (左端点, 原始下标)，用于排序后二分
        for (int i = 0; i < n; ++i) {  // 遍历所有区间，建立左端点到下标的映射
            arr.emplace_back(intervals[i][0], i);  // 原地构造 pair，记录左端点与该区间的原始下标
        }
        sort(arr.begin(), arr.end());  // 按左端点升序排序；pair 默认先比 first，再比 second
        vector<int> ans;  // 答案数组，按原区间顺序依次填入结果
        for (auto& e : intervals) {  // 按原始顺序逐个区间求右区间
            int j = lower_bound(arr.begin(), arr.end(), make_pair(e[1], -1)) - arr.begin();  // 二分找第一个左端点 ≥ e[1] 的位置；second 取 -1 保证同左端点时命中最靠前的那个
            ans.push_back(j == n ? -1 : arr[j].second);  // 越界说明没有左端点 ≥ 右端点的区间，否则取回该区间的原始下标
        }
        return ans;  // 返回与输入一一对应的答案数组
    }
};