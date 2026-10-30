# 题目：1742. 盒子中小球的最大数量（Maximum Number of Balls in a Box）
# 思路：小球编号的数位和就是它要放的盒子编号，用桶数组统计每个盒子的球数，最后取桶里的最大值。
# 时间复杂度：O((highLimit-lowLimit+1)*log highLimit)，每个数只拆它的十进制位；空间复杂度：O(1)，桶数组固定 50 个元素。
class Solution:  # LeetCode 约定的题解类
    def countBalls(self, lowLimit: int, highLimit: int) -> int:  # 统计编号区间内小球放入盒子后的最大球数
        cnt = [0] * 50  # 桶数组：下标是数位和（即盒子编号），值是该盒子里的球数；最大数位和 9*5=45，50 足够
        for x in range(lowLimit, highLimit + 1):  # 逐个处理编号为 x 的小球（右端开区间，故写 +1）
            y = 0  # y 用来累加 x 的十进制数位和
            while x:  # 反复取末位并右移一位，x 变成 0 时结束
                y += x % 10  # 取出当前最低位并累加到数位和
                x //= 10  # 整除 10，相当于整体右移一位；这里直接修改循环变量即可
            cnt[y] += 1  # 该盒子的小球数加一
        return max(cnt)  # 返回所有盒子中球数最多的那个数量
