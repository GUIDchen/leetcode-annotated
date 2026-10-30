# 题目：2067. 等计数子串的数量（Number of Equal Count Substrings）
# 思路：枚举子串里出现的不同字符数 i，则窗口长度固定为 i*count；滑动窗口用记号 t 记录「出现次数恰好为 count 的字符个数」，t == i 时累加答案。
# 时间复杂度：O(26n)，内层窗口对每个 i 扫一遍原串；空间复杂度：O(26)，只用了固定大小的计数容器。
class Solution:  # LeetCode 约定的题解类
    def equalCountSubstrings(self, s: str, count: int) -> int:  # s 是原串，count 是每个出现字符要求出现的次数
        ans = 0  # ans 统计满足条件的子串个数
        for i in range(1, 27):  # 枚举子串中出现的不同字符数 i，最多 26 种
            k = i * count  # 当前 i 对应的窗口长度
            if k > len(s):  # 窗口比原串还长，更大的 i 只会更长
                break  # 提前结束 i 的枚举
            cnt = Counter()  # 当前 i 下窗口内各字符的出现次数
            t = 0  # t 记录出现次数恰好为 count 的字符个数
            for j, c in enumerate(s):  # j 是窗口右端点下标，c 是右端字符
                cnt[c] += 1  # 右端字符频次加 1
                t += cnt[c] == count  # 频次恰好等于 count，说明该字符进入达标状态，t 加 1
                t -= cnt[c] == count + 1  # 频次变成 count+1，说明它刚掉出达标状态，t 减 1
                if j >= k:  # 窗口长度超过 k，需要移除左端字符
                    cnt[s[j - k]] -= 1  # 左端字符频次减 1
                    t += cnt[s[j - k]] == count  # 减后恰好等于 count，说明它从 count+1 回到达标，t 加 1
                    t -= cnt[s[j - k]] == count - 1  # 减后等于 count-1，说明它刚离开达标状态，t 减 1
                ans += i == t  # i 种字符都出现 count 次，说明这个窗口是合法子串
        return ans  # 返回所有 i 下累加得到的合法子串总数
