# 题目：2184. 建造坚实的砖墙的方法数（Number of Ways to Build Sturdy Brick Wall）
# 思路：DFS 枚举所有宽度恰为 width 的单行排列，用双指针筛出没有同列砖缝的兼容行对建图，再按高度做 DP 累加方案数。
# 时间复杂度：O(2^width + n^2 * width + height * n^2)，n 为单行合法排列数；空间复杂度：O(n^2 + height * n)。
class Solution:  # LeetCode 约定的题解类
    def buildWall(self, height: int, width: int, bricks: List[int]) -> int:  # height：高度；width：宽度；bricks：砖块长度集合
        def dfs(v):  # 内部 DFS：v 表示当前这一行已经铺好的长度
            if v > width:  # 超出墙宽，方案非法
                return  # 直接回溯
            if v == width:  # 恰好铺满一整行
                s.append(t[:])  # 复制当前行，记录为一个合法排列
                return  # 结束本次递归
            for x in bricks:  # 尝试每一块可用的砖
                t.append(x)  # 把这块砖加入当前行
                dfs(v + x)  # 递归继续往右铺
                t.pop()  # 回溯：撤销这块砖，尝试下一个长度

        def check(a, b):  # 判断排列 a、b 是否不存在同一列的砖缝（可上下相邻）
            s1, s2 = a[0], b[0]  # s1、s2 是 a、b 中当前砖块的右端位置（前缀和）
            i = j = 1  # i、j 是 a、b 中下一块砖的下标
            while i < len(a) and j < len(b):  # 两行都还没走到最后一块砖
                if s1 == s2:  # 砖缝落在同一列，冲突
                    return False  # 不能相邻
                if s1 < s2:  # a 的砖缝更靠左
                    s1 += a[i]  # 推进 a 的右端到下一块砖
                    i += 1  # a 的下标后移
                else:  # b 的砖缝更靠左
                    s2 += b[j]  # 推进 b 的右端到下一块砖
                    j += 1  # b 的下标后移
            return True  # 中途没有出现同列砖缝，兼容

        mod = 10**9 + 7  # 取模常量，防止方案数过大
        s = []  # 保存所有宽度恰为 width 的单行砖块排列
        t = []  # DFS 过程中正在拼的当前行（存砖块长度）
        dfs(0)  # 从长度 0 开始枚举全部单行排列
        g = defaultdict(list)  # 兼容图：g[i] 存所有可与第 i 种排列上下相邻的排列下标
        n = len(s)  # 单行合法排列的总数
        for i in range(n):  # 枚举每一对排列（含自身）
            if check(s[i], s[i]):  # 自己与自己比较，判断该行内部是否存在同列砖缝
                g[i].append(i)  # 自身兼容，说明同一排列可以上下堆叠
            for j in range(i + 1, n):  # 只枚举 j > i，避免重复
                if check(s[i], s[j]):  # 两种排列没有公共砖缝，可以上下相邻
                    g[i].append(j)  # 记录 i 的下方可以是 j
                    g[j].append(i)  # 记录 j 的下方可以是 i（双向）
        dp = [[0] * n for _ in range(height)]  # dp[i][j]：搭到第 i 行、该行用第 j 种排列的方案数
        for j in range(n):  # 初始化第一行
            dp[0][j] = 1  # 第一行用任意一种排列都算 1 种方案
        for i in range(1, height):  # 逐行向上递推
            for j in range(n):  # 枚举当前行（第 i 行）使用的排列
                for k in g[j]:  # 枚举与它兼容的上一行（第 i-1 行）排列
                    dp[i][j] += dp[i - 1][k]  # 累加上一行的方案数
                    dp[i][j] %= mod  # 随时取模，避免溢出
        return sum(dp[-1]) % mod  # 最后一行各种排列的方案数求和再取模，即为答案
