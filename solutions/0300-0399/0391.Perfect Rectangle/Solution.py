# 题目：391. 完美矩形（Perfect Rectangle）
# 思路：所有小矩形面积之和须等于外包矩形面积，且四个角各只出现一次；其余顶点只出现 2 次或 4 次才说明既无重叠也无空缺。
# 时间复杂度：O(n)，只遍历一遍小矩形并对顶点计数；空间复杂度：O(n)，顶点计数表最多存 4n 项。
class Solution:  # LeetCode 约定的题解类
    def isRectangleCover(self, rectangles: List[List[int]]) -> bool:  # rectangles 每项是 [x1, y1, x2, y2]，判断它们能否不重不漏拼成一个大矩形
        area = 0  # 累加所有小矩形的面积，用于和外包矩形面积比对
        minX, minY = rectangles[0][0], rectangles[0][1]  # 外包矩形左下角，先用第一个小矩形的左下角初始化
        maxX, maxY = rectangles[0][2], rectangles[0][3]  # 外包矩形右上角，先用第一个小矩形的右上角初始化
        cnt = defaultdict(int)  # 顶点计数表：键是顶点坐标，值是被覆盖次数，缺省为 0

        for r in rectangles:  # 逐个处理每个小矩形
            area += (r[2] - r[0]) * (r[3] - r[1])  # 累加当前小矩形的面积，Python 整数不会溢出

            minX = min(minX, r[0])  # 更新外包矩形的左边界
            minY = min(minY, r[1])  # 更新外包矩形的下边界
            maxX = max(maxX, r[2])  # 更新外包矩形的右边界
            maxY = max(maxY, r[3])  # 更新外包矩形的上边界

            cnt[(r[0], r[1])] += 1  # 左下角顶点计数加一
            cnt[(r[0], r[3])] += 1  # 左上角顶点计数加一
            cnt[(r[2], r[3])] += 1  # 右上角顶点计数加一
            cnt[(r[2], r[1])] += 1  # 右下角顶点计数加一

        if (  # 先检查两个必要条件：面积相等，并且四个角落顶点各只出现一次
            area != (maxX - minX) * (maxY - minY)  # 小矩形面积之和必须等于外包矩形面积
            or cnt[(minX, minY)] != 1  # 左下角顶点必须恰好出现一次
            or cnt[(minX, maxY)] != 1  # 左上角顶点必须恰好出现一次
            or cnt[(maxX, maxY)] != 1  # 右上角顶点必须恰好出现一次
            or cnt[(maxX, minY)] != 1  # 右下角顶点必须恰好出现一次
        ):
            return False  # 必要条件不满足，一定不能完美覆盖

        del cnt[(minX, minY)], cnt[(minX, maxY)], cnt[(maxX, maxY)], cnt[(maxX, minY)]  # 删掉外包矩形的四个角落顶点，剩下的只应是内部顶点

        return all(c == 2 or c == 4 for c in cnt.values())  # 内部顶点只会被 2 个或 4 个矩形共用，否则存在重叠或空缺
