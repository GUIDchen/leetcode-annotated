# 题目：299. 猜数字游戏（Bulls and Cows）
# 思路：同位置数字相同就是公牛（A）；其余位置分别统计各数字出现次数，对每种数字取两串次数的较小值累加即奶牛（B）。
# 时间复杂度：O(n + 10)，n 为数字串长度；空间复杂度：O(1)，只用两个计数器。
class Solution:  # LeetCode 约定的题解类
    def getHint(self, secret: str, guess: str) -> str:  # secret：答案数字串；guess：猜测数字串
        cnt1, cnt2 = Counter(), Counter()  # 两个计数器：统计尚未配对数字的出现次数
        x = 0  # 公牛（位置和数字都相同）的数量
        for a, b in zip(secret, guess):  # 用 zip 逐位同时取出两个串的字符
            if a == b:  # 同位置数字相同，是一只公牛
                x += 1  # 公牛数加一
            else:  # 否则各自计数，留待后面配对成奶牛
                cnt1[a] += 1  # 记录 secret 中该数字的出现次数
                cnt2[b] += 1  # 记录 guess 中该数字的出现次数
        y = sum(min(cnt1[c], cnt2[c]) for c in cnt1)  # 对每种数字取两串次数的较小值，求和即奶牛数
        return f"{x}A{y}B"  # 按「xAyB」的格式格式化输出
