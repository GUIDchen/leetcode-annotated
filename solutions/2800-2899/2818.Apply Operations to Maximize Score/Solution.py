# 题目：2818. 操作使得分最大（Apply Operations to Maximize Score）
# 思路：每个数的「价值」是它的不同质因数个数。先用单调栈求每个下标作为区间价值最大值时能覆盖的左右边界，得到它可选的次数 (i-l)*(r-i)；再按数值降序贪心，用带模快速幂把价值累乘进答案，直到 k 次用完。
# 时间复杂度：O(n·log V + n·log n)，质因数分解与排序为主；空间复杂度：O(n)，存三元组、左右边界与单调栈。
def primeFactors(n):  # 辅助函数：用试除法求 n 的不同质因数个数
    i = 2  # 从最小的质数 2 开始试
    ans = set()  # 集合去重：同一个质因数只计一次
    while i * i <= n:  # 只需试到 sqrt(n)
        while n % i == 0:  # 反复除掉当前质因数
            ans.add(i)  # 记录该质因数
            n //= i  # 从 n 中除掉 i
        i += 1  # 换下一个因数
    if n > 1:  # 剩下的 n 本身就是一个大质因数
        ans.add(n)  # 也计入
    return len(ans)  # 返回不同质因数个数


class Solution:  # LeetCode 约定的题解类
    def maximumScore(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：最多操作次数；返回最大得分（对 1e9+7 取模）
        mod = 10**9 + 7  # 取模常量
        arr = [(i, primeFactors(x), x) for i, x in enumerate(nums)]  # 预处理成 (下标, 价值, 数值) 三元组
        n = len(nums)  # 数组长度

        left = [-1] * n  # left[i]：左边第一个价值严格更大的下标，-1 表示没有
        right = [n] * n  # right[i]：右边第一个价值大于等于它的下标，n 表示没有
        stk = []  # 单调栈，保存还没确定边界的位置
        for i, f, x in arr:  # 从左往右求左边界
            while stk and stk[-1][0] < f:  # 栈顶价值更小就弹出，栈保持价值递减
                stk.pop()  # 弹出栈顶
            if stk:  # 栈非空，栈顶就是左边第一个价值更大的位置
                left[i] = stk[-1][1]  # 记录左边界
            stk.append((f, i))  # 把 (价值, 下标) 压栈

        stk = []  # 清空栈，改从右往左求右边界
        for i, f, x in arr[::-1]:  # 逆序遍历，拿到下标、价值与原值
            while stk and stk[-1][0] <= f:  # 注意用 <=：价值相等时也要让位，避免重复计数
                stk.pop()  # 弹出栈顶
            if stk:  # 栈非空，栈顶就是右边第一个价值不小于它的位置
                right[i] = stk[-1][1]  # 记录右边界
            stk.append((f, i))  # 压栈继续向左

        arr.sort(key=lambda x: -x[2])  # 按数值降序排序：先取大的数，乘积才最大
        ans = 1  # 答案从 1 开始连乘
        for i, f, x in arr:  # 依次按数值从大到小取用
            l, r = left[i], right[i]  # 取出左右边界
            cnt = (i - l) * (r - i)  # 以 i 为区间最大值的连续子数组个数，即可选次数
            if cnt <= k:  # 剩余次数足够用完这个数的全部可选次数
                ans = ans * pow(x, cnt, mod) % mod  # 内置 pow 三参数版本：带模快速幂
                k -= cnt  # 扣掉已用次数
            else:  # 次数不够，只能再用 k 次，用完直接结束
                ans = ans * pow(x, k, mod) % mod  # 用完剩余的 k 次
                break  # 跳出循环
        return ans  # 返回最大得分
