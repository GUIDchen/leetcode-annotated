# 题目：3145. 大数组元素的乘积（Find Products of Elements of Big Array）
# 思路：大数组把每个正整数 x 的二进制位按 2 的幂依次铺开；预处理前缀表 cnt（元素个数）与 s（指数和），二分定位端点所在的数，累加区间内的指数和，再求 2^指数和 mod mod。
# 时间复杂度：O(log^2C)，每次查询二分加按位统计；空间复杂度：O(m)，只有 m + 1 大小的常数表。
m = 50  # m：最大位宽，1 << m 已覆盖查询涉及的范围
cnt = [0] * (m + 1)  # cnt[i]：数字 1..2^i-1 的二进制总位数（即大数组中的元素个数）
s = [0] * (m + 1)  # s[i]：数字 1..2^i-1 的二进制指数总和
p = 1  # p：滚动保存 2^(i-1)，即当前最高位的位权
for i in range(1, m + 1):  # 递推预处理 i = 1..m
    cnt[i] = cnt[i - 1] * 2 + p  # 两个长度 i-1 的半段拼起来，再加新增最高位的 p 个 1
    s[i] = s[i - 1] * 2 + p * (i - 1)  # 新增的最高位共 p 个，每个贡献指数 i-1
    p *= 2  # 位权翻倍，供下一轮使用


def num_idx_and_sum(x: int) -> tuple:  # 求数字 1..x 在大数组中贡献的（元素个数, 指数总和）
    idx = 0  # idx：累计的元素个数
    total_sum = 0  # total_sum：累计的指数总和
    while x:  # 不断剥掉当前最高位，一段一段地处理
        i = x.bit_length() - 1  # i：x 的最高位位置（bit_length - 1）
        idx += cnt[i]  # 1..2^i-1 已被完整覆盖，累加其元素个数
        total_sum += s[i]  # 同理累加其指数总和
        x -= 1 << i  # 去掉最高位，x 变成剩下的低位部分
        total_sum += (x + 1) * i  # 剩余 x+1 个数都带最高位 i，每个贡献指数 i
        idx += x + 1  # 每个这样的数还多出一个元素（最高位本身）
    return (idx, total_sum)  # 返回（元素个数, 指数总和）


def f(i: int) -> int:  # f(i)：大数组前 i 个元素的指数总和
    l, r = 0, 1 << m  # 二分区间：最多用到 2^m 个数
    while l < r:  # 找最大的 l，使前 l 个完整数字贡献的元素数 < i
        mid = (l + r + 1) >> 1  # 取上中位，保证区间单调收敛
        idx, _ = num_idx_and_sum(mid)  # 计算 mid 对应的前缀信息
        if idx < i:  # 前缀不足 i 个元素，答案在右半区
            l = mid  # 右移左界
        else:
            r = mid - 1  # 否则收缩右界

    total_sum = 0  # 占位初始化，真正的值由下一行重新绑定
    idx, total_sum = num_idx_and_sum(l)  # 取前 l 个完整数字的元素个数与指数和
    i -= idx  # i 变成还要从数字 l+1 中取的位数
    x = l + 1  # 接下来处理的是数字 l+1
    for _ in range(i):  # 按从低到高的顺序取出还需要的那 i 个元素
        y = x & -x  # y：x 的最低位 1 所对应的值
        total_sum += y.bit_length() - 1  # 该位对应的指数 = bit_length - 1
        x -= y  # 删掉这一位，继续取下一个
    return total_sum  # 返回大数组前 i 个元素（函数入参）的指数总和


class Solution:  # LeetCode 约定的题解类
    def findProductsOfElements(self, queries: List[List[int]]) -> List[int]:  # queries 的每个元素是 [left, right, mod]
        return [pow(2, f(right + 1) - f(left), mod) for left, right, mod in queries]  # 区间指数和 = f(right+1) - f(left)，再求 2^该和 mod mod
