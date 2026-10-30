# 题目：2523. 范围内最接近的两个质数（Closest Prime Numbers in Range）
# 思路：先用线性筛筛出 [2, right] 的所有质数，再在落在 [left, right] 的质数中找相邻差最小的一对。
# 时间复杂度：O(right)，每个合数只被筛一次；空间复杂度：O(right)，标记数组与质数表。
class Solution:  # LeetCode 约定的题解类
    def closestPrimes(self, left: int, right: int) -> List[int]:  # left/right 是闭区间上下界，返回区间内最接近的两个质数
        cnt = 0  # 已筛出的质数个数，兼作质数表的写入下标
        st = [False] * (right + 1)  # st[i] 为 True 表示 i 是合数，初始全按质数处理
        prime = [0] * (right + 1)  # 质数表，按从小到大顺序存放筛出的质数
        for i in range(2, right + 1):  # 线性筛：从 2 枚举到 right
            if not st[i]:  # 没被标记为合数，说明 i 是质数
                prime[cnt] = i  # 把 i 写进质数表
                cnt += 1  # 质数个数加一
            j = 0  # 内层枚举质数表的下标，从最小的质数开始
            while prime[j] <= right // i:  # 用整数除法代替乘法，避免 prime[j]*i 超出上界
                st[prime[j] * i] = 1  # prime[j]*i 必为合数，标记掉
                if i % prime[j] == 0:  # prime[j] 恰好是 i 的最小质因子
                    break  # 每个合数只由它的最小质因子筛一次，立刻跳出内层 while
                j += 1  # 换下一个质数继续筛
        p = [v for v in prime[:cnt] if left <= v <= right]  # 切片取前 cnt 个质数，再筛出落在 [left, right] 的，它们仍升序
        mi = inf  # 当前最小间隔，初值为正无穷
        ans = [-1, -1]  # 默认答案：不足两个质数时返回 [-1, -1]
        for a, b in pairwise(p):  # pairwise 依次取出相邻的两个质数 (a, b)
            if (d := b - a) < mi:  # 海象运算符：先算出间隔 d，再判断是否更小
                mi = d  # 更新最小间隔
                ans = [a, b]  # 记录这一对更接近的质数
        return ans  # 返回间隔最小的一对质数
