# 题目：1659. 最大化网格幸福感（Maximize Grid Happiness）
# 思路：三进制状态压缩每一行，预处理单行幸福度 f 与相邻行幸福度 g，再用带缓存的 DFS 逐行分配人数。
# 时间复杂度：O(m · 3^n · 3^n · I · E)；空间复杂度：O(m · 3^n · I · E)，即缓存表的大小。
class Solution:  # LeetCode 约定的题解类
    def getMaxGridHappiness(  # 参数分多行书写：m 行、n 列、两种人数
        self, m: int, n: int, introvertsCount: int, extrovertsCount: int  # self 是实例，后面依次是行数、列数、内向者人数、外向者人数
    ) -> int:  # 返回能获得的最大幸福感
        @cache  # 装饰器：给 dfs 自动加记忆化缓存，相同状态不重复计算
        def dfs(i: int, pre: int, ic: int, ec: int) -> int:  # 递归函数：i 当前行号、pre 上一行状态、ic/ec 剩余人数
            if i == m or (ic == 0 and ec == 0):  # 边界：填完所有行，或两种人都用完
                return 0  # 没有更多可放的位置，贡献为 0
            ans = 0  # 本行枚举中的最优值，初始为 0
            for cur in range(mx):  # 枚举当前行所有可能状态
                if ix[cur] <= ic and ex[cur] <= ec:  # 人数够用该状态才可行
                    a = f[cur] + g[pre][cur]  # a：本行自身幸福 + 与上一行的相互影响
                    b = dfs(i + 1, cur, ic - ix[cur], ec - ex[cur])  # b：继续分配后面各行能得到的最优值
                    ans = max(ans, a + b)  # 在本行所有可行状态中取最大值
            return ans  # 返回本层答案（@cache 会自动缓存）
        # 先按行状态建表，再进入搜索；dfs 里引用的 mx / f / g 等此时已赋值
        mx = pow(3, n)  # mx 是行状态总数：n 列每列三态，共 3^n 种
        f = [0] * mx  # f[状态]：该行自身的幸福感
        g = [[0] * mx for _ in range(mx)]  # g[a][b]：上一行 a、当前行 b 时同列相邻的幸福感
        h = [[0, 0, 0], [0, -60, -10], [0, -10, 40]]  # 相邻两人幸福度增量表：h[自己类型][邻居类型]
        bits = [[0] * n for _ in range(mx)]  # bits[状态][列]：三进制展开后每一位的类型
        ix = [0] * mx  # ix[状态]：该行用掉的内向者数量
        ex = [0] * mx  # ex[状态]：该行用掉的外向者数量
        for i in range(mx):  # 枚举所有行状态
            mask = i  # 拷贝一份三进制数用于逐位拆解
            for j in range(n):  # 逐列拆出人员类型
                mask, x = divmod(mask, 3)  # divmod 一次得到商与余数：x 是最低位（当前列类型）
                bits[i][j] = x  # 记录该状态第 j 列的类型
                if x == 1:  # 1 表示内向者
                    ix[i] += 1  # 内向者计数加一
                    f[i] += 120  # 内向者自身基础幸福感 120
                elif x == 2:  # 2 表示外向者
                    ex[i] += 1  # 外向者计数加一
                    f[i] += 40  # 外向者自身基础幸福感 40
                if j:  # j 非 0 说明左边还有邻居
                    f[i] += h[x][bits[i][j - 1]]  # 加上与左邻的相互影响（查表 h）
        for i in range(mx):  # 枚举上一行状态
            for j in range(mx):  # 枚举当前行状态
                for k in range(n):  # 逐列统计同列上下相邻的影响
                    g[i][j] += h[bits[i][k]][bits[j][k]]  # 累加上下行同列两人的幸福感增量
        return dfs(0, 0, introvertsCount, extrovertsCount)  # 从第 0 行、上一行为空状态开始搜索
