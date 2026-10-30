# 题目：3302. 字典序最小的合法序列（Find the Lexicographically Smallest Valid Sequence）
# 思路：先倒序预处理 suf[i]（后缀 word1[i..] 最多能匹配 word2 的多少个尾部字符），再从左往右贪心，能选下标就选。
# 时间复杂度：O(m + n)，两趟线性扫描；空间复杂度：O(m)，suf 数组。
class Solution:  # LeetCode 约定的题解类
    def validSequence(self, word1: str, word2: str) -> List[int]:  # word1：候选字符来源；word2：待匹配目标；返回字典序最小的长度为 n 的合法下标序列
        m, n = len(word1), len(word2)  # m、n 分别是两个字符串的长度
        suf = [0] * (m + 1)  # suf[i]：word1[i..] 从右往左贪心匹配后，word2 仍需从前面补上的字符个数
        suf[m] = n  # 后缀为空时 word2 一个字符都还没匹配，需要 n 个
        j = n - 1  # 从 word2 的末尾开始倒序匹配
        for i in range(m - 1, -1, -1):  # 倒序扫描 word1，逐位求出后缀的匹配情况
            if j >= 0 and word1[i] == word2[j]:  # 当前字符正好等于 word2 待匹配的字符
                j -= 1  # 命中一个字符，匹配指针左移
            suf[i] = j + 1  # 记录该后缀之后还差 j+1 个前缀字符要补

        ans = []  # ans 保存选中的下标序列
        changed = False  # changed：唯一的“改一个字符”机会是否已经用掉
        j = 0  # j：当前要匹配的 word2 下标，从 0 开始
        for i, c in enumerate(word1):  # 从左往右贪心构造字典序最小的下标序列，c 为当前字符
            if c == word2[j] or (not changed and suf[i + 1] <= j + 1):  # 字符本来就相等；或还没用过修改机会，且剩余后缀能接上 word2[j+1..]
                if c != word2[j]:  # 字符不相等，说明这次必须消耗修改机会
                    changed = True  # 标记修改机会已用掉
                ans.append(i)  # 记录选中的下标
                j += 1  # 匹配进度 +1
                if j == n:  # word2 已经全部匹配完成
                    return ans  # 提前返回当前下标序列
        return []  # 无法构造合法序列，返回空数组
