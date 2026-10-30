# 题目：2176. 统计数组中相等且可以被整除的数对（Count Equal and Divisible Pairs in an Array）
# 思路：枚举所有 i < j 的下标对，同时检查 nums[i] == nums[j] 与 (i*j) % k == 0。
# 时间复杂度：O(n^2)，双重循环；空间复杂度：O(1)，只用一个计数器。
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是整除条件里的除数；返回满足条件的数对个数
        ans = 0  # ans 统计答案，初值为 0
        for j in range(1, len(nums)):  # 外层枚举较大的下标 j，从 1 开始保证前面至少存在 i = 0
            for i, x in enumerate(nums[:j]):  # 内层用切片 nums[:j] 只取 j 之前的元素，enumerate 同时给出下标 i 与值 x
                ans += int(x == nums[j] and i * j % k == 0)  # int(布尔值) 把 True/False 转成 1/0，条件成立时答案加一（一个判断表达式就能完成累加）
        return ans  # 返回统计到的数对个数
