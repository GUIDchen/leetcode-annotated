# 题目：2808. 使循环数组所有元素相等的最少秒数（Minimum Seconds to Equalize a Circular Array）
# 思路：用 defaultdict 按数值收集它出现的所有下标；环形数组中同一数值相邻下标的「最大空档」决定它把整圈同化所需的秒数，对所有数值取最小值。
# 时间复杂度：O(n)，每个下标只被统计与比较常数次；空间复杂度：O(n)，字典最多保存 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def minimumSeconds(self, nums: List[int]) -> int:  # nums：环形数组，首尾相邻；返回最少秒数
        d = defaultdict(list)  # 字典：键是数值，值是它出现的所有下标（随枚举天然升序）
        for i, x in enumerate(nums):  # 同时拿到下标 i 与数值 x
            d[x].append(i)  # 把下标 i 记录到数值 x 对应的列表里
        ans = inf  # 答案初值用无穷大，方便后面不断取 min
        n = len(nums)  # 环形数组的长度，跨边界时用 n 补齐
        for idx in d.values():  # 逐个数值处理它的下标列表
            t = idx[0] + n - idx[-1]  # 首尾相接的环形空档：从最后一个下标绕一圈回到第一个下标
            for i, j in pairwise(idx):  # pairwise 依次给出相邻的两个下标 (i, j)
                t = max(t, j - i)  # 取最大空档：它决定这个数值把整圈同化完需要多久
            ans = min(ans, t // 2)  # 每秒空档两端各向外扩散一格，故秒数是空档的一半
        return ans  # 返回所有数值方案中的最少秒数
