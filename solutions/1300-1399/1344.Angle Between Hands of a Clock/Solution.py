# 题目：1344. 时钟指针的夹角（Angle Between Hands of a Clock）
# 思路：分别算出时针、分针相对 12 点方向的角度，作差取绝对值，再与 360 度减去该差值取较小者。
# 时间复杂度：O(1)，只有常数次算术运算；空间复杂度：O(1)，仅用常数个浮点变量。
class Solution:  # LeetCode 约定的题解类
    def angleClock(self, hour: int, minutes: int) -> float:  # hour 是小时数，minutes 是分钟数
        h = 30 * hour + 0.5 * minutes  # 时针角度：每小时 30 度，每分钟再补 0.5 度
        m = 6 * minutes  # 分针角度：每分钟 6 度
        diff = abs(h - m)  # 两针夹角的绝对差
        return min(diff, 360 - diff)  # 夹角取劣角：diff 与 360-diff 中的较小者
