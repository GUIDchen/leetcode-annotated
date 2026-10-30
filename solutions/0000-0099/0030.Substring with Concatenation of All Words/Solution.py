# 题目：30. 串联所有单词的子串（Substring with Concatenation of All Words）
# 思路：所有单词长度都是 k，串联子串的起点只能落在 i ∈ [0, k) 这 k 个「相位」上。对每个相位以步长 k 做滑动窗口：窗口里是一个个整词，用 Counter 统计词频，某个词超量或遇到词表外的词就收缩左端，窗口长度恰为 n*k 时左端即答案。
# 时间复杂度：O(m·k) 级别，m 是字符串长度，每个相位窗口总体右移 O(m/k) 次、每次切片比较 O(k)；空间复杂度：O(n·k)，存放单词表的计数。
class Solution:  # LeetCode 约定的题解类
    def findSubstring(self, s: str, words: List[str]) -> List[int]:  # s：主串；words：等长单词表；返回所有串联子串的起始下标
        cnt = Counter(words)  # cnt：words 中每个单词需要的出现次数（Counter 对缺失键返回 0）
        m, n = len(s), len(words)  # m 主串长度，n 单词个数
        k = len(words[0])  # k 每个单词的长度，题目保证所有单词等长
        ans = []  # ans 收集所有合法起始下标
        for i in range(k):  # 枚举 k 个相位：相位决定切分单词的对齐位置
            l = r = i  # 窗口左右边界一起初始化，之后都以步长 k 前进
            cnt1 = Counter()  # cnt1：当前窗口内各单词的出现次数
            while r + k <= m:  # r 处还能切出一个完整单词时继续扩右边界
                t = s[r : r + k]  # 取出 r 处的整词
                r += k  # 右边界右移一个词长
                if cnt[t] == 0:  # Counter 对不存在的键返回 0，等价于「t 不在 words 里」
                    l = r  # 窗口作废，左指针直接跳到 r 重新开始
                    cnt1.clear()  # 清空窗口内的词频统计
                    continue  # 跳过本轮剩余逻辑
                cnt1[t] += 1  # t 合法，窗口内计数加一
                while cnt1[t] > cnt[t]:  # 某个词出现次数超了，从左边不断吐出单词
                    rem = s[l : l + k]  # 取出左端的整词
                    l += k  # 左边界右移一个词长
                    cnt1[rem] -= 1  # 该词计数减一（不删键也没关系，判断只看数值）
                if r - l == n * k:  # 窗口长度正好是 n 个单词的总长，说明恰好用完全部单词
                    ans.append(l)  # 记录这个左端点作为答案
        return ans  # 返回全部答案下标
