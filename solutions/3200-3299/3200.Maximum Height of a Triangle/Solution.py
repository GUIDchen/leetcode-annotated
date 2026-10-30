# 3200. 三角形的最大高度（Maximum Height of a Triangle）
# 核心思路：第 i 层需要 i 个同色球且颜色逐层交替；分别假设底层为红色或蓝色，按层号消耗对应颜色，取两种方案的最大高度。
# 复杂度：时间 O(√(red+blue))，空间 O(1)

class Solution:  # 定义题解类
    def maxHeightOfTriangle(self, red: int, blue: int) -> int:  # 返回用红、蓝球交替堆叠能形成的最大三角形高度
        ans = 0  # 记录最大高度
        for k in range(2):  # 枚举底层颜色：0 表示红球、1 表示蓝球
            c = [red, blue]  # 本轮可用的红、蓝球数
            i, j = 1, k  # i 为待放的层号，j 为该层使用的颜色
            while i <= c[j]:  # 当前颜色的球数够放第 i 层时继续
                c[j] -= i  # 消耗 i 个该颜色的球
                j ^= 1  # 颜色交替，下一层换另一种颜色
                ans = max(ans, i)  # 更新最大高度
                i += 1  # 进入下一层
        return ans  # 返回最大高度
