# 题目：1946. 子字符串突变后可能得到的最大整数（Largest Number After Mutating Substring）
# 思路：从左往右贪心，先在能变大的连续区间内替换，一旦进入替换后又遇到会变小的位就立刻停止，保证只突变一个子串。
# 时间复杂度：O(n)，只需一次线性扫描；空间复杂度：O(n)，把字符串转成列表便于按位修改。
class Solution:  # LeetCode 约定的题解类
    def maximumNumber(self, num: str, change: List[int]) -> str:  # num：数字字符串；change：0~9 每个数字替换后的值
        s = list(num)  # 字符串不可变，转成列表才能按位替换
        changed = False  # 标记是否已经进入「正在突变的子串」
        for i, c in enumerate(s):  # 同时取出下标 i 与当前字符 c
            d = str(change[int(c)])  # 字符转数字，查表得到替换值，再转回字符
            if changed and d < c:  # 已在替换中且这一位替换后会变小，说明突变子串该结束
                break  # 再替换只会更小，立刻停止
            if d > c:  # 替换后变大，属于值得突变的位置
                changed = True  # 从这一位开始进入突变区间
                s[i] = d  # 真正完成这一位的替换
        return "".join(s)  # 列表拼回字符串作为答案
