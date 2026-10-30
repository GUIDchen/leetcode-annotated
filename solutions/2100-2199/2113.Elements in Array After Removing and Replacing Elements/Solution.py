# 题目：2113. 查询删除和添加元素后的数组（Elements in Array After Removing and Replacing Elements）
# 思路：操作以 2n 分钟为一个周期：前 n 分钟不断删除首元素，后 n 分钟不断在尾部补 0（前缀不变）。
# 时间复杂度：O(m)，m 为查询个数；空间复杂度：O(m)，只存答案。
class Solution:# LeetCode 约定的题解类
    def elementInNums(self, nums: List[int], queries: List[List[int]]) -> List[int]:# nums：初始数组；queries 每项 [t, i]；返回每个查询的答案
        n, m = len(nums), len(queries)# n 为数组长度，m 为查询个数
        ans = [-1] * m# 答案数组，默认 -1 表示该下标已被删除或已变成 0
        for j, (t, i) in enumerate(queries):# 逐条处理查询，j 是答案下标，t 是时刻，i 是询问的下标
            t %= 2 * n# 操作以 2n 分钟为一个周期，先把时刻归约
            if t < n and i < n - t:# 前 n 分钟在删首元素，剩余部分是原数组的后缀 nums[t:]
                ans[j] = nums[i + t]# 后缀中的第 i 个就是原数组的 nums[i+t]
            elif t > n and i < t - n:# 后 n 分钟在尾部补 0，只有前 t-n 个位置还是原值
                ans[j] = nums[i]# 该位置未被覆盖，仍等于原数组对应元素
        return ans# 返回全部查询结果
