# 题目：2052. 将句子分隔成行的最低成本（Minimum Cost to Separate Sentence Into Rows）
# 思路：按空格切词并求单词长度前缀和；记忆化搜索 dfs(i) 表示从第 i 个单词开始排版的最小代价，本行放 [i, j) 时代价为剩余空格的平方，最后一行不计代价。
# 时间复杂度：O(n^2)，每个起点最多枚举 n 个断行位置；空间复杂度：O(n)，前缀和数组与记忆化缓存。
class Solution:  # 题解类
    def minimumCost(self, sentence: str, k: int) -> int:  # sentence 是原句，k 是每行宽度上限
        @cache  # 记忆化装饰器：同一个起点 i 只计算一次
        def dfs(i: int) -> int:  # dfs(i)：从第 i 个单词开始排版的最小代价
            if s[n] - s[i] + n - i - 1 <= k:  # 剩余单词全放一行也不超宽，说明这是最后一行
                return 0  # 最后一行不计代价
            ans = inf  # 用无穷大初始化，方便取最小值
            j = i + 1  # 从下一个单词开始尝试作为新一行的开头
            while j < n and (m := s[j] - s[i] + j - i - 1) <= k:  # m 是本行长度（单词长度和 + 词间空格），超过 k 就停止扩展
                ans = min(ans, dfs(j) + (k - m) ** 2)  # 本行代价为剩余空格的平方，加上后续最优代价
                j += 1  # 换下一个断行位置
            return ans  # 返回从 i 开始的最小代价

        nums = [len(s) for s in sentence.split()]  # 按空格切句，求每个单词的长度（这里的 s 只是临时变量）
        n = len(nums)  # 单词个数
        s = list(accumulate(nums, initial=0))  # 前缀和，initial=0 让 s[i] 表示前 i 个单词的总长度
        return dfs(0)  # 从第 0 个单词开始求解
