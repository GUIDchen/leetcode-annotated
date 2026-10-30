# 题目：2327. 知道秘密的人数（Number of People Aware of a Secret）
# 思路：cnt[i] 记第 i 天新知道秘密的人数，d 是“当天知道秘密人数”的差分数组：
#       第 i 天学到的人在 d[i] 加上、在 d[i+forget] 减去，并在 [i+delay, i+forget) 内继续传染；时间 O(n²)，空间 O(n)。
class Solution:  # LeetCode 约定的题解类
    def peopleAwareOfSecret(self, n: int, delay: int, forget: int) -> int:  # n 是求答案的第 n 天；delay 天后才会传播；forget 天后忘记秘密
        m = (n << 1) + 10  # 数组上界：天数最多到 n + forget，取 2n + 10 一定够用
        d = [0] * m  # d 是“知道秘密人数”的差分数组
        cnt = [0] * m  # cnt[i] 表示第 i 天新知道秘密的人数
        cnt[1] = 1  # 第 1 天只有最初的那 1 个人知道秘密
        for i in range(1, n + 1):  # 按天数从小到大递推，保证处理第 i 天时它的传染源都已被统计
            if cnt[i]:  # 第 i 天没有人新知道秘密就跳过，省掉无效计算
                d[i] += cnt[i]  # 这批人从第 i 天起知道秘密，差分数组在起点加上人数
                d[i + forget] -= cnt[i]  # 这批人第 i + forget 天忘记秘密，差分数组在终点减掉人数
                nxt = i + delay  # 秘密需要过 delay 天才能传播，第一个可传染的日子
                while nxt < i + forget:  # 一直传播到他们忘记秘密之前（不含 i + forget 那天）
                    cnt[nxt] += cnt[i]  # 第 nxt 天新知道秘密的人数累加上这批传染者
                    nxt += 1  # 推进到下一天继续传播
        mod = 10**9 + 7  # 结果取模的常量
        return sum(d[: n + 1]) % mod  # 差分数组前 n+1 项之和即第 n 天仍知道秘密的人数，取模后返回
