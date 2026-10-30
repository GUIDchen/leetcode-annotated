# 题目：1590. 使数组和能被 P 整除（Make Sum Divisible by P）
# 思路：要让总和余数 k 变成 0，需删掉一段和模 p 恰为 k 的子数组；用哈希表记录前缀余数最近出现的下标求最短长度。
# 时间复杂度：O(n)，一次遍历加哈希查询；空间复杂度：O(n)，哈希表最多保存 n 个余数。
class Solution:  # LeetCode 约定的题解类
    def minSubarray(self, nums: List[int], p: int) -> int:  # nums 为数组，p 为模数
        k = sum(nums) % p  # 总和模 p 的余数，即需要被删掉的那部分
        if k == 0:  # 总和已能整除 p
            return 0  # 不用删除任何元素
        last = {0: -1}  # 余数 → 该余数最近出现的下标；0 对应空前缀，下标记 -1
        cur = 0  # 当前位置的前缀和余数
        ans = len(nums)  # 答案初值取 n，等价于“暂时还没找到合法子数组”
        for i, x in enumerate(nums):  # 逐个元素维护前缀和
            cur = (cur + x) % p  # 更新前缀和余数
            target = (cur - k + p) % p  # 要删掉的那段的余数，加 p 保证结果非负
            if target in last:  # 该余数之前出现过，说明中间那段的和模 p 恰为 k
                ans = min(ans, i - last[target])  # 用更短的长度更新答案
            last[cur] = i  # 记录当前余数的最新下标
        return -1 if ans == len(nums) else ans  # 长度仍为 n 说明删不出合法子数组
