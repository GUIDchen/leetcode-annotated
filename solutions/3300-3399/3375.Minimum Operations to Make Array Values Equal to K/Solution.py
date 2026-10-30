# 题目：3375. 使数组的值全部为 K 的最少操作次数（Minimum Operations to Make Array Values Equal to K）
# 思路：每次操作可把某个值 h 及其倍数的所有更大元素一起降到 h。因此要先把所有比 k 大的不同值逐个降下来；若数组中出现比 k 小的值则无解，k 已在数组中时可少做一次。
# 时间复杂度：O(n)，一次遍历统计不同值与最小值；空间复杂度：O(n)，集合最多存 n 个不同值。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是目标值
        s = set()  # 集合：记录数组中所有出现过的不同值
        mi = inf  # 记录数组最小值，初值为正无穷
        for x in nums:  # 遍历数组中的每个元素
            if x < k:  # 操作只能把值变小，出现比 k 小的值就无解
                return -1  # 无法让所有元素都等于 k，返回 -1
            mi = min(mi, x)  # 维护当前最小值
            s.add(x)  # 把当前值加入去重集合
        return len(s) - int(k == mi)  # 不同值个数减去 1（k 已在数组中时可少做一次操作，int(k == mi) 即是否要减）
