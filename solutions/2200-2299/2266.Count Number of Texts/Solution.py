# 题目：2266. 统计打字方案数（Count Number of Texts）
# 思路：用 groupby 把按键序列切成连续相同字符段；长度为 m 的一段，按键属于 "79" 时方案数为 g[m]，否则为 f[m]；各段方案数相乘后取模。
# 时间复杂度：预处理 O(N)（N 约 1e5，只做一次），每次调用 O(|pressedKeys|)；空间复杂度：O(N)，保存两个递推表。
mod = 10**9 + 7  # 取模常量，避免方案数过大
f = [1, 1, 2, 4]  # f[m]：普通键（3 个字母）长度 m 的连续段方案数，先给出递推初值
g = [1, 1, 2, 4]  # g[m]：7/9 键（4 个字母）长度 m 的连续段方案数，初值与 f 相同
for _ in range(100000):  # 把两张表都预处理到长度 100004，足以覆盖题目上界
    f.append((f[-1] + f[-2] + f[-3]) % mod)  # 3 字母键：最后一段可以是 1/2/3 个相同字母
    g.append((g[-1] + g[-2] + g[-3] + g[-4]) % mod)  # 4 字母键：最后一段可以是 1/2/3/4 个相同字母


class Solution:  # LeetCode 约定的题解类
    def countTexts(self, pressedKeys: str) -> int:  # pressedKeys：按键序列
        ans = 1  # 乘法累加器，初始为 1
        for c, s in groupby(pressedKeys):  # groupby 把相邻相同字符聚成一组：c 是字符，s 是该段的可迭代对象
            m = len(list(s))  # 物化该段迭代器得到连续相同字符的个数
            ans = ans * (g[m] if c in "79" else f[m]) % mod  # 7/9 键用 g，其余用 f；乘完立即取模
        return ans  # 各段方案数之积即为答案
