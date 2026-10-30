# 题目：2605. 从两个数字数组里生成最小数字（Form Smallest Number From Two Digit Arrays）
# 思路：枚举所有数字对；存在公共数字时答案是更小的那个一位数，否则在 10*a+b 与 10*b+a 中取较小者。
# 时间复杂度：O(n·m)，枚举全部数字对；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minNumber(self, nums1: List[int], nums2: List[int]) -> int:  # nums1/nums2：两个数字数组；返回能组成的最小数字
        ans = 100  # 初始上界 100，大于任何两位数
        for a in nums1:  # 枚举 nums1 的数字 a
            for b in nums2:  # 枚举 nums2 的数字 b
                if a == b:  # 两个数组有公共数字，可以只用一位
                    ans = min(ans, a)  # 一位数时取更小的数字
                else:  # 否则只能拼成两位数
                    ans = min(ans, 10 * a + b, 10 * b + a)  # 两种拼接顺序取较小者，再与当前答案比较
        return ans  # 返回最小数字
