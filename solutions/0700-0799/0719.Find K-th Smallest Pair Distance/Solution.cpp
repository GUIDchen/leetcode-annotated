// 题目：719. 找出第 K 小的数对距离（Find K-th Smallest Pair Distance）
// 思路：先排序，再对答案 dist 二分；用双指针（二分左端点）统计距离不超过 dist 的数对个数，个数 >= k 即可行。
// 时间复杂度：O(n log n + n log W)，W 为最大差值；空间复杂度：O(1)（不计排序的栈开销）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestDistancePair(vector<int>& nums, int k) {  // nums：非负数组；k：第 k 小（1-based）
        sort(nums.begin(), nums.end());  // 排序后数组有序，统计「距离 <= dist 的数对个数」才能用二分
        int left = 0, right = nums.back() - nums.front();  // 答案下界是 0，上界是「最大值 - 最小值」
        while (left < right) {  // 在区间 [left, right] 上二分最小的可行距离
            int mid = (left + right) >> 1;  // 取中点作为候选距离
            if (count(mid, k, nums) >= k)  // 距离 <= mid 的数对不少于 k 个，说明答案不会超过 mid
                right = mid;  // 收缩右边界；mid 本身可能就是答案，故保留
            else  // 否则距离 <= mid 的数对不足 k 个，答案必然大于 mid
                left = mid + 1;  // 排除 mid 及更小的距离
        }  // 循环退出时 left == right，即最小的可行距离
        return left;  // 返回第 k 小的数对距离
    }  // 方法结束

    int count(int dist, int k, vector<int>& nums) {  // count：统计数对距离 <= dist 的个数（参数 k 未使用）
        int cnt = 0;  // 计数器：满足条件的数对总数
        for (int i = 0; i < nums.size(); ++i) {  // 以 i 为右端点，统计能与它组成合法数对的左端点个数
            int target = nums[i] - dist;  // 只要左端点值 >= nums[i] - dist，两数距离就不超过 dist
            int j = lower_bound(nums.begin(), nums.end(), target) - nums.begin();  // 二分出第一个不小于 target 的下标 j（保证 j <= i）
            cnt += i - j;  // 下标区间 [j, i-1] 全部合法，共 i - j 个左端点
        }  // 内层循环结束
        return cnt;  // 返回距离不超过 dist 的数对总数
    }  // count 方法结束
};  // 类定义结束