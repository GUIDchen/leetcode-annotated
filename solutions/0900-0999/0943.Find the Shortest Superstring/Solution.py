# 题目：943. 最短超级串（Find the Shortest Superstring）
# 思路：预处理任意两词的最大重叠长度 g，再用状压 DP 求「已用集合 mask、以 j 结尾」的最大重叠总量并记录前驱，回溯顺序后按重叠拼接。
# 时间复杂度：O(n²·2ⁿ)，n 为单词个数（另有 O(n³L) 的重叠预处理）；空间复杂度：O(n·2ⁿ)，dp 与前驱表。
class Solution:  # LeetCode 约定的题解类
    def shortestSuperstring(self, words: List[str]) -> str:  # words 是单词列表，返回包含全部单词的最短超级串
        n = len(words)  # 单词个数
        g = [[0] * n for _ in range(n)]  # g[i][j] 表示把 j 接在 i 后面时能重叠掉的最大字符数
        for i, a in enumerate(words):  # 枚举前一个单词，同时拿到下标 i 与单词 a
            for j, b in enumerate(words):  # 枚举后一个单词，同时拿到下标 j 与单词 b
                if i != j:  # 同一个单词不和自己算重叠
                    for k in range(min(len(a), len(b)), 0, -1):  # 从理论最长重叠长度倒着试，第一次命中的即为最大值
                        if a[-k:] == b[:k]:  # 判断 a 的后 k 个字符是否等于 b 的前 k 个字符
                            g[i][j] = k  # 记录这个最大重叠长度
                            break  # 已找到最大重叠，结束本对单词的搜索
        dp = [[0] * n for _ in range(1 << n)]  # dp[mask][j]：已用集合为 mask 且以 j 结尾时的最大重叠总量
        p = [[-1] * n for _ in range(1 << n)]  # p[mask][j]：最优状态的前一个单词，-1 表示没有前驱
        for i in range(1 << n):  # 枚举所有子集状态
            for j in range(n):  # 枚举该状态的最后一个单词
                if (i >> j) & 1:  # j 不在集合中时该状态无意义
                    pi = i ^ (1 << j)  # 去掉 j 得到前驱集合
                    for k in range(n):  # 枚举前驱集合的最后一个单词
                        if (pi >> k) & 1:  # k 必须属于前驱集合
                            v = dp[pi][k] + g[k][j]  # 在 k 后面接 j 的累计重叠量
                            if v > dp[i][j]:  # 出现更优方案
                                dp[i][j] = v  # 更新最大重叠量
                                p[i][j] = k  # 记录前驱，供回溯使用
        j = 0  # 全集中作为结尾的最优单词
        for i in range(n):  # 遍历所有可能的结尾单词
            if dp[-1][i] > dp[-1][j]:  # dp[-1] 即全集掩码对应的那一行，比较总重叠量
                j = i  # 记下更优的结尾
        arr = [j]  # 回溯出的顺序（先逆序保存）
        i = (1 << n) - 1  # 从全集状态开始回溯
        while p[i][j] != -1:  # 一直回溯到没有前驱为止
            i, j = i ^ (1 << j), p[i][j]  # 元组赋值先算右边：用旧的 i、j 求出前驱集合与前一个单词，再一起更新
            arr.append(j)  # 把前一个单词加入路径
        arr = arr[::-1]  # 翻转成从前往后的拼接顺序
        vis = set(arr)  # 记录路径上出现过的单词下标
        arr.extend([j for j in range(n) if j not in vis])  # 把重叠为 0 而没进入路径的孤立单词补到末尾
        ans = [words[arr[0]]] + [words[j][g[i][j] :] for i, j in pairwise(arr)]  # 首单词整串保留，其余只取去掉重叠部分后的后缀
        return ''.join(ans)  # 拼接成最短超级串返回
