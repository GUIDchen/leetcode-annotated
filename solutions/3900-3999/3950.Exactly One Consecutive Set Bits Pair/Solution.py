# 题目：3950. 恰好一对连续置位（Exactly One Consecutive Set Bits Pair）
# 思路：从最低位往高位逐位扫描，用 pre 记住上一位；若相邻两位同时为 1 就计数，出现第二次即失败，最后要求至少出现一次。
# 复杂度：时间 O(log n)（二进制位数），空间 O(1)。
class Solution:  # LeetCode 约定的题解类
    def consecutiveSetBits(self, n: int) -> bool:  # n：待检查的正整数，判断它的二进制里是否恰好有一对相邻的 1
        pre = 0  # pre 保存上一位的值，初始按 0 处理
        vis = False  # vis 记录是否已经出现过一次「相邻两位都是 1」
        while n:  # 从最低位开始逐位扫描，n 为 0 时结束
            cur = n & 1  # cur 是当前最低位的值（0 或 1）
            if pre == cur == 1:  # 上一位与当前位同为 1，说明出现了一对相邻置位
                if vis:  # 之前已经出现过一对，说明不止一对
                    return False  # 直接返回 False
                vis = True  # 标记已经出现过一对
            pre = cur  # 当前位成为下一轮的上一位
            n = n >> 1  # 右移一位，把已处理的低位丢掉
        return vis  # 返回 vis：为 True 表示恰好一对，False 表示一对都没有
