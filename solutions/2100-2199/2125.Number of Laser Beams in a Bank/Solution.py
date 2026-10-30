# 题目：2125. 银行中的激光束数量（Number of Laser Beams in a Bank）
# 核心思路：逐行统计 '1' 的个数，只有非空行才与上一个非空行相乘累加，空行跳过不断开逻辑。
# 时间复杂度：O(m·n)，每格只被 count 扫一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfBeams(self, bank: List[str]) -> int:  # bank 每行是只含 '0'/'1' 的字符串；返回所有激光束的条数
        ans = pre = 0  # ans 累计光束总数；pre 是上一个非空行的 '1' 个数，初始同时赋 0
        for row in bank:  # 自上而下遍历每一行
            if (cur := row.count("1")) > 0:  # 海象运算符：先数出本行 '1' 的个数存进 cur，再判断是否非空
                ans += pre * cur  # 上一非空行每个 '1' 与本行每个 '1' 两两配对，贡献 pre × cur 条光束
                pre = cur  # 本行成为下一次配对时的「上一个非空行」
        return ans  # 返回激光束总条数
