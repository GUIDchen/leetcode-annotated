# 题目：1207. 独一无二的出现次数（Unique Number of Occurrences）
# 思路：用 Counter 统计每个值的出现次数，再看这些次数去重后的个数是否等于不同值的个数。
# 时间复杂度：O(n)，统计与去重各线性一次；空间复杂度：O(n)，需要保存频次表与去重后的频次集合。
class Solution:  # LeetCode 约定的题解类
    def uniqueOccurrences(self, arr: List[int]) -> bool:  # arr：输入数组；返回是否所有出现次数都互不相同
        cnt = Counter(arr)  # 一次遍历统计每个值的出现次数
        return len(set(cnt.values())) == len(cnt)  # 频次去重后个数等于不同值的个数，说明没有任何两个值次数相同
