# 题目：1465. 切割后面积最大的蛋糕（Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts）
# 核心思路：把 0 与 h（或 w）当作虚拟切线一起排序，最大块面积等于水平最大间距与垂直最大间距之积，再对 1e9+7 取模。
# 时间复杂度：O(m log m + n log n)，瓶颈在排序；空间复杂度：O(m + n)，extend 会扩展原列表的长度。
class Solution:  # LeetCode 约定的题解类
    def maxArea(  # h、w 是蛋糕的高与宽；两个列表分别是水平、垂直方向的切线位置
        self, h: int, w: int, horizontalCuts: List[int], verticalCuts: List[int]  # 参数续行：self 之后的四个入参
    ) -> int:  # 返回最大块的面积（对 1e9+7 取模）
        horizontalCuts.extend([0, h])  # 补上上下边界，让边界也参与求间距
        verticalCuts.extend([0, w])  # 补上左右边界
        horizontalCuts.sort()  # 排序后相邻两线之差就是各水平块的高度
        verticalCuts.sort()  # 排序后相邻两线之差就是各垂直块的宽度
        x = max(b - a for a, b in pairwise(horizontalCuts))  # pairwise 依次给出相邻两元素，求最大高度
        y = max(b - a for a, b in pairwise(verticalCuts))  # 同理求最大宽度
        return (x * y) % (10**9 + 7)  # Python 大整数不会溢出，直接相乘后取模
