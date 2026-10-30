// 题目：1509. 三次操作后最大值与最小值的最小差（Minimum Difference Between Largest and Smallest Value in Three Moves）
// 思路：排序后，3 次「把某元素改成任意值」等价于删掉「最小的 l 个 + 最大的 3-l 个」，枚举 l=0..3 取剩余首尾差的最小值。
// 时间复杂度：O(n log n)，由排序决定；空间复杂度：O(1)（不计排序自身的栈空间）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDifference(vector<int>& nums) {  // nums：输入数组，允许把其中至多 3 个元素替换成任意值
        int n = nums.size();  // n：数组长度
        if (n < 5) {  // 元素少于 5 个时，3 次操作足以把所有元素改成同一个值
            return 0;  // 极差必然为 0，直接返回
        }  // 结束提前返回的分支
        sort(nums.begin(), nums.end());  // 升序排序，排序后极差就是「最后一个 - 第一个」
        long long ans = 1L << 60;  // ans：最小极差，初值 2^60 充当无穷大，用 long long 防止相减溢出
        for (int l = 0; l <= 3; ++l) {  // l：从左端（最小值一侧）替换掉的元素个数，最多 3 个
            int r = 3 - l;  // r：从右端（最大值一侧）替换掉的元素个数，两者合计恰好是 3 次操作
            ans = min(ans, 1LL * nums[n - 1 - r] - nums[l]);  // 剩余区间是 [l, n-1-r]，用 1LL 把差值提升为 long long 再比较
        }  // 结束四种划分方案的枚举
        return ans;  // 四种方案里的最小值就是答案
    }  // 结束方法
};  // 结束题解类