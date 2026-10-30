// 题目：4056. 统计相交区间对 I（Number of Intersecting Interval Pairs I）
// 思路：两个区间不相交当且仅当其中一个的右端点严格小于另一个的左端点；把左端点、右端点分别排序，先假设 C(n,2) 对全部相交，再按左端点从小到大扫描，用单调前进的指针 i 统计 ends[i] < start 的区间个数——这些区间都在当前区间开始之前就结束了，与当前区间必然不相交，从总数里扣掉即可（端点相触仍算相交）。
// 时间复杂度：O(n log n)，主要开销是两次排序，扫描是线性的；空间复杂度：O(n)，用于存放拆出来的左端点与右端点数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countIntersectingIntervals(vector<vector<int>>& intervals) {  // intervals：若干闭区间；返回其中相交的区间对数目
        int n = intervals.size();  // n 为区间个数，全部区间对共有 C(n,2) 个
        vector<int> starts(n), ends(n);  // 把左右端点拆成两个数组，便于各自独立排序
        for (int i = 0; i < n; i++) {  // 逐个区间拆出两个端点
            starts[i] = intervals[i][0];  // 收集左端点
            ends[i] = intervals[i][1];  // 收集右端点
        }  // 端点拆分结束
        sort(starts.begin(), starts.end());  // 左端点升序
        sort(ends.begin(), ends.end());  // 右端点升序
        int ans = n * (n - 1) / 2;  // 先假设所有区间对都相交，下面再减去不相交的对数
        int i = 0;  // i 指向 ends 中第一个“尚未被判定为早于当前起点结束”的位置，只前进不回退
        for (int start : starts) {  // 按左端点从小到大扫描，右端点指针随之单调前进
            while (i < n && ends[i] < start) {  // 只有 end < start 才算不相交，端点相触仍算相交
                i++;  // 指针前移，把在 start 之前结束的区间都数进来
            }  // while 循环结束
            ans -= i;  // 这 i 个区间都在当前区间开始前结束，与当前区间两两不相交，从总数中扣除
        }  // for 循环结束
        return ans;  // 返回相交区间对数
    }  // 方法结束
};  // 类定义结束