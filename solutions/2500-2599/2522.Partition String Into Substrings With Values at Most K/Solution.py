# 题目：2522. 将字符串分割成值不超过 K 的子字符串（Partition String Into Substrings With Values at Most K）
# 核心思路：记忆化搜索。dfs(i) 表示把后缀 s[i:] 切分的最少段数；从 i 起枚举子串右端点，数值一旦超过 k 就停止，取所有可行切法的最小值再加一。
# 时间复杂度：O(n^2)，每个状态最多枚举 n 个右端点；空间复杂度：O(n)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def minimumPartition(self, s: str, k: int) -> int:  # s：只含数字的字符串；k：每个子串数值的上界
        @cache  # cache 缓存 dfs 的结果，避免指数级重复搜索
        def dfs(i):  # dfs(i)：把后缀 s[i:] 切分的最少段数
            if i >= n:  # 已经越过末尾，无需再切分
                return 0  # 返回 0 段
            res, v = inf, 0  # res 初始为不可达；v 累积当前子串的数值
            for j in range(i, n):  # 枚举子串右端点 j，当前子串为 s[i..j]
                v = v * 10 + int(s[j])  # 把数字字符转成数字并拼接到 v 末尾
                if v > k:  # 数值超过 k 时
                    break  # 更长的子串只会更大，直接跳出循环
                res = min(res, dfs(j + 1))  # 当前子串合法，递归求剩余部分的段数并取最小值
            return res + 1  # 当前段数 = 剩余最少段数 + 1

        n = len(s)  # 字符串长度，供 dfs 中的边界判断使用
        ans = dfs(0)  # 从下标 0 开始求解整个字符串
        return ans if ans < inf else -1  # 有解返回最少段数，否则按题意返回 -1
