# 题目：2109. 向字符串添加空格（Adding Spaces to a String）
# 思路：两个指针同步扫描，j 指向下一个待插空格的下标；遍历 s 时若当前位置命中就先放入空格，再放入字符，最后 join 成字符串。
# 时间复杂度：O(n + m)，n 为字符串长度、m 为空格个数；空间复杂度：O(n)，列表与结果字符串。
class Solution:  # LeetCode 约定的题解类
    def addSpaces(self, s: str, spaces: List[int]) -> str:  # s 是原字符串，spaces 是升序的插入位置数组
        ans = []  # ans 用列表收集结果字符，避免反复创建字符串
        j = 0  # j 指向 spaces 中下一个待处理的位置
        for i, c in enumerate(s):  # i 是当前字符下标，c 是当前字符
            if j < len(spaces) and i == spaces[j]:  # 当前位置就是需要插入空格的位置（先判 j 未越界再比较）
                ans.append(' ')  # 先追加一个空格
                j += 1  # 该空格位置处理完毕，j 后移
            ans.append(c)  # 再追加原字符
        return ''.join(ans)  # 把字符列表拼接成最终字符串
