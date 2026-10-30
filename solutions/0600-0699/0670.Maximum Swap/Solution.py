# 题目：670. 最大交换（Maximum Swap）
# 思路：先倒序预处理后缀最大值下标 d[i]；再从左往右找第一个存在更大后缀字符的位置 i，与 d[i] 交换一次即为最大值。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，字符列表与后缀最值下标数组。
class Solution:  # LeetCode 约定的题解类
    def maximumSwap(self, num: int) -> int:  # 最多交换一次数位，返回能得到的最大数
        s = list(str(num))  # 转成字符列表，方便按下标交换
        n = len(s)  # 位数
        d = list(range(n))  # d[i] 表示 s[i:] 中最大字符的下标，默认每个位置就是自己
        for i in range(n - 2, -1, -1):  # 从右往左递推后缀最大值下标
            if s[i] <= s[d[i + 1]]:  # 后缀最大字符不小于当前字符
                d[i] = d[i + 1]  # 继承后一位的下标（相等时取靠后的，交换后数值更大）
        for i, j in enumerate(d):  # 同时枚举下标 i 与其后缀最大字符下标 j
            if s[i] < s[j]:  # 后面存在更大的字符，交换能让数变大
                s[i], s[j] = s[j], s[i]  # 只交换这一次
                break  # 交换后一定是最大值，结束循环
        return int(''.join(s))  # 拼回字符串再转整数返回
