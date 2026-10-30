# 题目：492. 构造矩形（Construct the Rectangle）
# 思路：让宽尽量接近 √area，于是宽从 floor(√area) 开始向下找第一个能整除面积的数，此时长 = area // 宽，长宽差最小。
# 时间复杂度：O(√area)，最坏从 √area 递减到 1；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def constructRectangle(self, area: int) -> List[int]:  # area：矩形面积；返回 [长, 宽]，要求 长 ≥ 宽 且两者差值尽可能小
        w = int(sqrt(area))  # 宽从 floor(√area) 开始向下找，这样长宽最接近；sqrt 来自题目环境已引入的 math
        while area % w != 0:  # 宽必须整除面积才有整数长，否则继续减 1
            w -= 1  # 宽减 1，继续往上逼近
        return [area // w, w]  # 长 = 面积 // 宽，按题目要求先长后宽返回
