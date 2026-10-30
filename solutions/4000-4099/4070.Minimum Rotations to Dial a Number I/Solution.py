# 4070. 拨号的最少旋转次数 I（Minimum Rotations to Dial a Number I）
# 核心思路：指针从 0 出发按顺序拨号，每一步取圆盘上顺时针与逆时针旋转次数的较小值累加。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # 题解类
    def minRotations(self, s: str) -> int:  # 按顺序拨出字符串 s 的每一位数字，返回最少旋转总次数
        ans = pre = 0  # ans 累计最少旋转次数；pre 是指针当前所指的数字（初始 0）
        for cur in map(int, s):  # 逐位把字符转成数字并拨号
            diff = abs(cur - pre)  # 两个数字在圆盘上的直线距离
            ans += min(diff, 10 - diff)  # 顺时针、逆时针两个方向取较小值累加
            pre = cur  # 指针移到当前数字，作为下一次拨号的起点
        return ans  # 返回拨完全部数字的最少旋转次数
