# 题目：1865. 找出和为指定值的下标对（Finding Pairs With a Certain Sum）
# 思路：nums1 不变、nums2 会随 add 改变，于是给 nums2 建值频次表；add 时先减旧值再加新值，count 时枚举 nums1 的 x，累加 tot - x 的出现次数。
# 时间复杂度：构造 O(n)，add O(1)，count O(len(nums1))；空间复杂度：O(len(nums2))，用于存放频次表。
class FindSumPairs:  # LeetCode 要求的 FindSumPairs 类
    def __init__(self, nums1: List[int], nums2: List[int]):  # 构造函数：保存两个数组并预先统计 nums2 的值频次
        self.cnt = Counter(nums2)  # 用 Counter 建立 nums2 的频次表，缺失的键自动按 0 返回
        self.nums1 = nums1  # 保存 nums1（只参与配对查询，不会被修改）
        self.nums2 = nums2  # 保存 nums2（add 会原地修改它）

    def add(self, index: int, val: int) -> None:  # 把 nums2[index] 加上 val，并同步维护频次表
        self.cnt[self.nums2[index]] -= 1  # 先从频次表里去掉旧值的一次出现
        self.nums2[index] += val  # 原地修改 nums2 的值
        self.cnt[self.nums2[index]] += 1  # 再把新值的一次出现加进频次表

    def count(self, tot: int) -> int:  # 统计有多少对 (nums1[i], nums2[j]) 的和恰好等于 tot
        return sum(self.cnt[tot - x] for x in self.nums1)  # 枚举 nums1 的每个 x，累加另一半 tot - x 在 nums2 中的出现次数


# 下面几行是 LeetCode 判题器生成的调用示例，仅供参考，不属于题解逻辑
# Your FindSumPairs object will be instantiated and called as such:
# obj = FindSumPairs(nums1, nums2)
# obj.add(index,val)
# param_2 = obj.count(tot)
