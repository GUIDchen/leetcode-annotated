// 题目：3893. 最大重叠区间团队规模（Maximum Team Size with Overlapping Intervals）
// 思路：枚举每个区间作为“与所有人互动的那个人”，能与它重叠的区间数 = 起点 ≤ r 的个数 − 终点 < l 的个数，用排序后的两个数组二分得到。
// 时间复杂度：O(n log n)，主要是两次排序与 n 次二分；空间复杂度：O(n)，存放区间对。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumTeamSize(vector<int>& startTime, vector<int>& endTime) {  // startTime / endTime：每个员工的开始与结束时间
        int n = startTime.size();  // 员工数量
        vector<pair<int, int>> intervals(n);  // 把每个员工的时间区间存成 (开始, 结束) 对
        for (int i = 0; i < n; i++) {  // 遍历每个员工
            intervals[i] = {startTime[i], endTime[i]};  // 组装该员工的区间
        }  // 结束组装

        sort(startTime.begin(), startTime.end());  // 对开始时间排序，便于统计“起点 ≤ x”的个数
        sort(endTime.begin(), endTime.end());  // 对结束时间排序，便于统计“终点 ≤ x”的个数

        int ans = 0;  // 答案：团队最大规模
        for (const auto& [l, r] : intervals) {  // 枚举作为“中心”的那个区间
            int i = upper_bound(endTime.begin(), endTime.end(), l - 1) - endTime.begin();  // 终点 ≤ l-1 说明它整体在当前区间左侧，不重叠，i 即为这类区间的个数
            int j = upper_bound(startTime.begin(), startTime.end(), r) - startTime.begin();  // 起点 ≤ r 的区间个数 j
            ans = max(ans, j - i);  // j - i 就是与当前区间重叠的区间数（含自身）
        }  // 结束枚举

        return ans;  // 返回最大团队规模
    }  // 结束方法
};  // 结束类
