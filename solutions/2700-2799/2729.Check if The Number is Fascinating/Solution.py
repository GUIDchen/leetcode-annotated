# 题目：2729. 判断一个数是否迷人（Check if The Number is Fascinating）
# 思路：把 n、2n、3n 拼成一个字符串，排序后判断是否恰好是 "123456789"。
# 时间复杂度：O(log n)（拼接长度固定为 9）；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def isFascinating(self, n: int) -> bool:  # 判断 n 是否为迷人数字
        s = str(n) + str(2 * n) + str(3 * n)  # 把 n、2n、3n 转成字符串并拼接
        return "".join(sorted(s)) == "123456789"  # 排序后判断是否恰好由 1~9 各一次组成
