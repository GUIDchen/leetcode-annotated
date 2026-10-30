# 4071. 拨号的最少旋转次数 II（Minimum Rotations to Dial a Number II）
# 核心思路：先求相邻数字距离之和 total，再枚举反转后缀的起点 k：k = 0 时整串反转，k >= 1 时去掉被跳过的那条边、改为 pre 直接连到末位数字。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # 题解类
    def minRotations(self, n: int, s: str) -> int:  # 允许至多反转一次某个后缀，返回拨号的最少旋转总次数
        def dist(a: str, b: str) -> int:  # 圆盘上两个数字字符之间的最少旋转次数
            d = abs(ord(a) - ord(b))  # 两个数字字符的编码差
            return min(d, 10 - d)  # 顺时针、逆时针取较小值

        total = sum(dist(a, b) for a, b in pairwise(s))  # 原串相邻数字距离之和（反转后缀不改变后缀内部的距离之和）

        first = s[0]  # 首位数字
        last = s[-1]  # 末位数字
        to_first = dist("0", first)  # 指针 0 到首位的距离，作为反转后缀（k >= 1）时的起步代价
        ans = total + dist("0", last)  # k = 0 即反转整个串：0 -> last -> ... -> first，代价为 total 加上 0 到 last 的距离

        for pre, cur in pairwise(s):  # 枚举反转后缀的起点 cur，pre 为其前一个数字
            ans = min(ans, total - dist(pre, cur) + to_first + dist(pre, last))  # 去掉边 (pre, cur)，改为 0 -> pre -> last 衔接，得到该方案的代价

        return ans  # 返回所有方案中的最小旋转总次数
