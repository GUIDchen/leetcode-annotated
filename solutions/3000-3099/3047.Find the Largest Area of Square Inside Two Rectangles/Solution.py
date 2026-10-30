# 题目：3047. 求交集区域内的最大正方形面积（Find the Largest Area of Square Inside Two Rectangles）
# 核心思路：用 combinations 枚举每一对矩形，算出交集宽高，正方形边长取两者较小值，累计最大面积。
# 时间复杂度：O(n^2)，两两枚举矩形；空间复杂度：O(1)，只用常数个中间变量。
class Solution:
    def largestSquareArea(  # bottomLeft、topRight：每个矩形的左下角与右上角坐标，返回任意两个矩形交集内最大正方形的面积
        self, bottomLeft: List[List[int]], topRight: List[List[int]]  # 继续声明入参：bottomLeft 是左下角列表，topRight 是右上角列表
    ) -> int:  # -> int：返回最大正方形面积
        ans = 0  # ans：目前找到的最大正方形面积
        for ((x1, y1), (x2, y2)), ((x3, y3), (x4, y4)) in combinations(  # combinations 取任意两个矩形；每个元素用 zip 预先配成（左下角, 右上角）
            zip(bottomLeft, topRight), 2  # zip(bottomLeft, topRight) 把同一个矩形的两个角配对，2 表示每次取两个矩形
        ):  # 解包出的 (x1, y1)、(x2, y2) 是矩形一的两个角，(x3, y3)、(x4, y4) 是矩形二的两个角
            w = min(x2, x4) - max(x1, x3)  # 交集宽度：两个右边界取小、两个左边界取大再相减；为负说明不相交
            h = min(y2, y4) - max(y1, y3)  # 交集高度：同理用上下边界计算
            e = min(w, h)  # 正方形边长受宽高共同限制，取两者较小值
            if e > 0:  # 边长为正才说明两个矩形确实有交集面积
                ans = max(ans, e * e)  # 用当前边长平方更新最大面积
        return ans  # 返回找到的最大正方形面积，没有任何交集时为 0
