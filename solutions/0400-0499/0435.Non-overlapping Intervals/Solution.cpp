// 题目：435. 无重叠区间（Non-overlapping Intervals）
// 思路：贪心——按右端点升序排序，尽量保留右端点小的区间：能与上一个保留区间接上就保留，接不上就必须移除它，这样移除数最少、保留数最多。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(log n)，std::sort 的递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {  // 返回最少需要移除的区间数，使剩下的区间两两互不重叠
        ranges::sort(intervals, [](const vector<int>& a, const vector<int>& b) {  // C++20 ranges::sort：按右端点升序排序，为贪心做准备
            return a[1] < b[1];  // 比较器：右端点小的排在前面
        });
        int ans = intervals.size();  // 先假设所有区间都要移除，之后每保留一个就减 1
        int pre = INT_MIN;  // 上一个被保留区间的右端点，初始为负无穷以保证第一个区间一定能接上
        for (const auto& e : intervals) {  // 按右端点从小到大依次做贪心判断
            int l = e[0], r = e[1];  // 取出当前区间的左、右端点
            if (pre <= l) {  // 与上一个保留区间不重叠（端点刚好相接也算不重叠）
                --ans;  // 该区间可以保留，需要移除的数量减 1
                pre = r;  // 更新已保留区间的右端点为当前区间的右端点
            }
        }
        return ans;  // 剩余的 ans 就是必须移除的最少区间数
    }
};
