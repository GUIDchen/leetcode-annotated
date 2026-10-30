# 题目：3348. 最小可整除数位乘积 II（Smallest Divisible Digit Product II）
# 思路：把 t 分解为 2/3/5/7 的幂，用贪心折算成最少的数字（8、9、6、4、2、3、5、7），再从右往左尝试抬高某一位，后缀用最小数字排列补齐。
# 时间复杂度：O(n * 10)（n 为 num 长度）；空间复杂度：O(1)，只维护常数大小的计数数组。
class Solution:  # LeetCode 约定的题解类
    def smallestNumber(self, num: str, t: int) -> str:  # num：下界字符串（结果必须不小于它）；t：数位乘积必须是它的倍数
        digit_primes = [  # 数字 0~9 对应的 (2,3,5,7) 指数表
            [0, 0, 0, 0],  # 数字 0：无法参与乘积，占位为全 0
            [0, 0, 0, 0],  # 数字 1：单位元，不含任何素因子
            [1, 0, 0, 0],  # 数字 2 = 2^1
            [0, 1, 0, 0],  # 数字 3 = 3^1
            [2, 0, 0, 0],  # 数字 4 = 2^2
            [0, 0, 1, 0],  # 数字 5 = 5^1
            [1, 1, 0, 0],  # 数字 6 = 2 * 3
            [0, 0, 0, 1],  # 数字 7 = 7^1
            [3, 0, 0, 0],  # 数字 8 = 2^3
            [0, 2, 0, 0],  # 数字 9 = 3^2
        ]  # 指数表结束

        def factorize(target: int):  # 把 target 分解到 2、3、5、7 上
            counts = [0, 0, 0, 0]  # 四个素因子的指数
            for i, p in enumerate((2, 3, 5, 7)):  # 逐个素因子试除
                while target % p == 0:  # 还能整除就一直除下去
                    target //= p  # 整除一次，去掉一个素因子
                    counts[i] += 1  # 对应指数加一
            return counts, target == 1  # 返回指数表，以及 target 是否只剩 1（即只含这四个素因子）

        def subtract(a, b):  # 逐分量做 max(0, a - b)，算出还缺的指数
            return [max(0, x - y) for x, y in zip(a, b)]  # 只保留正的缺口部分

        def to_digits(primes):  # 把素因子指数折算成每个数字的最少使用个数
            count8 = primes[0] // 3  # 每 3 个 2 合成一个 8 最省位
            remaining2 = primes[0] % 3  # 剩下的 2 的指数（0~2）
            count9 = primes[1] // 2  # 每 2 个 3 合成一个 9 最省位
            count3 = primes[1] % 2  # 剩下的 3 的指数（0~1）
            count4 = remaining2 // 2  # 两个 2 合成一个 4
            count2 = remaining2 % 2  # 还剩一个 2 就用数字 2
            count6 = 0  # 数字 6 的个数先置 0
            if count2 == 1 and count3 == 1:  # 同时剩一个 2 和一个 3，合并成 6 可以省一位
                count2 = count3 = 0  # 链式赋值：2 和 3 都已经并入 6
                count6 = 1  # 使用一个数字 6
            if count3 == 1 and count4 == 1:  # 剩一个 3 和一个 4 时拆成 2 与 6 位数更少
                count2 = 1  # 数字 2 承担一个因子 2
                count6 = 1  # 数字 6 承担 2 * 3
                count3 = count4 = 0  # 链式赋值：3 和 4 都已经消掉
            return [  # 按数字 0~9 返回各自的使用个数
                0,  # 数字 0 不使用
                0,  # 数字 1 不使用（补位时另外添加）
                count2,  # 数字 2 的个数
                count3,  # 数字 3 的个数
                count4,  # 数字 4 的个数
                primes[2],  # 因子 5 只能由数字 5 提供，个数等于 5 的指数
                count6,  # 数字 6 的个数
                primes[3],  # 因子 7 只能由数字 7 提供，个数等于 7 的指数
                count8,  # 数字 8 的个数
                count9,  # 数字 9 的个数
            ]  # 返回列表结束

        def construct(digits) -> str:  # 把各数字的使用个数拼成字典序最小的字符串
            return "".join(str(d) * digits[d] for d in range(2, 10))  # 2 到 9 依次重复输出：位数相同时升序排列即字典序最小

        required, ok = factorize(t)  # 分解 t，ok 表示 t 是否只由 2/3/5/7 组成
        if not ok:  # 含有其他素因子
            return "-1"  # 任何数位乘积都无法满足要求
        need = to_digits(required)  # 只用 t 的需求时最少需要几位
        if sum(need) > len(num):  # 所需位数比原数还长
            return construct(need)  # 只能在更高位构造，输出最小数字排列

        prefix = [0, 0, 0, 0]  # 记录 num 已固定前缀的素因子指数累计值
        for ch in num:  # 遍历原串的每个字符
            d = ord(ch) - 48  # 字符转数字（'0' 的 ASCII 码是 48）
            for i in range(4):  # 逐个素因子累加
                prefix[i] += digit_primes[d][i]  # 把该数字的指数加进前缀
        first_zero = num.find("0")  # 找第一个 '0'：0 会让整个数位乘积变成 0
        if first_zero == -1:  # 不存在 0
            first_zero = len(num)  # 视作 0 出现在末尾之后，整串都可以保留
            if all(r <= p for r, p in zip(required, prefix)):  # num 自身的素因子已经覆盖 t 的全部要求
                return num  # 原数本身就是最小答案

        n = len(num)  # 原数长度
        for i in range(n - 1, -1, -1):  # 从右往左扫描，寻找「抬高第 i 位、后缀最小」的最优切点
            d = ord(num[i]) - 48  # 第 i 位的数字值
            prefix = subtract(prefix, digit_primes[d])  # 先把自己从前缀里去掉，prefix 变成 num[:i] 的指数
            space = n - 1 - i  # 位置 i 之后还可以自由填写的位数
            if i > first_zero:  # 超过第一个 0 的位置不能改，只能继续左移
                continue  # 跳到更左边的位置
            for bigger in range(d + 1, 10):  # 枚举把第 i 位换成更大的数字，保证结果仍不小于 num
                suffix = to_digits(  # 用剩余指数折算后缀的最小数字组合
                    subtract(subtract(required, prefix), digit_primes[bigger])  # 还缺的指数 = t 的需求 - 前缀已提供 - 新第 i 位提供
                )  # to_digits 调用结束
                if sum(suffix) <= space:  # 剩余数字能在后缀位数预算内放下
                    return (  # 组装答案并返回
                        num[:i]  # 保持与 num 相同的最长前缀
                        + str(bigger)  # 抬高的第 i 位
                        + "1" * (space - sum(suffix))  # 放不满的位数用 1 补齐，1 不改变数位乘积
                        + construct(suffix)  # 最后接上最小数字排列
                    )  # 表达式拼接结束
        ext = to_digits(required)  # 原长度内无解，需要加一位
        return "1" * (n + 1 - sum(ext)) + construct(ext)  # 加长一位：多出的高位用 1 填满，后面接最小数字排列
