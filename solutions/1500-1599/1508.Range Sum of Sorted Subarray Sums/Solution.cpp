// 题目：1508. 子数组和排序后的区间和（Range Sum of Sorted Subarray Sums）
// 思路：枚举左右端点求出全部 n(n+1)/2 个子数组的和，排序后取第 left..right 项累加并取模。
// 时间复杂度：O(n^2 log n)，生成 n^2 个和再排序；空间复杂度：O(n^2)，存放全部子数组和。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int rangeSum(vector<int>& nums, int n, int left, int right) {  // nums：原数组；n：数组长度；left/right：区间端点（1-based）；返回该区间内元素之和模 1e9+7
        int arr[n * (n + 1) / 2];  // 子数组共 n(n+1)/2 个，用变长数组一次装下所有子数组和
        for (int i = 0, k = 0; i < n; ++i) {  // i 为子数组左端点，k 为写入 arr 的下标
            int s = 0;  // 以 i 开头的子数组的累加和
            for (int j = i; j < n; ++j) {  // j 为右端点，逐步向右扩展
                s += nums[j];  // 累加得到 nums[i..j] 的和
                arr[k++] = s;  // 存入结果数组，写指针右移
            }
        }  // 本行左端点枚举结束
        sort(arr, arr + n * (n + 1) / 2);  // 升序排序，题目要求的是排序后的序列
        int ans = 0;  // 区间和的累加器
        const int mod = 1e9 + 7;  // 取模常量 10^9+7
        for (int i = left - 1; i < right; ++i) {  // 题目下标 1-based，换算成 0-based 后取 [left-1, right-1]
            ans = (ans + arr[i]) % mod;  // 边加边取模，避免累加溢出
        }
        return ans;  // 返回区间和
    }
};