# 题目：3714. 最长的平衡子串 II（Longest Balanced Substring II）
# 思路：平衡子串按不同字符种类数分成三类——只有 1 种、恰好 2 种、3 种全有；分别用游程扫描、差前缀和哈希、二维差前缀和哈希求最长，三类取最大。
# 时间复杂度：O(n)，三个 calc 各线性扫描一遍；空间复杂度：O(n)，哈希表最多记录 n 个前缀状态。
class Solution:  # LeetCode 约定的题解类
    def longestBalanced(self, s: str) -> int:  # s：只含 a、b、c 的字符串；返回最长平衡子串的长度
        def calc1(s: str) -> int:  # 统计最长「全为同一字符」的连续段
            res = 0  # 结果长度
            i, n = 0, len(s)  # i：当前连续段起点；n：串长
            while i < n:  # 逐段扫描
                j = i + 1  # 从 i 之后开始探测相同字符
                while j < n and s[j] == s[i]:  # 找到第一个与 s[i] 不同的位置
                    j += 1  # 继续右移
                res = max(res, j - i)  # 更新最长连续段长度
                i = j  # 从新位置开始下一段
            return res  # 返回最长游程长度

        def calc2(s: str, a: str, b: str) -> int:  # 统计只由 a、b 组成且两者数量相等的最长子串
            res = 0  # 结果长度
            i, n = 0, len(s)  # i：扫描位置；n：串长
            while i < n:  # 逐个连续段处理
                while i < n and s[i] not in (a, b):  # 跳过不属于 {a, b} 的字符
                    i += 1  # 前进
                pos = {0: i - 1}  # 前缀差值 -> 首次出现下标，虚拟起点使段首的子串也能被统计
                d = 0  # a 记 +1、b 记 -1 的前缀差值
                while i < n and s[i] in (a, b):  # 在当前连续段内扩展
                    d += 1 if s[i] == a else -1  # 更新前缀差值
                    if d in pos:  # 该差值出现过：两下标之间 a、b 数量相等
                        res = max(res, i - pos[d])  # 更新最长长度
                    else:  # 首次出现该差值
                        pos[d] = i  # 记录下标
                    i += 1  # 前进到下一字符
            return res  # 返回最长长度

        def calc3(s: str) -> int:  # 统计三种字符数量都相等的最长子串
            pos = {(0, 0): -1}  # 二维差值 -> 首次出现下标，空前缀记为 -1
            cnt = Counter()  # a、b、c 的前缀出现次数
            res = 0  # 结果长度
            for i, c in enumerate(s):  # 遍历字符串
                cnt[c] += 1  # 对应字符计数加一
                k = (cnt["a"] - cnt["b"], cnt["b"] - cnt["c"])  # 两维差值作为元组键
                if k in pos:  # 该差值出现过：两下标之间三种字符数量相等
                    res = max(res, i - pos[k])  # 更新最长长度
                else:  # 首次出现该差值
                    pos[k] = i  # 记录下标
            return res  # 返回最长长度

        x = calc1(s)  # 只含一种字符的最长平衡子串
        y = max(calc2(s, "a", "b"), calc2(s, "b", "c"), calc2(s, "a", "c"))  # 恰好含两种字符的最长平衡子串，三种字符组合取最大
        z = calc3(s)  # 三种字符都出现且数量相等的平衡子串
        return max(x, y, z)  # 三类情况取最大即为答案
