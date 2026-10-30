// 题目：611. 有效三角形的个数（Valid Triangle Number）
// 思路：先排序，固定两条较短边 i、j，用二分找到最后一条满足 nums[k] < nums[i] + nums[j] 的下标 k，这一段长度即答案增量。
// 时间复杂度：O(n²log n)，双层循环加二分；空间复杂度：O(log n)，排序所需的栈空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int triangleNumber(vector<int>& nums) {  // 统计数组中能组成三角形的三元组个数
        ranges::sort(nums);  // 排序后才有单调性，从而可用二分统计第三边
        int ans = 0, n = nums.size();  // ans 累计答案，n 是数组长度
        for (int i = 0; i < n - 2; ++i) {  // 枚举最短边 i，至少还要留两条边所以上界是 n-2
            for (int j = i + 1; j < n - 1; ++j) {  // 枚举次短边 j，必须严格在 i 之后，上界留一条边给 k
                int sum = nums[i] + nums[j];  // 两短边之和，第三边必须严格小于它才能构成三角形
                auto it = ranges::lower_bound(nums.begin() + j + 1, nums.end(), sum);  // 在 j 之后找第一个大于等于 sum 的位置，它左边的都满足条件
                int k = int(it - nums.begin()) - 1;  // 减一后得到最后一个满足条件的下标 k
                ans += max(0, k - j);  // 合法的第三边个数是 k - j，取 max 防止无解时出现负数
            }  // j 枚举结束
        }  // i 枚举结束
        return ans;  // 返回有效三角形的总数
    }  // 方法结束
};  // 类定义结束
