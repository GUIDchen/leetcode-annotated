# 3843. 频率唯一的第一个元素 / First Element with Unique Frequency（中等）
# 核心思路：先用哈希表统计每个元素的出现次数，再统计每种出现次数被多少个不同元素拥有，最后按原数组顺序找第一个“其出现次数在全数组中唯一”的元素。
# 复杂度：时间 O(n)，空间 O(不同元素个数)。
class Solution:  # LeetCode 要求的类名
    def firstUniqueFreq(self, nums: List[int]) -> int:  # 返回第一个出现次数唯一的元素，不存在则返回 -1
        cnt = Counter(nums)  # cnt[x]：元素 x 在数组中出现的次数
        freq = Counter(cnt.values())  # freq[v]：出现次数恰好等于 v 的元素种类数
        for x in nums:  # 按原数组顺序检查
            if freq[cnt[x]] == 1:  # 该元素的出现次数没有别的元素拥有，即为唯一频率
                return x  # 第一个满足条件的元素就是答案
        return -1  # 不存在频率唯一的元素
