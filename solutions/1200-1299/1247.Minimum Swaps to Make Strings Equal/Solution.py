# 题目：1247. 交换字符使得字符串相同（Minimum Swaps to Make Strings Equal）
# 思路：统计 x/y 与 y/x 两类不匹配位置，同类两两用一次交换解决，剩余的异类各一个时用两次交换解决。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用两个计数器。
class Solution:  # LeetCode 约定的题解类
    def minimumSwap(self, s1: str, s2: str) -> int:  # 求把 s1 变成 s2 所需的最少交换次数（交换可跨两个字符串）
        xy = yx = 0  # xy：s1 为 x、s2 为 y 的位置数；yx：s1 为 y、s2 为 x 的位置数
        for a, b in zip(s1, s2):  # 同步遍历两个字符串的每一位
            xy += a < b  # 字符 'x' 小于 'y'，为真则这一位是 x/y 型不匹配，布尔值当 0/1 累加
            yx += a > b  # 为真则这一位是 y/x 型不匹配
        if (xy + yx) % 2:  # 不匹配位置总数是奇数，两类无法配对
            return -1  # 无解，返回 -1
        return xy // 2 + yx // 2 + xy % 2 + yx % 2  # 同类两两各一次交换；两类各剩 1 个时再用两次交换解决这对异类
