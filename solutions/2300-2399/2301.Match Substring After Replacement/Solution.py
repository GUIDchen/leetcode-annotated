# 题目：2301. 替换字符后匹配（Match Substring After Replacement）
# 思路：用 defaultdict(set) 记录「原字符 到 可替换字符集合」，枚举每个起点，用 all 检查整段能否逐位匹配。
# 时间复杂度：O(m * n)，枚举 m 个起点、每次最多比较 n 位；空间复杂度：O(k)，k 为替换规则条数。
class Solution:  # LeetCode 约定的题解类
    def matchReplacement(self, s: str, sub: str, mappings: List[List[str]]) -> bool:  # s：主串；sub：待匹配子串；mappings：替换规则列表
        d = defaultdict(set)  # 映射表：访问不存在的键时自动创建空集合，省去判空
        for a, b in mappings:  # 逐条读入规则 a 到 b
            d[a].add(b)  # 记录 a 可以替换成 b
        for i in range(len(s) - len(sub) + 1):  # 枚举所有可能容纳 sub 的起点
            if all(a == b or a in d[b] for a, b in zip(s[i : i + len(sub)], sub)):  # 逐位检查：字符相等，或者 b 能替换成 a
                return True  # 整段匹配成功
        return False  # 所有起点都失败
