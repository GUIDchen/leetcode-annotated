// 题目：2918. 数组的最小相等和（Minimum Equal Sum of Two Arrays After Replacing Zeros）
// 思路：先把每个 0 都替换成 1 得到两数组的最小和，令 s1<=s2；相等直接返回，否则只有 nums1 含 0 才能把和继续抬高到 s2。
// 时间复杂度：O(n+m)，每个元素只累加一次（递归仅交换参数、不复制数组）；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minSum(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两个可以把 0 替换为正整数的数组
        long long s1 = 0, s2 = 0;  // s1、s2：把所有 0 替换成 1 后两数组的最小和，用 long long 防溢出
        bool hasZero = false;  // 记录 nums1 中是否存在 0，决定较小和是否还能继续上调
        for (int x : nums1) {  // 先统计 nums1 的最小和
            hasZero |= x == 0;  // 遇到 0 就置位，说明这个数组的和之后还可以增大
            s1 += max(x, 1);  // 0 至少替换成 1，非 0 保持原值，所以取 max(x, 1)
        }  // nums1 遍历结束
        for (int x : nums2) {  // 再统计 nums2 的最小和
            s2 += max(x, 1);  // 同样把 0 视作 1 累加
        }  // nums2 遍历结束
        if (s1 > s2) {  // 让 s1 始终是较小的那个和，方便统一讨论
            return minSum(nums2, nums1);  // 交换参数递归，复用同一段逻辑
        }  // 分支结束
        if (s1 == s2) {  // 两边最小和相等时无需再调整
            return s1;  // 直接返回这个相等的和
        }  // 分支结束
        return hasZero ? s2 : -1;  // s1<s2：nums1 有 0 才能把和抬到 s2，否则永远无法相等
    }  // minSum 结束
};  // 类定义结束