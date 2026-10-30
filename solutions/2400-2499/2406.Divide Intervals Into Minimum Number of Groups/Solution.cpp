// 题目：2406. 将区间分为最少组数（Divide Intervals Into Minimum Number of Groups）
// 思路：按左端点排序后用最小堆维护各组的最晚结束时间，能复用空闲组就复用，堆的大小就是最少组数。
// 时间复杂度：O(n log n)，排序加每次堆操作；空间复杂度：O(n)，堆最多保存 n 个结束时间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minGroups(vector<vector<int>>& intervals) {  // intervals：若干闭区间，返回把它们划分成互不重叠的组所需的最少组数
        sort(intervals.begin(), intervals.end());  // 按左端点升序排序，保证按时间先后处理区间
        priority_queue<int, vector<int>, greater<int>> q;  // 小根堆：保存当前每个组中最晚的结束时间，堆顶是最早结束的组
        for (auto& e : intervals) {  // 依次处理排序后的每个区间
            if (q.size() && q.top() < e[0]) {  // 堆非空且结束最早的组已经早于当前左端点，说明该组空闲可复用
                q.pop();  // 弹出这一组的旧结束时间，相当于把它挪给当前区间
            }  // 复用分支结束
            q.push(e[1]);  // 把当前区间的右端点作为该组新的结束时间
        }  // 区间处理结束
        return q.size();  // 堆的大小就是同时活跃的组数，也就是最少需要的组数
    }  // 方法结束
};  // 题解类结束