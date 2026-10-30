// 题目：1577. 数的平方等于两数乘积的方法数（Number of Ways Where Square of Number Is Equal to Product of Two Numbers）
// 思路：先分别用哈希表统计两个数组里所有数对的乘积频次，再对另一个数组的每个元素 x 查表累加 x*x 的出现次数，两种情况相加。
// 时间复杂度：O(m^2 + n^2)，两数组各枚举一次数对；空间复杂度：O(m^2)，乘积哈希表最多存 m 个元素的两两乘积。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {  // nums1/nums2：两个整数数组，分别轮流充当「平方来源」和「乘积来源」
        auto cnt1 = count(nums1);  // 统计 nums1 中所有数对乘积的出现次数
        auto cnt2 = count(nums2);  // 统计 nums2 中所有数对乘积的出现次数
        return cal(cnt1, nums2) + cal(cnt2, nums1);  // 两种情况相加：nums1 的元素做平方去匹配 nums2 的乘积，反之亦然
    }  // 第一种情况的方法体结束

    unordered_map<long long, int> count(vector<int>& nums) {  // 统计数组 nums 中所有下标对 i<j 的乘积频次
        unordered_map<long long, int> cnt;  // 键是乘积（用 long long 防止 int 乘法溢出），值是出现次数
        for (int i = 0; i < nums.size(); i++) {  // 枚举数对的第一个下标 i
            for (int j = i + 1; j < nums.size(); j++) {  // 枚举第二个下标 j，只取 j>i 使每个数对恰好统计一次
                cnt[(long long) nums[i] * nums[j]]++;  // 乘积出现一次，频次加一
            }  // 内层循环结束
        }  // 外层循环结束
        return cnt;  // 返回乘积频次表
    }  // count 方法结束

    int cal(unordered_map<long long, int>& cnt, vector<int>& nums) {  // cal：用乘积频次表统计 nums 中每个元素的平方能匹配多少个数对
        int ans = 0;  // 累计的答案
        for (int x : nums) {  // 遍历 nums 的每个元素 x
            ans += cnt[(long long) x * x];  // x*x 作为键查频次并累加，三元组按数对下标区分，所以频次可直接相加
        }  // for 循环结束
        return ans;  // 返回匹配总数
    }  // cal 方法结束
};  // 题解类结束
