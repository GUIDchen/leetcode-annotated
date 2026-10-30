# 题目：2001. 可互换矩形的组数（Number of Pairs of Interchangeable Rectangles）
# 思路：把每个矩形的宽高比约分成最简分数，用计数器统计相同比例出现的次数，每遇到一个就与之前所有同比例矩形配对。
# 时间复杂度：O(n log C)，每次求一次 gcd；空间复杂度：O(n)，计数器存放不同比例的计数。
class Solution:  # LeetCode 约定的题解类
    def interchangeableRectangles(self, rectangles: List[List[int]]) -> int:  # rectangles：每个元素是 [宽, 高]
        ans = 0  # ans 统计可互换矩形对数
        cnt = Counter()  # 键是约分后的比例 (w, h)，值是这种比例已出现的次数
        for w, h in rectangles:  # 逐个枚举矩形，解包出宽与高
            g = gcd(w, h)  # 求宽高的最大公因数，用于约分
            w, h = w // g, h // g  # 把宽高同时除以 g 化为最简分数，比例保持不变
            ans += cnt[(w, h)]  # 当前矩形能与之前所有同比例的矩形配对，累加对数
            cnt[(w, h)] += 1  # 把当前矩形计入该比例的出现次数
        return ans  # 返回可互换矩形的总组数
