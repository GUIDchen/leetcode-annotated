// 题目：2006. 差的绝对值为 K 的数对数目（Count Number of Pairs With Absolute Difference K）
// 思路：数据范围很小，直接双重枚举所有下标对 (i, j) 且 i < j，统计绝对差恰好等于 k 的对数。
// 时间复杂度：O(n^2)，两层循环；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:
    int countKDifference(vector<int>& nums, int k) {  // nums 是输入数组；k 是要求的绝对差；返回满足条件的数对个数
        int n = nums.size();  // n 是数组长度
        int ans = 0;  // ans 累计满足条件的数对个数
        for (int i = 0; i < n; ++i) {  // 枚举数对中的第一个下标 i
            for (int j = i + 1; j < n; ++j) {  // 只枚举 j > i，保证每个数对只被统计一次
                ans += abs(nums[i] - nums[j]) == k;  // 若绝对差等于 k，比较结果为 true，累加时相当于 +1
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回数对总数
    }  // countKDifference 方法结束
};  // Solution 类结束