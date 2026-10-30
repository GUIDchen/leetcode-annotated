# 题目：753. 破解保险箱（Cracking the Safe）——困难
# 思路：把「n-1 位前缀」看作结点、「接一位数字」看作有向边，答案即一条欧拉回路；用 Hierholzer 深搜，回溯时把数字追加到答案末尾。
# 时间复杂度：O(k^n)，共 k^n 条边且每条边只访问一次；空间复杂度：O(k^n)，访问集合与答案列表的规模都与边数同阶。
class Solution:  # LeetCode 约定的题解类
    def crackSafe(self, n: int, k: int) -> str:  # n 是密码位数，k 是数字种类（0~k-1）
        def dfs(u):  # 内部深搜：u 是当前所在的 n-1 位前缀
            for x in range(k):  # 尝试给前缀接上数字 x
                e = u * 10 + x  # 边 / 完整 n 位串的整数编码
                if e not in vis:  # 这条边还没走过
                    vis.add(e)  # 先标记为已访问，保证每条边只用一次
                    v = e % mod  # 取后 n-1 位，作为下一个结点
                    dfs(v)  # 递归进入新结点
                    ans.append(str(x))  # 回溯时再追加数字：得到的序列只差开头 n-1 个 0
        mod = 10 ** (n - 1)  # 10^(n-1)，用于截取后 n-1 位
        vis = set()  # 记录已经走过的边
        ans = []  # 逆序累积访问到的数字
        dfs(0)  # 从全 0 前缀出发，图连通所以一次深搜就能覆盖所有边
        ans.append("0" * (n - 1))  # 补齐开头缺失的 n-1 个 0，形成完整密码
        return "".join(ans)  # 拼成字符串返回
