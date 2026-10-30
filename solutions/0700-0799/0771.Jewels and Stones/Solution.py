# 题目：771. 宝石与石头（Jewels and Stones）
# 核心思路：把 jewels 转成集合，再对 stones 逐个判断是否在集合中并计数。
# 时间复杂度 O(|jewels| + |stones|)；空间复杂度 O(|jewels|)（集合大小不超过宝石种类数）。
class Solution:  # LeetCode 约定的题解类
    def numJewelsInStones(self, jewels: str, stones: str) -> int:  # jewels：宝石类型；stones：拥有的石头；返回其中宝石的个数
        s = set(jewels)  # 把 jewels 转成集合，让「是否宝石」的判断降到 O(1)
        return sum(c in s for c in stones)  # 生成器逐个判断，sum 把 True 当 1 累加，直接得到宝石数量
