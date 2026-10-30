# 题目：3931. 检查相邻数字差（Check Adjacent Digit Differences）
# 思路：把字符串逐字符转成数字后用 pairwise 生成相邻对，再用 all 判断每一对的绝对差是否都不超过 2。
# 时间复杂度：O(n)，只扫描一遍；空间复杂度：O(n)，转换后的数字列表与相邻对生成器占用线性空间。
class Solution:  # LeetCode 约定的题解类
    def isAdjacentDiffAtMostTwo(self, s: str) -> bool:  # s：只含数字的字符串，返回是否所有相邻数字差都至多为 2
        return all(abs(x - y) <= 2 for x, y in pairwise(map(int, list(s))))  # 先 map(int, ...) 把字符转成数字，pairwise 生成相邻对，all 判断每对差值是否不超过 2
