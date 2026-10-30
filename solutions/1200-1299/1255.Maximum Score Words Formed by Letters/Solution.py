# 题目：1255. 得分最高的单词集合（Maximum Score Words Formed by Letters）
# 思路：单词最多 14 个，直接枚举所有子集（用二进制位表示选不选）；对每个子集统计字母用量，若不超过可用字母就按 score 累计得分，取最大值。
# 时间复杂度：O(2^n · n · L)，L 为单词平均长度；空间复杂度：O(1)，只用两个不超过 26 项的计数器。
class Solution:  # LeetCode 约定的题解类
    def maxScoreWords(  # words：候选单词；letters：可用字母（每个只能用一次）；score：26 个字母各自的得分
        # 参数换行书写，仍是同一个方法的签名（续行由括号维持）
        self, words: List[str], letters: List[str], score: List[int]  # 形参：候选单词、可用字母、26 个字母的分值表
    ) -> int:  # 返回能拿到的最高分
        cnt = Counter(letters)  # 用计数器统计手里每个字母的可用次数
        n = len(words)  # n 是单词个数，决定了子集枚举的范围
        ans = 0  # ans 记录所有可行子集中的最高得分
        for i in range(1 << n):  # 用 n 位二进制数 i 枚举所有子集：第 j 位为 1 表示选第 j 个单词
            cur = Counter(''.join([words[j] for j in range(n) if i >> j & 1]))  # 把选中单词拼成一串再计数；i >> j & 1 取出第 j 位判断该单词是否入选
            if all(v <= cnt[c] for c, v in cur.items()):  # 逐个字母核对用量有没有超出手中库存，全都够用才继续算分
                t = sum(v * score[ord(c) - ord('a')] for c, v in cur.items())  # 该字母个数 × 对应分值后求和，ord(c) - ord('a') 把字母映射成 0~25 的下标
                ans = max(ans, t)  # 用更高分更新答案
        return ans  # 返回所有可行子集中的最高得分
