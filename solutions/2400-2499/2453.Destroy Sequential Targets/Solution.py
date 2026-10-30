# 题目：2453. 摧毁一系列目标（Destroy Sequential Targets）
# 思路：能被同一轮摧毁的目标，其值对 space 取模的余数相同；先用 Counter 统计每个余数类的目标个数，再按原数组顺序挑出所在类最大（同大小取值更小者）的目标。
# 时间复杂度：O(n)，对数组做两遍线性遍历；空间复杂度：O(n)，计数器最多保存 n 个不同的余数。
class Solution:  # LeetCode 约定的题解类
    def destroyTargets(self, nums: List[int], space: int) -> int:  # nums：目标值数组；space：每轮推进的距离
        cnt = Counter(v % space for v in nums)  # 生成器推导式配 Counter：统计每个余数类各有多少个目标
        ans = mx = 0  # ans 记录答案值，mx 记录当前最优余数类的大小
        for v in nums:  # 按原数组顺序挑选最合适的起始目标
            t = cnt[v % space]  # 以当前目标为起点时，同一轮能摧毁的目标总数
            if t > mx or (t == mx and v < ans):  # 数量更多，或数量相同但值更小（题目要求取最小值）
                ans = v  # 更新答案
                mx = t  # 更新当前最优数量
        return ans  # 返回摧毁目标数最多时可选的最小起始目标值
