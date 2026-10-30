# 3906. 统计网格路径中好整数的数目（Count Good Integers on a Grid Path）
# 思路：先由 directions 求出 4x4 网格路径上哪些数位受「不小于前一位」的约束，再用数位 DP 统计 [0, x] 内满足约束的 16 位数，最后用前缀和相减得到 [l, r] 的答案。
# 复杂度：时间复杂度 O(16*10*10)，记忆化后每个状态只计算一次；空间复杂度 O(16*10)。
class Solution:  # LeetCode 约定的题解类
    def countGoodIntegersOnPath(self, l: int, r: int, directions: str) -> int:  # 统计 [l, r] 中满足路径约束的整数个数，directions 给出路径
        key = [False] * 16  # key[p] 表示路径第 p 个数位是否被约束成「不小于前一位」
        row, col = 0, 0  # 当前路径在 4x4 网格中的位置
        key[0] = True  # 起点（第 0 位）有约束
        for c in directions:  # 沿 directions 逐位前进
            if c == "D":  # 向下走：行号加一
                row += 1  # 行坐标前移
            else:  # 否则向右走：列号加一
                col += 1  # 列坐标前移
            key[row * 4 + col] = True  # 路径经过的数位被标记为有约束

        s = ""  # 当前上界 x 补零到 16 位后的字符串

        @cache  # 记忆化：同一个 (pos, last, lim) 只计算一次
        def dfs(pos, last, lim):  # pos：当前数位；last：上一位数字；lim：是否紧贴上界
            if pos == 16:  # 16 位全部填完，得到一个合法整数
                return 1  # 计数加一

            res = 0  # 当前状态的方案数
            start = last if key[pos] else 0  # 有约束的数位必须不小于上一位
            end = int(s[pos]) if lim else 9  # 紧贴上界时只能取到上界当前位的数字

            for i in range(start, end + 1):  # 枚举当前位可填的数字
                res += dfs(pos + 1, i if key[pos] else last, lim and (i == end))  # 递归下一位；只有本行也贴上界才继续受限

            return res  # 返回当前状态的方案数

        def calc(x):  # 计算 [0, x] 内的合法整数个数
            nonlocal s  # 需要修改外层保存的上界字符串
            if x < 0:  # 负数没有合法整数
                return 0  # 返回 0
            s = str(x).zfill(16)  # 左侧补零到 16 位，低位对齐数位 DP
            dfs.cache_clear()  # 每个上界都要清空记忆化缓存
            return dfs(0, 0, True)  # 从最高位开始，初始紧贴上界

        return calc(r) - calc(l - 1)  # 前缀和相减得到 [l, r] 的答案
