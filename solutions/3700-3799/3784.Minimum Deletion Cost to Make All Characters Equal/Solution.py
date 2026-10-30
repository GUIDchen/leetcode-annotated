# 题目：3784. 使所有字符相等的最小删除代价（Minimum Deletion Cost to Make All Characters Equal）
# 核心思路：枚举最终保留下来的字符，其余字符的代价全部要删掉，代价为总代价减去该字符的代价和，对出现的每种字符取最小值。
# 复杂度：时间 O(n)，一次扫描加一次分组遍历；空间 O(1)，哈希表最多存 26 个键。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, s: str, cost: List[int]) -> int:  # 可删除任意多个字符，要求剩余串非空且字符全相同，返回最小删除总代价
        tot = 0  # 所有字符的删除代价之和
        g = defaultdict(int)  # g[c] 记录字符 c 的删除代价总和
        for c, v in zip(s, cost):  # 逐个字符累加总代价，并按字符分组累计
            tot += v  # 累加总代价
            g[c] += v  # 把该字符的代价加进对应分组
        return min(tot - x for x in g.values())  # 保留字符 x 需删掉其余字符，代价为 tot 减去该分组的和，取最小值
