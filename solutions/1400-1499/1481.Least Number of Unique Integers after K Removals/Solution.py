# 题目：1481. 不同整数的最少数目（Least Number of Unique Integers after K Removals）
# 思路：先用 Counter 统计每个数的出现次数，把次数排序；为了让剩下的不同整数最少，优先删掉出现次数最少的数，每删光一种就少一个不同整数。
# 时间复杂度：O(n + u log u)，u 为不同整数个数；空间复杂度：O(u)，哈希表与计数列表。
class Solution:  # LeetCode 约定的题解类
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:  # arr：输入数组；k：最多可删除的元素个数
        cnt = Counter(arr)  # 统计每个元素出现的次数（Counter 由题解环境提供）
        for i, v in enumerate(sorted(cnt.values())):  # 频次从小到大排序后逐个尝试删空，i 是已彻底删掉的种类数
            k -= v  # 删光当前这种数，消耗它的全部出现次数
            if k < 0:  # 次数不够，说明这种数只能删一部分、仍然存在
                return len(cnt) - i  # 前 i 种已删光，剩下的不同整数个数为总数减 i
        return 0  # k 足够删光所有数，不同整数个数为 0
