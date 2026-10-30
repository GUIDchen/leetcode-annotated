// 题目：2226. 每个小孩最多能分到多少糖果（Maximum Candies Allocated to K Children）
// 思路：二分答案。每人分 x 颗可行则分更少也一定可行，答案有单调性；把每堆按 x 尽量切分累加份数，份数达到 k 即说明 x 可行。
// 时间复杂度：O(n log C)，n 为堆数、C 为最大堆大小，每轮二分 O(n) 统计；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumCandies(vector<int>& candies, long long k) {  // candies：每堆的糖果数；k：小孩人数
        int l = 0, r = ranges::max(candies);  // 二分区间 [l, r]：0 一定可行，最大堆大小是答案上界
        while (l < r) {  // 区间尚未收缩到单点，继续二分
            int mid = (l + r + 1) >> 1;  // 上取整的中点，配合后面的 l = mid 避免死循环
            long long cnt = 0;  // 统计每人分 mid 颗时能切出的总份数，用 long long 防溢出
            for (int x : candies) {  // 逐堆计算份数
                cnt += x / mid;  // 每堆最多切出 x / mid 份；mid 恒为正，不会除零
            }
            if (cnt >= k) {  // 份数够分，mid 可行，尝试更大的值
                l = mid;  // 保留 mid，把区间下界抬到 mid
            } else {  // 份数不够，mid 偏大
                r = mid - 1;  // 答案至多为 mid - 1
            }
        }
        return l;  // 区间收缩到单点即为可行的最大值
    }
};
