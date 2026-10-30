# 题目：3298. 统计重新排列后包含另一个字符串的子字符串数目 II（Count Substrings That Can Be Rearranged to Contain a String II）
# 思路：与 I 相同的滑动窗口：need 记录还差几种字母，窗口满足时不断右移左端点，答案累加以当前右端点结尾的合法起点数 l。
# 时间复杂度：O(n + m)，每个字符至多进出窗口一次；空间复杂度：O(1)，计数器大小不超过字母表规模。
class Solution:  # LeetCode 约定的题解类
    def validSubstringCount(self, word1: str, word2: str) -> int:  # word1 是长串，word2 是目标串（字符可任意重排）
        if len(word1) < len(word2):  # 长串比目标串短，不可能包含它
            return 0  # 直接返回 0
        cnt = Counter(word2)  # cnt 记录 word2 中每个字母的需求次数
        need = len(cnt)  # need 记录还有几种字母没被窗口满足
        ans = l = 0  # ans 统计合法子串数，l 是窗口左端点
        win = Counter()  # win 记录当前窗口内每个字母的出现次数
        for c in word1:  # 右端点逐字符向右扩展
            win[c] += 1  # 把当前字符计入窗口
            if win[c] == cnt[c]:  # 该字母数量刚好补齐需求
                need -= 1  # 少一种未满足的字母
            while need == 0:  # 窗口已满足全部需求，尝试收缩左端点
                if win[word1[l]] == cnt[word1[l]]:  # 移出这个字符后它的数量就不够了
                    need += 1  # 重新标记为未满足
                win[word1[l]] -= 1  # 把左端点字符移出窗口
                l += 1  # 左端点右移
            ans += l  # 以当前字符结尾、起点在 0..l-1 的子串都合法，共 l 个
        return ans  # 返回合法子串总数
