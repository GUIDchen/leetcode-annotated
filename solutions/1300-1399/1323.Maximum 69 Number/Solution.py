# 题目：1323. 6 和 9 组成的最大数字（Maximum 69 Number）
# 思路：把数字转成字符串，只替换第一个 6 为 9（位权最高，收益最大），再转回整数。
# 时间复杂度：O(log num)，即十进制位数；空间复杂度：O(log num)，字符串长度。
class Solution:  # LeetCode 约定的题解类
    def maximum69Number(self, num: int) -> int:  # 求把 num 中最多一位的 6 翻成 9 后得到的最大数字
        return int(str(num).replace("6", "9", 1))  # replace 第三个参数 1 表示只替换第一个 6，再转回整数
