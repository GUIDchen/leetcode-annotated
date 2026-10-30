# 题目：1222. 可以攻击国王的皇后（Queens That Can Attack the King）
# 思路：从国王出发沿 8 个方向逐格射线扫描，每个方向上遇到的第一个皇后才能攻击国王，收集后跳过该方向。
# 时间复杂度：O(q + 8*8)，q 为皇后个数，棋盘固定 8x8；空间复杂度：O(1)，集合与答案规模受 8x8 限制。
class Solution:  # LeetCode 约定的题解类
    def queensAttacktheKing(  # queens：皇后坐标列表；king：国王坐标；返回能攻击国王的皇后坐标
        self, queens: List[List[int]], king: List[int]  # self 是实例本身；queens 与 king 分别带类型标注（参数换行书写）
    ) -> List[List[int]]:  # 返回值类型：坐标列表
        n = 8  # 国际象棋棋盘固定是 8x8
        s = {(i, j) for i, j in queens}  # 用集合保存皇后坐标，查询某个格子是否有皇后只需 O(1)
        ans = []  # 收集所有能攻击国王的皇后坐标
        for a in range(-1, 2):  # 行方向偏移：-1、0、1
            for b in range(-1, 2):  # 列方向偏移：-1、0、1，组合起来共 8 个方向
                if a or b:  # 跳过 (0,0)，那不是方向而是原地
                    x, y = king  # 从国王所在位置开始沿该方向扫描
                    while 0 <= x + a < n and 0 <= y + b < n:  # 下一步仍在棋盘内才继续前进
                        x, y = x + a, y + b  # 真正沿该方向前进一格
                        if (x, y) in s:  # 该方向上遇到的第一个皇后
                            ans.append([x, y])  # 它能攻击国王，加入答案
                            break  # 更远的皇后被它挡住，该方向不用再看
        return ans  # 返回答案，顺序与方向枚举顺序一致
