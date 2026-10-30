# 题目：1189. “气球” 的最大数量（Maximum Number of Balloons）
# 思路：用 Counter 统计词频，把需要两份的 o、l 折半，再对 b/a/l/o/n 取最小值。
# 时间复杂度：O(n)，遍历一次 text 加常数次比较；空间复杂度：O(1)，最多 26 个键。
class Solution:  # LeetCode 约定的题解类
    def maxNumberOfBalloons(self, text: str) -> int:  # 返回最多能拼出多少个 "balloon"
        cnt = Counter(text)  # 统计每个字符出现的次数，缺失的键访问时按 0 计
        cnt['o'] >>= 1  # 一个 balloon 需要两个 o，先折半（右移一位等于除以 2）
        cnt['l'] >>= 1  # 一个 balloon 也需要两个 l，同样折半
        return min(cnt[c] for c in 'balon')  # 其余字母各需一个，最小值就是答案
