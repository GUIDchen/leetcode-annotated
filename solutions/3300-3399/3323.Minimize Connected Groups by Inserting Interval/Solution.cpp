// 题目：3323. 通过插入区间最小化连通组（Minimize Connected Groups by Inserting Interval）
// 思路：先按左端点排序并合并所有重叠区间；再枚举每个合并组 i，用 lower_bound 找到插入长度 k 的区间后仍够不到的第一个组 j，
// 用 总组数 - 被吞并的中间组数 更新答案。时间复杂度：O(n log n)；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minConnectedGroups(vector<vector<int>>& intervals, int k) {  // intervals：原始区间集合；k：可以额外插入的区间长度
        sort(intervals.begin(), intervals.end());  // 按左端点升序排序（左端点相同则比较右端点），保证后面能顺序合并
        vector<vector<int>> merged;  // 存放合并之后互不相交的连通组
        for (const auto& interval : intervals) {  // 按左端点顺序扫描每个区间
            int s = interval[0], e = interval[1];  // 取出当前区间的左右端点
            if (merged.empty() || merged.back()[1] < s) {  // 还没有组，或当前区间与上一个组的右端点不相交
                merged.emplace_back(interval);  // 开启一个新的连通组
            } else {  // 有重叠，延长上一个组的右端点
                merged.back()[1] = max(merged.back()[1], e);  // 有重叠（或相邻），把上一个组的右端点延长到两者较大值
            }
        }
        int ans = merged.size();  // 不插入任何区间时的组数，作为答案初值
        for (int i = 0; i < merged.size(); ++i) {  // 枚举新插入区间落在的那个组
            auto& interval = merged[i];  // 当前组的左右端点
            int j = lower_bound(merged.begin(), merged.end(), vector<int>{interval[1] + k + 1, 0}) - merged.begin();  // 二分找到第一个左端点 >= 当前右端点 + k + 1 的组，即插入后仍然够不到的分界
            ans = min(ans, (int) merged.size() - (j - i - 1));  // 插入一段长度 k 的区间后，共吞并 j-i-1 个中间组，组数变成 总数 - 吞并数
        }
        return ans;  // 返回最小的连通组数
    }
};
