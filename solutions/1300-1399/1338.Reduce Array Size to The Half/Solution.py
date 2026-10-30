# 题目：1338. 数组大小减半（Reduce Array Size to The Half）
# 思路：用 Counter 统计每个值的出现次数，按出现次数从多到少贪心删除，累计删掉的元素数达到数组一半就停止，此时删除的数值种类数最少。
# 时间复杂度：O(n log n)，主要是对次数排序；空间复杂度：O(n)，计数表与排序结果。
class Solution:  # LeetCode 约定的题解类
    def minSetSize(self, arr: List[int]) -> int:  # arr 是待减半的数组，返回最少要删除多少个不同的值
        cnt = Counter(arr)  # 统计每个值出现的次数
        ans = m = 0  # ans 记删除的不同值个数，m 记已删除的元素总数
        for _, v in cnt.most_common():  # most_common 按出现次数从多到少返回 (值, 次数)，值用不到就忽略
            m += v  # 累计已删除的元素数
            ans += 1  # 集合大小加一
            if m * 2 >= len(arr):  # 已删元素达到总数的一半（乘 2 避免浮点误差）
                break  # 已经满足要求，提前跳出
        return ans  # 返回最少需要删除的不同值个数
