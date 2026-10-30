# 题目：2380. 二进制字符串重新安排顺序需要的时间（Time Needed to Rearrange a Binary String）
# 思路：每一秒把字符串中所有互不重叠的 '01' 同时替换为 '10'；str.replace 替换的正是互不重叠的出现位置，等价于题意中的同时替换，反复执行到不存在 '01' 为止，次数即答案。
# 时间复杂度：O(n^2)，最坏每秒都要完整扫描一次字符串；空间复杂度：O(n)，每轮 replace 都会生成新字符串。
class Solution:  # LeetCode 约定的题解类
    def secondsToRemoveOccurrences(self, s: str) -> int:  # s 为只含 '0' 与 '1' 的字符串，返回把全部 1 移到左侧所需的秒数
        ans = 0  # ans 记录已经过的秒数
        while s.count('01'):  # 只要串中还存在 '01'，就还需要继续下一秒
            s = s.replace('01', '10')  # 一次性替换所有互不重叠的 '01'，与题意「同一秒同时交换」等价
            ans += 1  # 秒数加一
        return ans  # 返回总秒数
