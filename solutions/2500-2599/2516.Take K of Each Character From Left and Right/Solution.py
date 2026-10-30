# 题目：2516. 每种字符至少取 K 个（Take K of Each Character From Left and Right）
# 思路：逆向考虑「整段不取、留在中间」的最长子串，它需保证剩余每种字符仍有 k 个；用滑动窗口求最长合法窗口，答案为 n - 窗口长度。
# 时间复杂度：O(n)，每个下标最多被左右指针各访问一次；空间复杂度：O(1)，计数器只有 a/b/c 三个键。
class Solution:  # LeetCode 约定的题解类
    def takeCharacters(self, s: str, k: int) -> int:  # s 只含 a/b/c，k 是每种字符至少要取的数量
        cnt = Counter(s)  # 统计 a、b、c 的总出现次数
        if any(cnt[c] < k for c in "abc"):  # 只要有一种字符总数不足 k
            return -1  # 无法完成，返回 -1
        mx = j = 0  # mx：可以整段不取的最长子串长度；j：窗口左端点
        for i, c in enumerate(s):  # i 为窗口右端点，逐字扩展窗口
            cnt[c] -= 1  # 把 s[i] 划入「不取」的窗口，先从可取字符中扣除
            while cnt[c] < k:  # 扣除后该字符剩余不足 k，窗口不合法
                cnt[s[j]] += 1  # 把左端点字符移出窗口，使其重新可被取走
                j += 1  # 左端点右移
            mx = max(mx, i - j + 1)  # 窗口此时合法，更新最长长度
        return len(s) - mx  # 要取的字符数 = 总长度 - 可以整段不取的部分
