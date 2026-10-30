// 题目：1855. 下标对中的最大距离（Maximum Distance Between a Pair of Values）
// 思路：nums1、nums2 都是非递增数组，先把 nums2 反转成非递减，再对每个 i 二分出「最后一个 >= nums1[i] 的位置」，换算回原下标 j，用 j - i 更新答案。
// 时间复杂度：O(n log m + m)，n = len(nums1)、m = len(nums2)，每个 i 做一次二分；空间复杂度：O(1)，反转在原地完成，只用常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 均非递增，求满足 i <= j 且 nums1[i] <= nums2[j] 的最大 j - i
        int ans = 0;  // 答案初值：没有任何合法下标对时距离为 0
        reverse(nums2.begin(), nums2.end());  // 反转后 nums2 变成非递减，才能用它做二分查找
        for (int i = 0; i < nums1.size(); ++i) {  // 枚举 nums1 的每个下标 i 作为左端点
            int j = nums2.size() - (lower_bound(nums2.begin(), nums2.end(), nums1[i]) - nums2.begin()) - 1;  // lower_bound 找出反转数组里第一个 >= nums1[i] 的位置，换算回原下标即满足 nums1[i] <= nums2[j] 的最大 j
            ans = max(ans, j - i);  // j < i 时差值为负，max 会自然保留更优的旧答案
        }  // nums1 枚举结束
        return ans;  // 返回最大距离
    }  // 方法结束
};  // 类定义结束