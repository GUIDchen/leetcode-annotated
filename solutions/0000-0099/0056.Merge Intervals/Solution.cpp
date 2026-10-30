// 题目：56. 合并区间（Merge Intervals）
// 思路：排序 + 贪心。先按左端点排序让重叠区间相邻，再线性扫描，用一个「待合并区间」边扩展边收集。
// 时间复杂度：O(n log n)，主要花在排序上；空间复杂度：O(log n) 的排序栈（不计返回结果）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> merge(vector<vector<int>>& intervals) {  // intervals 为若干闭区间，返回合并所有重叠区间后的结果
        sort(intervals.begin(), intervals.end());  // 按左端点（左端点相同则按右端点）升序排序，保证重叠区间彼此相邻
        int st = intervals[0][0], ed = intervals[0][1];  // st、ed 是当前待合并区间的左右端点，先用第一个区间初始化
        vector<vector<int>> ans;  // 存放合并后的结果
        for (int i = 1; i < intervals.size(); ++i) {  // 从第二个区间开始逐个与待合并区间比较
            if (ed < intervals[i][0]) {  // 待合并区间的右端点小于当前左端点，说明两者不相交
                ans.push_back({st, ed});  // 把已经确定的待合并区间收进答案
                st = intervals[i][0];  // 把当前区间换作新的待合并区间（新的左端点）
                ed = intervals[i][1];  // 同时更新新的右端点
            } else {  // 否则两者相交（或相接）
                ed = max(ed, intervals[i][1]);  // 相交时右端点取较大者，相当于把当前区间并入待合并区间
            }  // if/else 结束
        }  // for 结束
        ans.push_back({st, ed});  // 循环结束后最后一个待合并区间还没有收集，补上
        return ans;  // 返回合并结果
    }  // merge 结束
};  // 类定义结束