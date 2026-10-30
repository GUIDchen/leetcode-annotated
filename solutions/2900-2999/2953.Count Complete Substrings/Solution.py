# 题目：2953. 统计完全子字符串（Count Complete Substrings）
# 思路：先按「相邻字符差不超过 2」把串切成互不影响的块；块内完全子串长度必为 i*k，用定长滑动窗口配合频次计数统计。
# 时间复杂度：O(n * 26)，块内枚举字母种数并线性滑窗；空间复杂度：O(26)，计数器大小为常数。
class Solution:  # LeetCode 约定的题解类
    def countCompleteSubstrings(self, word: str, k: int) -> int:  # word 是输入字符串，k 是每种字母必须出现的次数；返回完全子串个数
        def f(s: str) -> int:  # 处理单块：块内相邻字符差都不超过 2
            m = len(s)  # 当前块长度
            ans = 0  # 块内答案
            for i in range(1, 27):  # 完全子串恰含 i 种字母，长度必为 i*k
                l = i * k  # 对应的窗口长度
                if l > m:  # 窗口比整块还长，更大的 i 只会更不可能，直接跳出
                    break  # 跳出枚举
                cnt = Counter(s[:l])  # 初始窗口内各字母的出现次数
                freq = Counter(cnt.values())  # 频次表：出现次数 -> 有多少种字母是这个次数
                ans += freq[k] == i  # i 种字母各出现 k 次时布尔值为 True，累加即加一
                for j in range(l, m):  # 定长窗口逐位右移
                    freq[cnt[s[j]]] -= 1  # 字符 s[j] 进窗前，先撤销它的旧频次
                    cnt[s[j]] += 1  # 计数加一
                    freq[cnt[s[j]]] += 1  # 再登记新频次

                    freq[cnt[s[j - l]]] -= 1  # 字符 s[j-l] 离开窗口，撤销它的旧频次
                    cnt[s[j - l]] -= 1  # 计数减一
                    freq[cnt[s[j - l]]] += 1  # 再登记新频次

                    ans += freq[k] == i  # 每个窗口都判断一次是否满足条件
            return ans  # 返回该块答案

        n = len(word)  # 字符串总长度
        ans = i = 0  # ans 累计总答案，i 是当前块起点
        while i < n:  # 按块扫描整个字符串
            j = i + 1  # 块至少包含 i 这一个字符
            while j < n and abs(ord(word[j]) - ord(word[j - 1])) <= 2:  # 相邻字符差大于 2 就是块边界，必须断开
                j += 1  # 继续向右扩展当前块
            ans += f(word[i:j])  # 把该块的贡献累加进总答案
            i = j  # 跳到下一块起点
        return ans  # 返回全部完全子串的个数
