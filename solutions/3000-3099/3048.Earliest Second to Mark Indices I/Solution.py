# 题目：3048. 标记所有下标的最早秒数 I（Earliest Second to Mark Indices I）
# 思路：二分答案秒数 t，check(t) 用字典记录每个下标在 changeIndices 前 t 项中最后一次出现的秒数，再按时间顺序模拟攒减一次数与标记。
# 时间复杂度：O((n + m) log m)，每次 check 为 O(t)、二分 log m 次；空间复杂度：O(n + m)，last 字典与切片副本。
class Solution:  # LeetCode 约定的题解类
    def earliestSecondToMarkIndices(  # nums：各下标初始值；changeIndices：每秒可以操作的下标
        self, nums: List[int], changeIndices: List[int]  # 参数续行：self、nums、changeIndices
    ) -> int:  # 返回最早的可行秒数，无解则返回 -1
        def check(t: int) -> bool:  # 判断前 t 秒之内能否把所有下标标记完
            decrement = 0  # 已经攒下的减一操作次数
            marked = 0  # 已经标记好的下标个数
            last = {i: s for s, i in enumerate(changeIndices[:t])}  # 下标 i 映射到它在前 t 秒中最后一次出现的秒数（后者覆盖前者）
            for s, i in enumerate(changeIndices[:t]):  # 按时间顺序逐秒模拟
                if last[i] == s:  # 这是下标 i 的最后一次出现机会，必须现在标记
                    if decrement < nums[i - 1]:  # 攒下的减一次数不足以把 nums[i-1] 减到 0
                        return False  # 前 t 秒不可行
                    decrement -= nums[i - 1]  # 花掉 nums[i-1] 次操作，把该下标清零
                    marked += 1  # 清零后标记，已标记数加一
                else:  # 不是最后一次出现
                    decrement += 1  # 这一秒先攒下一次减一的机会
            return marked == len(nums)  # 全部下标都被标记才算成功

        m = len(changeIndices)  # 可用的总秒数
        l = bisect_left(range(1, m + 2), True, key=check) + 1  # 在 [1, m+1] 上二分第一个使 check 为真的位置，关键在于用 bisect_left 的 key 参数；m+1 是无解哨兵
        return -1 if l > m else l  # 超过总秒数说明无解，返回 -1，否则返回最小秒数
