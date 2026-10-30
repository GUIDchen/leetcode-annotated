# 题目：3085. 成为 K 特殊字符串需要删除的最少字符数（Minimum Deletions to Make String K-Special）
# 思路：用 Counter 统计各字符频次，枚举保留下来的最小频次 v；低于 v 的字符整类删除，高于 v + k 的削到 v + k，取最小总删除数。
# 时间复杂度：O(n·26)，n 为字符串长度，枚举 n+1 个下界各扫一遍频次；空间复杂度：O(1)，只含至多 26 个字符的频次。
class Solution:  # LeetCode 约定的题解类
    def minimumDeletions(self, word: str, k: int) -> int:  # word 是输入字符串，k 是允许的字符频次最大差值
        def f(v: int) -> int:  # 内层函数 f(v)：以 v 为保留下来的最小频次，返回该方案的总删除数
            ans = 0  # 本次枚举的删除总数
            for x in nums:  # 逐个检查每种字符的频次 x
                if x < v:  # 频次低于下界 v，这类字符无法保留
                    ans += x  # 整类删除，代价为它的全部出现次数
                elif x > v + k:  # 频次高于上界 v + k，只能保留 v + k 个
                    ans += x - v - k  # 删掉超出的 x - (v + k) 个字符
            return ans  # 返回该下界下的删除总数

        # 空行之后是主逻辑：先统计频次，再枚举所有下界
        nums = Counter(word).values()  # 统计每个字符的出现次数；.values() 只要频次、不含字符名
        return min(f(v) for v in range(len(word) + 1))  # 枚举 0..len(word) 每个下界 v，取所有 f(v) 中的最小值
