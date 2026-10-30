# 题目：335. 路径交叉（Self Crossing）
# 核心思路：路径按「上、左、下、右」循环前进，把新边与前几条边的相交归纳成三种情况，逐条检查。
# 时间复杂度：O(n)，一趟扫描；空间复杂度：O(1)，只复用传入的列表（未额外复制）。
class Solution:  # LeetCode 约定的题解类
    def isSelfCrossing(self, distance: List[int]) -> bool:  # distance 是每步长度，方向依次为上、左、下、右；返回是否自交
        d = distance  # 给距离列表起个短名，后面按下标读取更简洁
        for i in range(3, len(d)):  # 从下标 3（第 4 条边）开始检查，至少 4 条边才可能相交
            if d[i] >= d[i - 2] and d[i - 1] <= d[i - 3]:  # 情况一：新边长度覆盖对边第 i-2 条，且相邻边没有越界，必然相交
                return True  # 发现相交，返回 True
            if i >= 4 and d[i - 1] == d[i - 3] and d[i] + d[i - 4] >= d[i - 2]:  # 情况二：新边与第 i-3 条边共线相撞
                return True  # 满足情况二，返回 True
            if (  # 情况三条件较多，用括号折行书写以保持可读性
                i >= 5  # 至少 6 条边才可能出现这种绕圈的相交
                and d[i - 2] >= d[i - 4]  # 内侧第 i-4 条边足够短，才留出可穿越的通道
                and d[i - 1] <= d[i - 3]  # 相邻边第 i-1 条没有先越出第 i-3 条边
                and d[i] >= d[i - 2] - d[i - 4]  # 新边长度足够长，能一路穿到内侧
                and d[i - 1] + d[i - 5] >= d[i - 3]  # 累计的距离已经越过第 i-3 条边所在的位置
            ):  # 条件列表结束
                return True  # 满足情况三，返回 True
        return False  # 全部检查完仍未相交，返回 False
