# 题目：2584. 分割数组使乘积互质（Split the Array to Make Coprime Products）
# 思路：对每个数质因数分解，first 记录质因子首次出现的下标，last[i] 记下标 i 的质因子最远延伸位置；再从左往右扫描并维护最远覆盖 mx，出现 mx < i 即左右两段互质，返回 i。
# 时间复杂度：O(n * sqrt(maxVal)) 的分解代价；空间复杂度：O(n + 质因子种类数)。
class Solution:  # LeetCode 约定的题解类
    def findValidSplit(self, nums: List[int]) -> int:  # nums 为输入数组；返回合法分割点，不存在返回 -1
        first = {}  # 质因子 → 它第一次出现的下标
        n = len(nums)  # 数组长度
        last = list(range(n))  # last[i]：下标 i 的质因子们最远出现到的下标，初始为自己
        for i, x in enumerate(nums):  # 从左到右分解每个数
            j = 2  # 试除因子从 2 开始
            while j <= x // j:  # 只试除到 sqrt(x)，用整除避免浮点误差
                if x % j == 0:  # j 是 x 的一个质因子
                    if j in first:  # 该质因子之前出现过
                        last[first[j]] = i  # 更新它首次出现位置能延伸到的右端点
                    else:  # 该质因子首次出现
                        first[j] = i  # 记录首次出现的下标
                    while x % j == 0:  # 把因子 j 从 x 中除干净
                        x //= j  # 去掉一个 j
                j += 1  # 继续试下一个因子
            if x > 1:  # 剩下的 x>1 说明它本身是最后一个质因子
                if x in first:  # 这个质因子之前出现过
                    last[first[x]] = i  # 同样更新右端点
                else:  # 首次出现
                    first[x] = i  # 记录首次出现的下标
        mx = last[0]  # mx：前缀 [0..i] 中所有质因子能延伸到的最远下标
        for i, x in enumerate(last):  # 从左往右找第一个可以切开的位置
            if mx < i:  # 前缀的最远延伸仍在本位置左侧，说明已与右侧无公共质因子
                return mx  # 切在 mx 处即合法分割点
            mx = max(mx, x)  # 否则把当前位置的延伸距离并入 mx
        return -1  # 整个数组都连在一起，无法分割
