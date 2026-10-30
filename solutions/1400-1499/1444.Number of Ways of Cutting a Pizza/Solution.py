# 题目：1444. 切披萨的方案数（Number of Ways of Cutting a Pizza）
# 思路：二维前缀和 O(1) 判断区域是否有苹果，再用 @cache 记忆化搜索剩余块的切割方案数。
# 时间复杂度：O(k·m·n·(m+n))；空间复杂度：O(m·n·k)。
class Solution:  # LeetCode 约定的题解类
    def ways(self, pizza: List[str], k: int) -> int:  # pizza 是每行一个字符串的披萨，k 是要切成的块数
        @cache  # @cache 自动记忆化：相同参数只算一次
        def dfs(i: int, j: int, k: int) -> int:  # i,j 是当前块左上角，k 是还要切的刀数
            if k == 0:  # 不能再切，剩下的整块必须自带苹果
                return int(s[m][n] - s[i][n] - s[m][j] + s[i][j] > 0)  # 用前缀和求剩余区域苹果数，大于 0 记 1 种方案，否则为 0
            ans = 0  # 当前状态的方案数
            for x in range(i + 1, m):  # 枚举横切位置，把上方部分切走
                if s[x][n] - s[i][n] - s[x][j] + s[i][j] > 0:  # 上方那块必须有苹果，否则这种切法不合法
                    ans += dfs(x, j, k - 1)  # 下方剩余部分继续切 k-1 刀
            for y in range(j + 1, n):  # 枚举竖切位置，把左侧部分切走
                if s[m][y] - s[i][y] - s[m][j] + s[i][j] > 0:  # 左侧那块必须有苹果
                    ans += dfs(i, y, k - 1)  # 右侧剩余部分继续切 k-1 刀
            return ans % mod  # 取模后返回当前状态的方案数

        mod = 10**9 + 7  # 取模常量
        m, n = len(pizza), len(pizza[0])  # m 是行数，n 是列数
        s = [[0] * (n + 1) for _ in range(m + 1)]  # (m+1)×(n+1) 的二维前缀和，多一行一列让边界天然为 0
        for i, row in enumerate(pizza, 1):  # 行列下标都从 1 开始枚举，对应前缀和的偏移
            for j, c in enumerate(row, 1):  # 同上，逐列推进
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + int(c == 'A')  # 容斥构造前缀和：上 + 左 - 左上 + 当前格；int(c == 'A') 把苹果记为 1
        return dfs(0, 0, k - 1)  # 整块披萨开始，要切成 k 块只需再切 k-1 刀
