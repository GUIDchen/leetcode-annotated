// 题目：57. 插入区间（Insert Interval）
// 思路：把新区间追加进数组，再复用「合并区间」的做法：先按左端点排序，然后线性扫描合并相邻重叠区间。
// 时间复杂度：O(n log n)，主要由排序决定；空间复杂度：O(log n) 的排序栈（不计返回结果）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {  // intervals 为已按左端点升序排列的不重叠区间，newInterval 待插入；返回插入并合并后的区间
        intervals.emplace_back(newInterval);  // 把新区间追加到数组末尾（此时顺序可能被破坏）
        return merge(intervals);  // 交给 merge 统一排序并合并，避免两套逻辑
    }  // insert 结束

    vector<vector<int>> merge(vector<vector<int>>& intervals) {  // 合并区间：把相互重叠的区间合并成互不重叠的结果
        sort(intervals.begin(), intervals.end());  // 按左端点升序排序，保证可能重叠的区间相邻
        vector<vector<int>> ans;  // 存放合并后的结果
        ans.emplace_back(intervals[0]);  // 第一个区间先作为结果中的首个区间
        for (int i = 1; i < intervals.size(); ++i) {  // 从第二个区间开始逐个比较
            if (ans.back()[1] < intervals[i][0]) {  // 结果末尾区间的右端点小于当前左端点，说明两者不相交
                ans.emplace_back(intervals[i]);  // 不相交：当前区间另起一段放进结果
            } else {  // 否则两者相交（或相接）
                ans.back()[1] = max(ans.back()[1], intervals[i][1]);  // 相交：把末尾区间的右端点延长到两者中较大的那个
            }  // if/else 结束
        }  // for 结束
        return ans;  // 返回合并后的区间列表
    }  // merge 结束
};  // 类定义结束