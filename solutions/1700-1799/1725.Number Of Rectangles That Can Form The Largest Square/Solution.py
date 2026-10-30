# 题目：1725. 可以形成最大正方形的矩形数目（Number Of Rectangles That Can Form The Largest Square）
# 思路：正方形边长取矩形长宽的较小值；遍历时维护当前最大边长 mx 与其出现次数 ans。
# 时间复杂度：O(n)，每个矩形只遍历一次；空间复杂度：O(1)，只用了两个整型变量。
class Solution:  # LeetCode 约定的题解类
    def countGoodRectangles(self, rectangles: List[List[int]]) -> int:  # rectangles 中每个二元组是一条矩形的长与宽
        ans = mx = 0  # ans 记录最大边长出现的次数，mx 记录目前遇到的最大正方形边长
        for l, w in rectangles:  # 逐个矩形取出长 l 与宽 w
            x = min(l, w)  # 该矩形能切出的最大正方形边长是长宽中的较小值
            if mx < x:  # 出现了比当前记录更大的正方形
                ans = 1  # 旧的最大值失效，计数重置为 1
                mx = x  # 更新最大边长
            elif mx == x:  # 与当前最大边长相等，说明这条矩形也能形成最大正方形
                ans += 1  # 计数加一
        return ans  # 返回能形成最大正方形的矩形数目
