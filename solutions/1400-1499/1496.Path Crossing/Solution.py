# 题目：1496. 判断路径是否相交（Path Crossing）
# 思路：按字符移动坐标，用集合记录走过的点，一旦某个点重复出现就返回 True。
# 时间复杂度：O(n)，n 为路径长度；空间复杂度：O(n)，集合存坐标。
class Solution:  # LeetCode 约定的题解类
    def isPathCrossing(self, path: str) -> bool:  # 返回路径是否经过同一个坐标两次
        i = j = 0  # 当前坐标，起点为 (0,0)
        vis = {(0, 0)}  # 记录走过的点，起点先放进去
        for c in path:  # 逐字符模拟移动
            match c:  # Python 3.10 的结构化模式匹配，按方向分支
                case 'N':  # 向北：行坐标减一
                    i -= 1  # 更新行坐标
                case 'S':  # 向南：行坐标加一
                    i += 1  # 更新行坐标
                case 'E':  # 向东：列坐标加一
                    j += 1  # 更新列坐标
                case 'W':  # 向西：列坐标减一
                    j -= 1  # 更新列坐标
            if (i, j) in vis:  # 当前点以前走过
                return True  # 路径相交
            vis.add((i, j))  # 记录当前点
        return False  # 遍历完没有重复，返回 False
