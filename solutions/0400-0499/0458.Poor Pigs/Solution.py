# 题目：458. 可怜的小猪（Poor Pigs）
# 思路：每头猪有「测试轮数+1」种状态，n 头猪可编码 base^n 个桶；倍增 base 直到不少于 buckets，倍增次数就是答案。
# 时间复杂度：O(log_base buckets)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def poorPigs(self, buckets: int, minutesToDie: int, minutesToTest: int) -> int:  # buckets 为桶数、minutesToDie 为毒发时间、minutesToTest 为总测试时间
        base = minutesToTest // minutesToDie + 1  # base = 每头猪的状态数 = 可测试轮数 + 1（多出的 1 表示始终不死）
        res, p = 0, 1  # res 为猪数，p 为当前猪数能区分的桶数上限（从 1 开始倍增）
        while p < buckets:  # 还不足以区分所有桶
            p *= base  # 再多一头猪，可区分的桶数乘以 base
            res += 1  # 猪的数量加一
        return res  # 返回最少猪数
