// 题目：454. 四数相加 II（4Sum II）
// 思路：先枚举 nums1、nums2 的所有两数组合，用哈希表统计每种和的出现次数；再枚举 nums3、nums4，累加 -(c+d) 的次数即为 a+b+c+d=0 的四元组数。
// 时间复杂度：O(n^2)，两组两两组合各枚举一次；空间复杂度：O(n^2)，哈希表最多存 n^2 个不同的和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {  // 四个等长数组；返回满足 a+b+c+d == 0 的下标元组个数
        unordered_map<int, int> cnt;  // 哈希表：nums1 与 nums2 的两数之和 → 该和出现的次数
        for (int a : nums1) {  // 枚举第一个数组的元素
            for (int b : nums2) {  // 枚举第二个数组的元素
                ++cnt[a + b];  // 把这一对元素的和计入统计
            }  // 结束 nums2 的枚举
        }  // 结束 nums1 的枚举
        int ans = 0;  // ans：满足条件的四元组个数
        for (int c : nums3) {  // 枚举第三个数组的元素
            for (int d : nums4) {  // 枚举第四个数组的元素
                ans += cnt[-(c + d)];  // 需要 a+b == -(c+d)，把该和的次数累加进来（和不存在时自动为 0）
            }  // 结束 nums4 的枚举
        }  // 结束 nums3 的枚举
        return ans;  // 返回四元组总数
    }  // 结束 fourSumCount
};  // 结束 Solution 类