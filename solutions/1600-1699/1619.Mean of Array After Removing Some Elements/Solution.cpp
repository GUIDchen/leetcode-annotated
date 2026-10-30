// 题目：1619. 删除某些元素后的数组均值（Mean of Array After Removing Some Elements）
// 思路：先排序，再去掉前后各 5% 的元素，对剩余 90% 的元素求和后除以个数；n 能被 20 整除，所以删除个数是整数。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，排序递归栈（快排/内省排序）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double trimMean(vector<int>& arr) {  // arr：长度为 20 的倍数的整数数组
        sort(arr.begin(), arr.end());  // 升序排序，让最小的 5% 和最大的 5% 分别落在两端
        int n = arr.size();  // 记录原数组长度，后面算区间与除数都要用
        double s = 0;  // 剩余元素的累加和，用浮点避免整数溢出与精度丢失
        for (int start = (int) (n * 0.05), i = start; i < n - start; ++i)  // start 是两端要跳过的个数，区间为 [start, n-start)
            s += arr[i];  // 逐项累加保留下来的中间段元素
        return s / (n * 0.9);  // 除以剩余元素个数（即原长度的 90%）得到均值
    }
};