// 题目：759. 员工空闲时间（Employee Free Time）——困难（付费题）
// 思路：把所有员工的工作区间摊平、按起点排序，先合并重叠区间，再取相邻合并段之间的空隙 (前一段 end, 后一段 start) 作为公共空闲时间。
// 时间复杂度：O(N log N)，N 为区间总数，主要开销是排序；空间复杂度：O(N)，摊平数组与合并结果各占 O(N)。
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {  // schedule 是每位员工各自的、已按起点排好序的工作区间
        vector<Interval> intervals;  // 用来把所有员工的工作区间摊平到同一个数组里
        for (auto& e : schedule) {  // 遍历每位员工
            intervals.insert(intervals.end(), e.begin(), e.end());  // 把该员工的区间整段追加到末尾
        }

        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {  // 按起点升序排序
            if (a.start == b.start) return a.end < b.end;  // 起点相同则按终点升序，保证短区间在前
            return a.start < b.start;  // 一般情况按起点升序
        });

        vector<Interval> merged;  // 存放合并后的互不重叠区间
        merged.push_back(intervals[0]);  // 用第一个区间初始化合并结果
        for (int i = 1; i < intervals.size(); ++i) {  // 顺序扫描其余区间
            auto& last = merged.back();  // 当前合并段的最后一个区间
            auto& cur = intervals[i];  // 待处理的区间
            if (last.end < cur.start) {  // 与上一段完全不相交
                merged.push_back(cur);  // 另起一段
            } else {  // 有重叠，需要合并
                last.end = max(last.end, cur.end);  // 把右端点扩展到更远的一侧
            }
        }

        vector<Interval> ans;  // 收集公共空闲区间
        for (int i = 1; i < merged.size(); ++i) {  // 相邻两个合并段之间就是所有人的公共空闲
            auto& a = merged[i - 1];  // 前一段
            auto& b = merged[i];  // 后一段
            ans.emplace_back(a.end, b.start);  // 空隙就是 (前一段终点, 后一段起点)
        }

        return ans;  // 返回按时间升序排列的空闲区间
    }
};
