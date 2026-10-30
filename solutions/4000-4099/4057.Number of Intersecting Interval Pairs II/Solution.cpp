// 题目：4057. 统计相交区间对 II（Number of Intersecting Interval Pairs II）
// 思路：与 I 完全同构——不相交等价于一个区间的右端点严格小于另一个区间的左端点；把左右端点分别排序，先取 C(n,2)，再按左端点顺序用单调前进的指针统计在其之前就结束的区间个数并扣减；差别只在 n 变大，答案改用 long long（Python 天然支持大整数）承接 C(n,2) 以免溢出。
// 时间复杂度：O(n log n)，主要开销是两次排序；空间复杂度：O(n)，用于存放左右端点数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {  // intervals：若干闭区间；返回相交的区间对数目（规模更大，返回值可能是 64 位）
        int n = intervals.size();  // n 为区间个数，全部区间对共有 C(n,2) 个
        vector<int> starts(n), ends(n);  // 把左右端点拆成两个数组，便于各自独立排序
        for (int i = 0; i < n; i++) {  // 逐个区间拆出两个端点
            starts[i] = intervals[i][0];  // 收集左端点
            ends[i] = intervals[i][1];  // 收集右端点
        }  // 端点拆分结束
        sort(starts.begin(), starts.end());  // 左端点升序
        sort(ends.begin(), ends.end());  // 右端点升序
        long long ans = 1LL * n * (n - 1) / 2;  // 先假设所有区间对都相交；1LL 把乘法提升到 64 位，避免 n 很大时溢出
        int i = 0;  // i 指向 ends 中第一个“不早于当前起点结束”的位置，只前进不回退
        for (int start : starts) {  // 按左端点从小到大扫描，右端点指针随之单调前进
            while (i < n && ends[i] < start) {  // 只有 end < start 才算不相交，端点相触仍算相交
                i++;  // 指针前移，把在 start 之前结束的区间都数进来
            }  // while 循环结束
            ans -= i;  // 这 i 个区间都在当前区间开始前结束，与当前区间两两不相交，从总数中扣除
        }  // for 循环结束
        return ans;  // 返回相交区间对数
    }  // 方法结束
};  // 类定义结束