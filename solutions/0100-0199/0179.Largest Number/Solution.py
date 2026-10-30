# 题目：179. 最大数（Largest Number）
# 思路：把整数转成字符串，用 cmp_to_key 定义「a+b 与 b+a 谁更大」的比较器降序排序，再拼接；全 0 时特判返回 "0"。
# 时间复杂度：O(n log n * L)，每次比较都要拼接长度 L 的字符串；空间复杂度：O(n * L)，保存字符串列表。
class Solution:  # LeetCode 约定的题解类
    def largestNumber(self, nums: List[int]) -> str:  # nums：待拼接的非负整数数组
        nums = [str(v) for v in nums]  # 先全部转成字符串，之后按字符串拼接结果比较大小
        nums.sort(key=cmp_to_key(lambda a, b: 1 if a + b < b + a else -1))  # a+b 更小说明 a 应排后面，返回 1 表示 a 大于 b；相等时返回 -1 保持稳定
        return "0" if nums[0] == "0" else "".join(nums)  # 首位为 "0" 说明全是 0，返回单个 "0"；否则依序拼接
