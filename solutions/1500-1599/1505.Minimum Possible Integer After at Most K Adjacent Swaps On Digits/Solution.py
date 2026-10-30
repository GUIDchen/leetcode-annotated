# 题目：1505. 最多 K 次交换相邻数位后得到的最小整数（Minimum Possible Integer After at Most K Adjacent Swaps On Digits）
# 思路：从左到右逐位贪心，10 个双端队列记录每个数字的原始位置，树状数组统计已固定数字带来的位移，选出负担得起的最小数字。
# 时间复杂度：O(10 * n log n)，每位最多试 10 个数字、每次一次树状数组查询；空间复杂度：O(n)。
class BinaryIndexedTree:  # 树状数组：单点加 + 前缀和查询，标记哪些原始位置已被取走
    def __init__(self, n):  # 构造函数，n 为下标上界（1-based）
        self.n = n  # 保存规模
        self.c = [0] * (n + 1)  # 数组开 n+1 个位置，全部清零

    @staticmethod  # 静态方法：不依赖实例状态
    def lowbit(x):  # 求 x 的最低位 1 所代表的数值
        return x & -x  # 位运算技巧：x 与 -x 相与只保留最低位的 1

    def update(self, x, delta):  # 在位置 x 上累加 delta
        while x <= self.n:  # 沿父结点方向向上更新
            self.c[x] += delta  # 累加增量
            x += BinaryIndexedTree.lowbit(x)  # 跳到下一个受影响的结点

    def query(self, x):  # 求前缀和 1..x
        s = 0  # 累加结果
        while x:  # x 降到 0 为止
            s += self.c[x]  # 累加当前结点负责的区间
            x -= BinaryIndexedTree.lowbit(x)  # 跳到前一个区间
        return s  # 返回前缀和


class Solution:  # LeetCode 约定的题解类
    def minInteger(self, num: str, k: int) -> str:  # num：数字字符串；k：最多允许的相邻交换次数；返回最小整数（字符串形式）
        pos = defaultdict(deque)  # pos[d] 是数字 d 的原始下标双端队列（1-based）
        for i, v in enumerate(num, 1):  # 下标从 1 开始，方便配合树状数组
            pos[int(v)].append(i)  # 记录每个数字出现的位置
        ans = []  # 逐位收集答案字符
        n = len(num)  # 数字长度
        tree = BinaryIndexedTree(n)  # 树状数组标记哪些原始位置已被取走
        for i in range(1, n + 1):  # 依次确定答案的第 i 位（1-based）
            for v in range(10):  # 贪心：从小到大尝试放哪个数字
                q = pos[v]  # 该数字还未使用的原始位置队列
                if q:  # 该数字还有剩余可用位置
                    j = q[0]  # 取它最靠前的一个位置
                    dist = tree.query(n) - tree.query(j) + j - i  # 估算交换次数：基准距离 j - i，再加上已取走元素（原本位于 j 右侧）带来的额外位移
                    if dist <= k:  # 剩余交换次数够把它移到第 i 位
                        k -= dist  # 扣掉本次交换消耗的次数
                        q.popleft()  # 该位置已被使用，出队
                        ans.append(str(v))  # 追加该数字到答案
                        tree.update(j, 1)  # 标记该位置已取走，供后续位修正位移
                        break  # 当前位已确定，跳出尝试循环
        return ''.join(ans)  # 拼接成字符串返回
