# 题目：3356. 零数组变换 II（Zero Array Transformation II）
# 思路：二分答案 k，用差分数组判断前 k 个区间操作能否把 nums 全减成 0；可行性关于 k 单调，用 bisect_left 的 key 直接找第一个可行的 k。
# 时间复杂度：O((n+m) log m)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:  # nums：目标数组；queries：区间减操作
        def check(k: int) -> bool:  # 内层函数：判断只取前 k 个操作能否让数组归零
            d = [0] * (len(nums) + 1)  # 差分数组，多开一位承接 r+1 处的回扣
            for l, r, val in queries[:k]:  # 逐个套用前 k 个操作
                d[l] += val  # 区间左端加上减量
                d[r + 1] -= val  # 区间右端后一位减去减量
            s = 0  # 前缀累加值，等于当前位置被减掉的总量
            for x, y in zip(nums, d):  # 同步遍历目标值与差分值
                s += y  # 还原出当前位置的累计减量
                if x > s:  # 减量不足，x 无法归零
                    return False  # 该 k 不可行
            return True  # 所有位置都够减，可行

        m = len(queries)  # 操作总数
        l = bisect_left(range(m + 1), True, key=check)  # 在 0..m 上二分：key=check，返回第一个让 check 为 True 的下标，即最小可行 k
        return -1 if l > m else l  # 返回值大于 m 说明所有操作也不够，返回 -1；否则直接返回最小 k
