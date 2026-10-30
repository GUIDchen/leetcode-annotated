# 3588. 找到最大三角形面积（Find Maximum Area of a Triangle）
# 核心思路：三角形需要一条水平（或竖直）底边，按 x 分组记录每组 y 的最小与最大值得到底边，再乘该组到最左/最右 x 的最大水平高；转置坐标再算一次取较大值。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为坐标点个数。
class Solution:  # 定义题解类
    def maxArea(self, coords: List[List[int]]) -> int:  # 求所有点能组成的最大三角形面积（返回值是面积的两倍）
        def calc() -> int:  # 按当前坐标轴方向计算一次最大面积
            mn, mx = inf, 0  # 记录最小的 x 与最大的 x
            f = {}  # f 存每列最小 y
            g = {}  # g 存每列最大 y
            for x, y in coords:  # 遍历所有坐标点
                mn = min(mn, x)  # 更新最小 x
                mx = max(mx, x)  # 更新最大 x
                if x in f:  # 该 x 已经出现过，需要比较 y
                    f[x] = min(f[x], y)  # 更新同列最小 y
                    g[x] = max(g[x], y)  # 更新同列最大 y
                else:  # 该 x 首次出现
                    f[x] = g[x] = y  # 同时初始化同列最小与最大 y
            ans = 0  # 记录本次计算的最大面积
            for x, y in f.items():  # 枚举用作竖直底边的每一列
                d = g[x] - y  # 该列上最长竖直底边的长度
                ans = max(ans, d * max(mx - x, x - mn))  # 底边乘该列到最左/最右 x 的最大水平高
            return ans  # 返回本次计算的最大面积

        ans = calc()  # 先按原始坐标轴计算一次
        for c in coords:  # 遍历所有点做坐标交换
            c[0], c[1] = c[1], c[0]  # 交换横纵坐标，等价于沿对角线转置
        ans = max(ans, calc())  # 转置后再算一次并取较大值
        return ans if ans else -1  # 面积为 0 说明无法构成三角形，返回 -1
