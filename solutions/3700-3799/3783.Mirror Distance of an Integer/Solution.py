# 题目：3783. 整数的镜像距离（Mirror Distance of an Integer）
# 核心思路：把 n 转成字符串后切片逆序，再转回整数得到 reverse(n)，最后返回 abs(n - reverse(n))。
# 复杂度：时间 O(log n)，即 n 的十进制位数；空间 O(log n)，用于存放逆序后的字符串。
class Solution:  # LeetCode 约定的题解类
    def mirrorDistance(self, n: int) -> int:  # 返回 n 与其各位数字逆序后所得整数之差的绝对值
        return abs(n - int(str(n)[::-1]))  # str(n)[::-1] 完成数字逆序，再转回 int 并与 n 相减取绝对值
