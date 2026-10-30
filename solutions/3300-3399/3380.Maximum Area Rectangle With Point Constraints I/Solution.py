# 题目：3380. 用点构造面积最大的矩形 I（Maximum Area Rectangle With Point Constraints I）
# 思路：n 很小，枚举任意两点作为矩形的两个对角顶点并规整成 (x3,y3)-(x4,y4)；check 扫描全部点，要求矩形内无点、四条边上恰好只有 4 个给定点（四个角），满足则更新最大面积。
# 时间复杂度：O(n^3)，枚举点对 O(n^2) 乘以 check 的 O(n)；空间复杂度：O(1)，只用常数个临时变量。
class Solution:  # LeetCode 约定的题解类
    def maxRectangleArea(self, points: List[List[int]]) -> int:  # points：所有给定点；矩形只能以这些点为四角，且内部与边上不能有多余的点
        def check(x1: int, y1: int, x2: int, y2: int) -> bool:  # check 是内部函数：判断以 (x1,y1)、(x2,y2) 为左下/右上角的矩形是否合法
            cnt = 0  # 计数器：统计落在矩形四个角上的点数
            for x, y in points:  # 遍历所有给定点
                if x < x1 or x > x2 or y < y1 or y > y2:  # 点落在矩形外，与本题无关
                    continue  # 直接跳过
                if (x == x1 or x == x2) and (y == y1 or y == y2):  # 点正好落在矩形的某个角上
                    cnt += 1  # 合法角点，计数加一
                    continue  # 跳过，继续看下一个点
                return False  # 既在矩形内又不在角上：内部或边上有别的点，矩形不合法
            return cnt == 4  # 恰好 4 个角点且没有其他点，说明构成合法矩形

        ans = -1  # 答案初始为 -1，表示暂时找不到合法矩形
        for i, (x1, y1) in enumerate(points):  # 枚举第一个对角顶点 i 及其坐标
            for x2, y2 in points[:i]:  # 枚举另一个对角顶点 j（只取 i 之前的点，避免重复枚举点对）
                x3, y3 = min(x1, x2), min(y1, y2)  # 两个点顺序可能颠倒，统一取较小的 x、y 作为左下角
                x4, y4 = max(x1, x2), max(y1, y2)  # 统一取较大的 x、y 作为右上角
                if check(x3, y3, x4, y4):  # 用规整后的边界检查矩形是否合法
                    ans = max(ans, (x4 - x3) * (y4 - y3))  # 合法就用「宽 × 高」更新最大面积
        return ans  # 返回最大面积（找不到合法矩形时为 -1）
