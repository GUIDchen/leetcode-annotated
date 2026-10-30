# 题目：868. 二进制间距（Binary Gap）
# 思路：从低位到高位扫描 n 的二进制位，记录上一个 1 的位置 pre 与当前位下标 cur，遇到 1 就用 cur-pre 更新答案。
# 时间复杂度：O(log n)，即 n 的二进制位数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def binaryGap(self, n: int) -> int:  # 返回 n 的二进制表示中相邻两个 1 之间的最大距离
        ans = 0  # ans 记录最大间距，初值 0 表示目前还没有间距
        pre, cur = inf, 0  # pre 是上一个 1 所在位的下标，inf 作哨兵；cur 是当前位下标
        while n:  # 不断检查 n 的最低位，直到 n 变成 0
            if n & 1:  # 最低位是 1 时才需要统计间距
                ans = max(ans, cur - pre)  # 当前位置减上一个 1 的位置即间距，取最大值；第一个 1 算出负值，被初值 0 压住
                pre = cur  # 把「上一个 1」更新为当前位置
            cur += 1  # 检查完一位后，当前位下标后移
            n >>= 1  # n 右移一位，下一轮检查新的最低位
        return ans  # 返回最大间距；不足两个 1 时返回 0
