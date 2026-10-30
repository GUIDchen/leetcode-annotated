# 题目：347. 前 K 个高频元素（Top K Frequent Elements）
# 思路：用 Counter 统计每个元素的出现次数，再取 most_common(k) 得到出现次数最多的 k 个元素。
# 时间复杂度：O(n + m log m)，m 为不同元素个数（Counter 内部用堆挑前 k 个）；空间复杂度：O(m)。
class Solution:  # LeetCode 约定的题解类
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:  # nums：输入数组；k：要返回的高频元素个数
        cnt = Counter(nums)  # Counter 一次性统计每个元素的出现次数，键是元素、值是次数
        return [x for x, _ in cnt.most_common(k)]  # most_common(k) 返回 (元素, 次数) 二元组列表，按次数降序；下划线丢弃次数只留元素值
