# 题目：1394. 找出数组中的幸运数（Find Lucky Integer in an Array）
# 思路：用 Counter 统计每个数值的出现次数，在所有「数值等于它出现次数」的键里取最大值；若一个都没有，则用 default 兜底返回 -1。
# 时间复杂度：O(n)，统计与求最大值各扫一遍；空间复杂度：O(n)，哈希表保存不同的数值。
class Solution:  # LeetCode 约定的题解类
    def findLucky(self, arr: List[int]) -> int:  # arr 是输入数组
        cnt = Counter(arr)  # 统计每个数值出现的次数
        return max((x for x, v in cnt.items() if x == v), default=-1)  # 生成器筛出 x == 出现次数的数值，max 取其中最大的；default=-1 表示没有这样的数值时返回 -1
