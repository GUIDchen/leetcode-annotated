# 题目：3377. 使两个整数相等的数位操作（Digit Operations to Make Two Integers Equal）
# 思路：先用埃氏筛得到 1e5 以内的质数表（操作过程中不允许出现质数），把每个整数当节点、「某一位 ±1」当边（边权为目标数字），从 n 到 m 跑 Dijkstra，首次弹出 m 时的累计和即答案。
# 时间复杂度：O(V log V)，V = 1e5；空间复杂度：O(V)，用于质数表与访问集合。
import heapq  # 用堆实现 Dijkstra 所需的小根堆


class Solution:  # LeetCode 约定的题解类
    def __init__(self):  # 构造函数：只声明属性，真正的建表放在 run_sieve 里
        self.sieve = []  # 质数表：sieve[x] 为 True 表示 x 是质数（操作过程中禁止出现质数）

    def run_sieve(self):  # 埃氏筛预处理 1e5 以内的质数
        self.sieve = [True] * 100000  # 先假设 0..99999 全部是质数
        self.sieve[0], self.sieve[1] = False, False  # 0 和 1 不是质数，单独置 False
        for i in range(2, 100000):  # 从最小的质数 2 开始枚举
            if self.sieve[i]:  # i 仍是质数，就用它筛掉自己的倍数
                for j in range(2 * i, 100000, i):  # 从 2i 开始，步长为 i，覆盖所有倍数
                    self.sieve[j] = False  # i 的倍数一定是合数

    def solve(self, n, m):  # 在「非质数」构成的隐式图上跑 Dijkstra
        pq = []  # 小根堆，元素为 (累计和, 当前数字)
        heapq.heappush(pq, (n, n))  # 起点入堆，累计和初始为 n 本身（每次操作会把新数字累加进和里）
        visited = set()  # 已确定最短路的数字集合，用于出堆去重

        while pq:  # 堆不空就继续扩展
            sum_, cur = heapq.heappop(pq)  # 弹出累计和最小的状态：sum_ 是累计和，cur 是当前数字

            if cur in visited:  # cur 之前已出堆，这是更差的旧记录
                continue  # 跳过旧记录，避免重复扩展
            visited.add(cur)  # 第一次出堆即为最短路，标记已确定

            if cur == m:  # 首次弹出 m 时，累计和就是最小答案（Dijkstra 的贪心正确性）
                return sum_  # 返回累计和

            s = list(str(cur))  # 把数字拆成字符列表，便于逐位修改
            for i in range(len(s)):  # 枚举要修改的位
                c = s[i]  # 备份当前字符，改完这一位后要还原才能尝试其他位

                if s[i] < '9':  # 这一位可以加一（小于 '9'，保证不进位、位数不变）
                    s[i] = chr(ord(s[i]) + 1)  # 字符加一
                    next_ = int(''.join(s))  # 拼回整数，得到下一个数字
                    if not self.sieve[next_] and next_ not in visited:  # 新数字必须是合数（非质数）且还没有确定最短路
                        heapq.heappush(pq, (sum_ + next_, next_))  # 边权就是新数字本身，累计和增加后入堆
                    s[i] = c  # 还原该位，准备尝试减一

                if s[i] > '0' and not (i == 0 and s[i] == '1'):  # 可以减一：不能小于 '0'，且首位不能由 '1' 变成 '0'（否则少一位）
                    s[i] = chr(ord(s[i]) - 1)  # 字符减一
                    next_ = int(''.join(s))  # 拼回整数
                    if not self.sieve[next_] and next_ not in visited:  # 同样要求新数字是合数且未访问
                        heapq.heappush(pq, (sum_ + next_, next_))  # 累计和加上新数字后入堆
                    s[i] = c  # 还原该位，供下一轮循环使用

        return -1  # 堆空仍未到达 m，说明两点不可达

    def minOperations(self, n, m):  # LeetCode 入口：n 起点，m 目标
        self.run_sieve()  # 先建质数表，供后面 O(1) 查询
        if self.sieve[n] or self.sieve[m]:  # 起点或终点本身是质数时，第一步就非法，直接不可达
            return -1  # 返回 -1
        return self.solve(n, m)  # 在合数图上跑 Dijkstra 求最小操作和
