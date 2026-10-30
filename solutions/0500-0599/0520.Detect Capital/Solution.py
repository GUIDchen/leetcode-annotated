# 题目：520. 检测大写字母（Detect Capital）
# 思路：统计大写字母个数 cnt，全部合法情形只有三种：全小写、全大写、仅首字母大写。
# 时间复杂度：O(n)，只需遍历一次字符串；空间复杂度：O(1)，只用一个计数变量。
class Solution:  # LeetCode 约定的题解类
    def detectCapitalUse(self, word: str) -> bool:  # word：待判定的字符串；返回它的大小写用法是否合法
        cnt = sum(c.isupper() for c in word)  # 生成器表达式逐字符判断 isupper，sum 把 True 累加成大写字母个数
        return cnt == 0 or cnt == len(word) or (cnt == 1 and word[0].isupper())  # 返回判定：没有大写（全小写）/ 全部大写 / 恰好一个大写且它在首位（仅首字母大写）
