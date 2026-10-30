# 题目：902. 最大为 N 的数字组合（Numbers At Most N Given Digit Set）
# 核心思路：数位 DP，逐位枚举可填数字，用 lead 表示是否仍为前导零、limit 表示是否贴上界，并用 cache 记忆化。
# 时间复杂度：O(len(N) * 10 * 2 * 2)；空间复杂度：O(len(N)) 的记忆化状态。
class Solution:  # LeetCode 约定的题解类
    def atMostNGivenDigitSet(self, digits: List[str], n: int) -> int:  # digits：允许使用的数字字符；n：上界
        @cache  # 自动记忆化：同一个 (i, lead, limit) 只计算一次
        def dfs(i: int, lead: int, limit: bool) -> int:  # i：当前位；lead：是否仍全是前导零；limit：是否贴上界
            if i >= len(s):  # 所有位都填完了
                return lead ^ 1  # lead 为 1 说明没填任何数字（不计入），否则计为一个合法方案

            up = int(s[i]) if limit else 9  # 当前位的上限：贴界取 N 的这一位，否则取 9
            ans = 0  # 当前状态的方案数
            for j in range(up + 1):  # 枚举当前位可填的数字
                if j == 0 and lead:  # 保持前导零，这一位相当于不填
                    ans += dfs(i + 1, 1, limit and j == up)  # 前导零延续；只有贴界且取到上界时才继续贴界
                elif j in nums:  # 填一个允许使用的数字
                    ans += dfs(i + 1, 0, limit and j == up)  # 离开前导零状态，继续递归
            return ans  # 返回当前状态的方案数

        s = str(n)  # 把上界转成字符串，便于逐位取数字
        nums = {int(x) for x in digits}  # 允许使用的数字集合
        return dfs(0, 1, True)  # 从最高位开始，初始有前导零且贴上界
