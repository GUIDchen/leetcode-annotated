# 题目：2698. 求一个整数的惩罚数（Find the Punishment Number of an Integer）
# 核心思路：枚举 i = 1..n，对 i*i 的十进制串用 DFS 枚举所有切分方式；若存在一种切分使各段之和等于 i，则 i 是惩罚数，把 i*i 累加进答案。
# 时间复杂度：O(n * 2^k)，k 为平方数位数（k <= 7）；空间复杂度：O(k)，递归深度等于位数。
class Solution:  # LeetCode 约定的题解类
    def punishmentNumber(self, n: int) -> int:  # n：上界；返回 1..n 中所有惩罚数的平方和
        def check(s: str, i: int, x: int) -> bool:  # s：平方数的字符串；i：当前切分起点；x：剩余还需要凑出的和
            m = len(s)  # 串长
            if i >= m:  # 已经切到字符串末尾
                return x == 0  # 剩余和恰好为 0 才算合法切分
            y = 0  # y：当前这一段的数值，从 0 开始累加
            for j in range(i, m):  # 枚举这一段的结束下标 j，段内容就是 s[i..j]
                y = y * 10 + int(s[j])  # 逐位把 s[i..j] 变成一个整数
                if y > x:  # 这一段已经超过剩余和，再往后拼只会更大
                    break  # 剪枝：不必继续延长这一段
                if check(s, j + 1, x - y):  # 递归处理剩下的后缀，剩余和减去当前段
                    return True  # 只要有一种切法成立就提前返回
            return False  # 所有切法都失败

        ans = 0  # ans：累加所有满足条件的 i*i
        for i in range(1, n + 1):  # 逐个枚举候选数 i
            x = i * i  # 候选平方数
            if check(str(x), 0, i):  # 判断它的十进制表示能否切成若干段且各段之和等于 i
                ans += x  # 是惩罚数，把平方累加进答案
        return ans  # 返回所有惩罚数的平方和
