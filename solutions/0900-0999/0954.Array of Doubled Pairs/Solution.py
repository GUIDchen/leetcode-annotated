# 题目：954. 二倍数对数组（Array of Doubled Pairs）
# 思路：Counter 统计频次，按绝对值从小到大遍历不同数值，检查 2x 的数量是否够与 x 配对，并就地扣减。
# 时间复杂度：O(n + m log m)，m 为不同数值个数；空间复杂度：O(m)，计数表与排序结果都只占 m 个槽位。
class Solution:  # LeetCode 约定的题解类
    def canReorderDoubled(self, arr: List[int]) -> bool:  # arr 是输入整数数组，返回它能否重排成两两二倍的关系
        freq = Counter(arr)  # Counter 统计每个数值出现次数：键是数值，值是次数
        if freq[0] & 1:  # 0 只能与 0 配对，0 的个数是奇数时必然剩下一个
            return False  # 存在落单的 0，直接返回 False
        for x in sorted(freq, key=abs):  # 按绝对值从小到大处理每个不同的数值
            if freq[x << 1] < freq[x]:  # x << 1 就是 2x；不够配对的 2x 说明这个 x 无法被消化
                return False  # 配对失败，返回 False
            freq[x << 1] -= freq[x]  # 扣掉与 x 配对的那些 2x，剩余次数留给后面更大的数值
        return True  # 全部数值都配对成功，返回 True
