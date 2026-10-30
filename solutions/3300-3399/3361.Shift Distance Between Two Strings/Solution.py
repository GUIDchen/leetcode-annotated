# 题目：3361. 两个字符串的切换距离（Shift Distance Between Two Strings）
# 思路：对 26 个字母分别做向右与向左两圈的前缀和，任意一段移动代价可 O(1) 求出；每位取两个方向中更便宜的一种累加。
# 时间复杂度：O(n + 26)，n 为串长；空间复杂度：O(26)。
class Solution:  # LeetCode 约定的题解类
    def shiftDistance(  # s、t：起止字符串；nextCost/previousCost：每个字母向右/向左走一步的代价
        self, s: str, t: str, nextCost: List[int], previousCost: List[int]  # 参数续行：起止字符串与两个代价数组
    ) -> int:  # 返回类型为 int
        m = 26  # 字母表大小 26
        s1 = [0] * (m << 1 | 1)  # 前缀代价表；m << 1 | 1 的优先级等价于 (m<<1)|1 = 2m+1，多出的一段用于绕环
        s2 = [0] * (m << 1 | 1)  # 向左切换的前缀代价表，同样长度 2m+1
        for i in range(m << 1):  # 预先算好两圈的前缀和
            s1[i + 1] = s1[i] + nextCost[i % m]  # 向右：第 i 步的代价取自字母 i%m
            s2[i + 1] = s2[i] + previousCost[(i + 1) % m]  # 向左：第 i 步是从字母 i+1 走回 i，代价取 previousCost[(i+1)%m]
        ans = 0  # 累计总切换距离
        for a, b in zip(s, t):  # 逐位配对处理两个字符串
            x, y = ord(a) - ord("a"), ord(b) - ord("a")  # 把字符换算成 0..25 的字母编号
            c1 = s1[y + m if y < x else y] - s1[x]  # 只用向右操作的代价；y < x 时绕一整圈，终点下标加 m
            c2 = s2[x + m if x < y else x] - s2[y]  # 只用向左操作的代价；x < y 时绕一整圈，起点下标加 m
            ans += min(c1, c2)  # 取两个方向中更便宜的代价累加
        return ans  # 返回总切换距离
