# 题目：395. 至少有 K 个重复字符的最长子串（Longest Substring with At Least K Repeating Characters）
# 思路：某字符在区间内出现次数不足 k 次时它不可能属于答案，于是以它为界把区间切段，对每段递归求解并取最大。
# 时间复杂度：O(n·Σ)，每层按 26 个字母切段，递归深度至多 n；空间复杂度：O(n)，递归栈最深 n 层。
class Solution:  # LeetCode 约定的题解类
    def longestSubstring(self, s: str, k: int) -> int:  # s 是原串，k 要求每种出现的字符在子串内至少重复 k 次
        def dfs(l, r):  # 递归求闭区间 [l, r] 内的最长合法子串长度
            cnt = Counter(s[l : r + 1])  # 统计区间内每个字符的出现次数
            split = next((c for c, v in cnt.items() if v < k), '')  # 找出第一个次数不足 k 的字符作为分割符，找不到时取空串
            if not split:  # 没有字符违反条件
                return r - l + 1  # 整个区间都合法，直接返回区间长度
            i = l  # i 用来切分被分割符隔开的各段
            ans = 0  # 记录本层各段长度的最大值
            while i <= r:  # 从区间左端开始逐段扫描
                while i <= r and s[i] == split:  # 跳过连续出现的分割符
                    i += 1  # 右移越过分割符
                if i >= r:  # 剩余不足两个字符，后面不可能再构成合法段
                    break  # 提前结束扫描
                j = i  # j 用于寻找当前段的右端点
                while j <= r and s[j] != split:  # 一直走到下一个分割符或区间末尾
                    j += 1  # 右移扩张当前段
                t = dfs(i, j - 1)  # 递归处理这一段，注意右端是 j-1
                ans = max(ans, t)  # 用这一段的答案更新最大值
                i = j  # 从分割符位置继续向后扫描
            return ans  # 返回本层的最大长度

        return dfs(0, len(s) - 1)  # 从整个字符串开始递归，右端点是 len(s)-1
