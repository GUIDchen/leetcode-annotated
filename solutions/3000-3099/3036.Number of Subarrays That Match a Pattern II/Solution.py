# 题目：3036. 匹配模式数组的子数组数目 II（Number of Subarrays That Match a Pattern II）
# 思路：先把 nums 的相邻大小关系压缩成 1/0/-1 序列，再用 KMP 统计 pattern 在该序列中出现的次数，整体线性。
# 时间复杂度：O(n + m)，KMP 均摊线性；空间复杂度：O(n + m)，额外保存了差值序列与 pi 数组。
def partial(s):  # 预处理 KMP 的 pi 数组：pi[i] 是 s[0..i] 的最长相等前后缀长度
    g, pi = 0, [0] * len(s)  # g 是当前已匹配的前缀长度，pi 初始化为全零
    for i in range(1, len(s)):  # 从第二个字符开始逐个计算 pi
        while g and (s[g] != s[i]):  # 候选前缀字符对不上，就不断回退
            g = pi[g - 1]  # 回退到更短的相等前后缀，继续尝试
        pi[i] = g = g + (s[g] == s[i])  # 字符相等则长度加一（True 当作 1），同时写入 pi[i]
    return pi  # 返回算好的 pi 数组


def match(s, pat):  # 用 KMP 找出 pat 在 s 中所有出现的位置
    pi = partial(pat)  # 先对模式串做预处理
    g, idx = 0, []  # g 是当前已匹配长度，idx 收集每个匹配起点的下标
    for i in range(len(s)):  # 依次扫描主串的每个字符
        while g and pat[g] != s[i]:  # 失配时按 pi 回退，避免从头重新比对
            g = pi[g - 1]  # 跳到更短的候选前缀长度
        g += pat[g] == s[i]  # 字符相同则匹配长度加一
        if g == len(pi):  # 匹配长度等于模式长度，说明找到一次完整匹配
            idx.append(i + 1 - g)  # 起点下标 = 当前下标 - 匹配长度 + 1
            g = pi[g - 1]  # 回退，以便继续找出重叠的下一处匹配
    return idx  # 返回所有匹配起点的下标列表


def string_find(s, pat):  # 判断 pat 是否为 s 的子串（只关心存在性）
    pi = partial(pat)  # 对模式串预处理出 pi 数组
    g = 0  # 当前已匹配的长度
    for i in range(len(s)):  # 扫描主串的每个字符
        while g and pat[g] != s[i]:  # 失配则沿 pi 回退
            g = pi[g - 1]  # 退到更短的可复用前缀
        g += pat[g] == s[i]  # 相等则匹配长度加一
        if g == len(pi):  # 完整匹配到模式串
            return True  # 只要存在一次就立刻返回 True
    return False  # 扫描结束仍未匹配，返回 False


class Solution:  # LeetCode 约定的题解类
    def countMatchingSubarrays(self, nums: List[int], pattern: List[int]) -> int:  # nums 是原数组，pattern 是关系模式
        s = []  # 存放相邻元素压缩后的 1/0/-1 序列
        for i in range(1, len(nums)):  # 从第二个元素开始遍历每一对相邻元素
            if nums[i] > nums[i - 1]:  # 当前元素比前一个大
                s.append(1)  # 上升记作 1
            elif nums[i] == nums[i - 1]:  # 当前元素与前一个相等
                s.append(0)  # 相等记作 0
            else:  # 当前元素比前一个小
                s.append(-1)  # 下降记作 -1
        return len(match(s, pattern))  # 关系序列中 pattern 的出现次数就是答案
