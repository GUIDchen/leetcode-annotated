# 题目：1426. 数元素（Counting Elements）
# 核心思路：用 Counter 统计每个值出现的次数；只要 x+1 也出现过，就把值为 x 的元素个数全部累加进答案。
# 时间复杂度：O(n)，遍历计数表一次；空间复杂度：O(V)，V 为不同取值的个数。
class Solution:  # LeetCode 约定的题解类
    def countElements(self, arr: List[int]) -> int:  # arr：整数数组
        cnt = Counter(arr)  # 统计每个值出现的次数
        return sum(v for x, v in cnt.items() if cnt[x + 1])  # x+1 也在数组中时，把值为 x 的元素个数累加进答案
