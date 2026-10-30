# 题目：1576. 替换所有的问号（Replace All 's to Avoid Consecutive Repeating Characters）
# 思路：从左到右遇到问号时，只在 {a, b, c} 中挑一个与左右邻居都不同的字符填入；三个候选一定够用，因为每个位置最多只有两个邻居。
# 时间复杂度：O(n)，每个位置最多试 3 个字符；空间复杂度：O(n)，需要一份列表拷贝来实现原地修改。
class Solution:  # LeetCode 约定的题解类
    def modifyString(self, s: str) -> str:  # s 是输入字符串，返回替换问号后的字符串
        s = list(s)  # 字符串不可变，先转成列表以便按下标改写
        n = len(s)  # 长度，作为扫描边界
        for i in range(n):  # 从左到右逐位处理
            if s[i] == "?":  # 只处理问号位置
                for c in "abc":  # 候选只有 a/b/c 三个，足以避开左右两个邻居
                    if (i and s[i - 1] == c) or (i + 1 < n and s[i + 1] == c):  # 与左邻居或右邻居相同则该字符不可用
                        continue  # 换下一个候选字符
                    s[i] = c  # 三个条件都满足，把该字符写入当前位置
                    break  # 填好即跳出候选循环，继续处理后面的问号
        return "".join(s)  # 把列表拼回字符串返回
