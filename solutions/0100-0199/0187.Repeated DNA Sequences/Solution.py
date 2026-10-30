# 题目：187. 重复的DNA序列（Repeated DNA Sequences）
# 思路：滑动窗口枚举所有长度 10 的子串，用计数器统计频次，频次恰好变成 2 时收入答案。
# 时间复杂度：O(n·L)，L=10，切片与哈希均为 O(L)；空间复杂度：O(n·L)，最坏保存全部子串。
class Solution:  # LeetCode 约定的题解类
    def findRepeatedDnaSequences(self, s: str) -> List[str]:  # s 是只含 A/C/G/T 的 DNA 字符串
        cnt = Counter()  # 计数器：键是长度为 10 的子串，值是出现次数
        ans = []  # 结果列表，存放重复出现过的子串
        for i in range(len(s) - 10 + 1):  # i 遍历所有可能的窗口起点（长度不足 10 时循环不执行）
            t = s[i : i + 10]  # Python 切片取出 s[i..i+9] 这 10 个字符
            cnt[t] += 1  # 该子串出现次数加 1（Counter 对缺失键默认返回 0）
            if cnt[t] == 2:  # 恰好第二次出现，说明是重复序列
                ans.append(t)  # 只记录一次，防止第三次及以后重复追加
        return ans  # 返回所有重复出现的 10 长序列
