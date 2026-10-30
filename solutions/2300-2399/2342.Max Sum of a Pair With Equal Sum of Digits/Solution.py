# 题目：2342. 数位和相等数对的最大和（Max Sum of a Pair With Equal Sum of Digits）
# 思路：用字典 d 记录「数位和 → 该数位和下见过的最大值」；顺序扫描，先查字典里已有的最大值与 v 配对更新答案，再把 v 写入字典。
# 时间复杂度：O(n log M)，M 为元素最大值，需要逐位拆分；空间复杂度：O(k)，k 为不同数位和的个数（最多 82 种，可视为 O(1)）。
class Solution:  # LeetCode 约定的题解类
    def maximumSum(self, nums: List[int]) -> int:  # nums：输入数组；返回数位和相等数对的最大和，不存在则返回 -1
        d = defaultdict(int)  # 键为数位和，值为该数位和下出现过的最大值（defaultdict 由判题环境提供）
        ans = -1  # 不存在合法数对时的返回值就是 -1
        for v in nums:  # 顺序扫描每个元素
            x, y = 0, v  # x 存数位和，y 是待拆分的副本
            while y:  # y 为 0 说明所有数位已取完
                x += y % 10  # 取最低位数字累加到 x
                y //= 10  # 去掉最低位，继续处理高位
            if x in d:  # 用 in 判断，避免 defaultdict 因访问而插入 0 值键
                ans = max(ans, d[x] + v)  # 用字典中同数位和的最大值与当前 v 配对，尝试更新答案
            d[x] = max(d[x], v)  # 把 v 也写入字典并保留最大值；先查后写保证不会自己和自己配对
        return ans  # 返回最大和，从未配对成功时保持 -1
