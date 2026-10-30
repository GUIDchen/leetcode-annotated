# 题目：1773. 统计匹配检索规则的物品数量（Count Items Matching a Rule）
# 思路：规则键只有 type/color/name 三种，先用首字母确定列下标，再用生成器求和统计该列等于规则值的物品数。
# 时间复杂度：O(n·L)，n 为物品数、L 为字符串比较代价；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def countMatches(self, items: List[List[str]], ruleKey: str, ruleValue: str) -> int:  # items：物品三元组列表；ruleKey/ruleValue：规则键与规则值
        i = 0 if ruleKey[0] == 't' else (1 if ruleKey[0] == 'c' else 2)  # 用规则键首字母确定列号：t 对应 type 列 0，c 对应 color 列 1，否则 name 列 2
        return sum(v[i] == ruleValue for v in items)  # 统计第 i 列等于规则值的物品个数
