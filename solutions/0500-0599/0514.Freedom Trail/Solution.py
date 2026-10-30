# 题目：514. 自由之路（Freedom Trail）
# 思路：动态规划。先按字符记下环上所有出现位置，f[i][j] 表示拼完 key[0..i] 且指针停在 j 的最小代价，转移时枚举上一个字符的位置并取环上最短旋转距离。
# 时间复杂度：O(m·n²)，每个字符对每种落点组合转移一次；空间复杂度：O(m·n)，即 DP 表大小。
class Solution:  # LeetCode 约定的题解类
    def findRotateSteps(self, ring: str, key: str) -> int:  # ring 是圆环，key 是要拼出的字符串
        m, n = len(key), len(ring)  # m 是关键字长度（阶段数），n 是环上字符数
        pos = defaultdict(list)  # 字符 -> 它在环上出现的全部下标，缺省值是空列表
        for i, c in enumerate(ring):  # 遍历圆环，建立字符到位置表的索引
            pos[c].append(i)  # 把位置 i 记到字符 c 名下
        f = [[inf] * n for _ in range(m)]  # f[i][j]：拼完前 i+1 个字符、指针停在 j 的最小步数，先全设成无穷大
        for j in pos[key[0]]:  # 第一个字符可以停在它出现的任意位置
            f[0][j] = min(j, n - j) + 1  # 从下标 0 转到 j 的最短距离，+1 表示按下按钮
        for i in range(1, m):  # 按顺序处理后面的每个字符
            for j in pos[key[i]]:  # 当前字符 key[i] 的候选落点
                for k in pos[key[i - 1]]:  # 上一个字符 key[i-1] 的候选落点
                    f[i][j] = min(  # 在「保持原值」和「由 k 转移过来」之间取较小者
                        f[i][j], f[i - 1][k] + min(abs(j - k), n - abs(j - k)) + 1  # 旧值，以及 上一阶段代价 + 环上最短距离 + 按键一次
                    )  # 结束 min 调用
        return min(f[-1][j] for j in pos[key[-1]])  # 最后一个字符的所有落点里取最小总代价
