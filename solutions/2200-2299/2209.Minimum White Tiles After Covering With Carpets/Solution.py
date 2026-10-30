# 题目：2209. 用地毯覆盖后的最少白色砖块（Minimum White Tiles After Covering With Carpets）
# 核心思路：记忆化搜索。dfs(i, j) 表示从位置 i 起、还剩 j 块地毯时的最少剩余白砖；
#           遇到白砖可「放弃」或「用一块地毯覆盖 [i, i+carpetLen)」，取两者较小值；黑砖直接跳过。
# 时间复杂度：O(n * numCarpets)，每个状态只计算一次；空间复杂度：O(n * numCarpets)，缓存加 O(n) 前缀和。
class Solution:  # LeetCode 约定的题解类
    def minimumWhiteTiles(self, floor: str, numCarpets: int, carpetLen: int) -> int:  # floor 是地板串，numCarpets 是地毯数，carpetLen 是每块地毯长度
        @cache  # 记忆化装饰器：相同的 (i, j) 只会真正计算一次
        def dfs(i: int, j: int) -> int:  # dfs(i, j)：从位置 i 起、还剩 j 块地毯时的最少剩余白砖数
            if i >= n:  # 已经走到地板末尾，后面没有砖块
                return 0  # 剩余白砖数为 0
            if floor[i] == "0":  # 当前位置是黑砖，覆盖它没有收益
                return dfs(i + 1, j)  # 直接右移一格，地毯数量不变
            if j == 0:  # 地毯已经用完，只能把后面的白砖全部计入答案
                return s[-1] - s[i]  # 前缀和之差就是区间 [i, n) 的白砖数
            return min(1 + dfs(i + 1, j), dfs(i + carpetLen, j - 1))  # 两种选择取小：放弃这块白砖，或用一块地毯覆盖 [i, i+carpetLen)

        n = len(floor)  # 地板的总长度
        s = [0] * (n + 1)  # 前缀和数组：s[i] 是 floor[0..i-1] 中白砖 '1' 的个数
        for i, c in enumerate(floor):  # 逐格统计白砖
            s[i + 1] = s[i] + int(c == "1")  # 白砖加 1、黑砖加 0，滚动得到前缀和
        ans = dfs(0, numCarpets)  # 从位置 0 出发求解
        dfs.cache_clear()  # 主动清空缓存，避免记忆化结果长期占用内存
        return ans  # 返回覆盖后最少的白砖数
