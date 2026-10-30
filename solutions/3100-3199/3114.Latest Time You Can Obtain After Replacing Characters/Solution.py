# 题目：3114. 替换字符可以得到的最晚时间（Latest Time You Can Obtain After Replacing Characters）
# 思路：从最晚的 11:59 开始倒序枚举所有合法时刻，第一个与模式 s 兼容（非 '?' 的位置全部相同）的时刻就是答案。
# 时间复杂度：O(12 × 60 × 5) = O(1)，枚举次数固定；空间复杂度：O(1)，只用了常数级临时变量。
class Solution:  # LeetCode 约定的题解类
    def findLatestTime(self, s: str) -> str:  # s 是形如 "hh:mm" 的时间模式，'?' 表示该位可以替换
        for h in range(11, -1, -1):  # 小时从最晚的 11 倒序到 0（12 小时制）
            for m in range(59, -1, -1):  # 分钟从最晚的 59 倒序到 0
                t = f"{h:02d}:{m:02d}"  # 把当前时刻格式化成 "hh:mm"
                if all(a == b for a, b in zip(s, t) if a != "?"):  # 模式中所有确定的位都必须与当前时刻一致
                    return t  # 第一个兼容的时刻就是能得到的最大时间
