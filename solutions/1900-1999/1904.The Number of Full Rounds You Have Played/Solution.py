# 题目：1904. 你完成的完整对局数（The Number of Full Rounds You Have Played）
# 思路：把时间换算成分钟数，跨天时给结束时间加一天；完整对局数 = 结束前的整刻数 - 开始后的第一个整刻数（向上取整到 15 的倍数）。
# 时间复杂度：O(1)，只有常数次运算；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def numberOfRounds(self, loginTime: str, logoutTime: str) -> int:  # loginTime / logoutTime：形如 HH:MM 的登录与登出时间
        def f(s: str) -> int:  # 内部函数：把 HH:MM 换算成从 00:00 起的分钟数
            return int(s[:2]) * 60 + int(s[3:])  # 前两位是小时，第 3 位起是分钟

        # 先把登录、登出时刻都换算成分钟数，后续比较与取整都基于分钟数
        a, b = f(loginTime), f(logoutTime)  # 分别得到登录、登出的分钟数
        if a > b:  # 登录晚于登出，说明这次登录跨过了午夜
            b += 1440  # 给登出时间加一天，让时间区间保持递增
        a, b = (a + 14) // 15, b // 15  # a 向上取整到下一个 15 分钟刻度，b 向下取整到整刻，得到可完整进行的对局数
        return max(0, b - a)  # 两者相减即完整对局数，与 0 取大防止区间太短时出现负数
