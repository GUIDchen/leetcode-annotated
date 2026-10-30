// 题目：2563. 统计公平数对的数目（Count the Number of Fair Pairs）
// 核心思路：先排序，固定较小的下标 i，再对后缀二分出满足 lower <= nums[i]+nums[j] <= upper 的 j 的区间 [j, k)。
// 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(1)（不计排序所需的栈空间）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countFairPairs(vector<int>& nums, int lower, int upper) {  // nums：输入数组；lower/upper：和的下界与上界（闭区间）
        long long ans = 0;  // 公平数对总数，最大可达 O(n^2)，必须用 long long
        sort(nums.begin(), nums.end());  // 升序排序后，右端点相对 i 才具有单调性，可以二分
        for (int i = 0; i < nums.size(); ++i) {  // 枚举数对中较小的下标 i
            auto j = lower_bound(nums.begin() + i + 1, nums.end(), lower - nums[i]);  // 在 i 之后找第一个使 nums[i]+nums[j] >= lower 的位置
            auto k = lower_bound(nums.begin() + i + 1, nums.end(), upper - nums[i] + 1);  // 找第一个使和 > upper 的位置（+1 把闭区间转成半开区间）
            ans += k - j;  // 两个位置之间的元素个数就是合法的 j 的个数
        }
        return ans;  // 返回公平数对总数
    }
};