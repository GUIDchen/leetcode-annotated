# 题目：836. 矩形重叠（Rectangle Overlap）
# 思路：两个轴对齐矩形相交，当且仅当它们在 x 方向和 y 方向上的投影都真正重叠；把四个「分离」条件整体取反即可。
# 时间复杂度：O(1)，只做常数次比较；空间复杂度：O(1)，只用到几个临时变量。
class Solution:  # LeetCode 约定的题解类
    def isRectangleOverlap(self, rec1: List[int], rec2: List[int]) -> bool:  # rec1、rec2 都按 [x1,y1,x2,y2] 给出矩形的左下角与右上角
        x1, y1, x2, y2 = rec1  # 解包第一个矩形的四个坐标
        x3, y3, x4, y4 = rec2  # 解包第二个矩形的四个坐标
        return not (y3 >= y2 or y4 <= y1 or x3 >= x2 or x4 <= x1)  # 四个分离条件任一成立即不重叠，取反后即为「相交」
