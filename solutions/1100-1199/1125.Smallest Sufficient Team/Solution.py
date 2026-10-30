# 题目：1125. 最小的必要团队（Smallest Sufficient Team）
# 思路：把 m 个技能压成二进制掩码，先算出每个人掌握的技能掩码，再做状压 DP：f[mask] 表示覆盖技能集合 mask 所需的最少人数，用 g/h 数组分别记录「最后加入的人」和「前驱状态」，最后从满集合沿前驱回溯出团队名单。
# 时间复杂度：O(2^m · n)，共有 2^m 个状态、每个状态枚举 n 个人；空间复杂度 O(2^m)，需要三张大小为 2^m 的数组。
class Solution:  # LeetCode 约定的题解类
    def smallestSufficientTeam(  # 参数较多，按 LeetCode 风格折行书写函数签名
        self, req_skills: List[str], people: List[List[str]]  # self 是实例；req_skills 是必需技能，people 是每人掌握的技能
    ) -> List[int]:  # 返回最少人数团队成员的下标列表
        d = {s: i for i, s in enumerate(req_skills)}  # 技能名 → 位编号，把技能集合压成整数掩码
        m, n = len(req_skills), len(people)  # m：必需技能数；n：候选人数
        p = [0] * n  # p[i]：第 i 个人掌握的技能掩码
        for i, ss in enumerate(people):  # 同时取出人和他的技能列表
            for s in ss:  # 遍历该人掌握的每个技能
                p[i] |= 1 << d[s]  # 把该技能对应的位或进掩码
        f = [inf] * (1 << m)  # f[mask]：覆盖该集合所需的最少人数，inf 表示不可达
        g = [0] * (1 << m)  # g[mask]：转移到该集合时最后加入的人
        h = [0] * (1 << m)  # h[mask]：转移前的前驱集合，用于回溯
        f[0] = 0  # 空集合不需要任何人
        for i in range(1 << m):  # 枚举所有技能集合作为起点
            if f[i] == inf:  # 不可达状态直接跳过
                continue  # 跳过本状态
            for j in range(n):  # 尝试让第 j 个人加入
                if f[i] + 1 < f[i | p[j]]:  # 人数更少才转移，保证 f 取到最小值
                    f[i | p[j]] = f[i] + 1  # 更新最少人数
                    g[i | p[j]] = j  # 记录本次加入的人
                    h[i | p[j]] = i  # 记录前驱集合
        i = (1 << m) - 1  # 从满集合开始回溯
        ans = []  # 答案列表
        while i:  # 沿前驱回溯到空集合为止
            ans.append(g[i])  # 把该集合最后加入的人加入答案
            i = h[i]  # 继续向前回溯
        return ans  # 返回人数最少的团队成员下标列表
