# 题目：2815. 数组中的最大数对和（Max Pair Sum in an Array）
# 思路：两重循环枚举所有下标对，把每个数转成字符串后取最大字符即最大数位，数位相同才构成数对，在其中取最大的元素和。
# 时间复杂度：O(n²·log V)，枚举数对 O(n²)，求最大数位 O(log V)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxSum(self, nums: List[int]) -> int:  # nums：输入数组；返回最大数对和，没有合法数对时返回 -1
        ans = -1  # ans 初值 -1，正好对应「不存在合法数对」的返回值
        for i, x in enumerate(nums):  # 枚举第一个数的下标与数值
            for y in nums[i + 1 :]:  # 只枚举后面的元素，每次配对只算一次
                v = x + y  # 当前数对的和
                if ans < v and max(str(x)) == max(str(y)):  # 两数最大数位（字符串最大的字符）相同且和更大时才更新
                    ans = v  # 更新答案
        return ans  # 返回答案；没有合法数对时仍是 -1
