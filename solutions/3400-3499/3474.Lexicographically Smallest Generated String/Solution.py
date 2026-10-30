# 3474. Lexicographically Smallest Generated String / 3474. 字典序最小的生成字符串
# 核心思路：先按所有 T 位置把 t 强制写入，再从右往左为仍与 t 相同的 F 窗口放一个 'b' 破坏匹配，从而字典序增量最小。
# 复杂度：时间 O((n + m) * m)，空间 O(n + m)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def generateString(self, s: str, t: str) -> str:  # 返回满足所有 T/F 约束的字典序最小字符串
        n, m = len(s), len(t)  # n 为约束个数，m 为模式串 t 的长度
        ans = ["a"] * (n + m - 1)  # 结果串长度固定为 n + m - 1，先全部填字典序最小的 'a'
        fixed = [False] * (n + m - 1)  # 标记每个位置是否已被 T 约束强制写死

        for i, b in enumerate(s):  # 先处理所有 T 约束
            if b != "T":  # 只处理要求完全匹配的位置
                continue  # 跳过 F 约束
            for j, c in enumerate(t):  # 把模式串逐位写入窗口
                k = i + j  # 对应的结果串下标
                if fixed[k] and ans[k] != c:  # 与之前写死的字符冲突
                    return ""  # 无解，返回空串
                ans[k] = c  # 写入模式串字符
                fixed[k] = True  # 标记该位置已固定

        for i, b in enumerate(s):  # 再处理所有 F 约束
            if b != "F":  # 只处理要求不完全匹配的位置
                continue  # 跳过 T 约束
            if "".join(ans[i : i + m]) != t:  # 判断当前窗口是否已经不等于模式串
                continue  # 已经满足 F 约束，无需处理
            for j in range(i + m - 1, i - 1, -1):  # 从右往左找第一个可自由修改的位置
                if not fixed[j]:  # 找到非固定位置
                    ans[j] = "b"  # 改成 'b' 破坏匹配，且字典序增加最少
                    break  # 只改一个字符即可
            else:  # 循环正常结束说明窗口内全被固定
                return ""  # 无法破坏匹配，无解

        return "".join(ans)  # 返回构造出的字典序最小字符串
