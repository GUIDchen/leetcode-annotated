# 题目：683. K 个关闭的灯泡（K Empty Slots）
# 思路：按天依次点亮灯泡，用树状数组统计区间内已点亮的灯泡数；每点亮位置 x，只需检查左右各 k+1 处是否已亮且中间没有别的亮灯。
# 时间复杂度：O(n log n)，每天一次树状数组更新与常数次前缀查询；空间复杂度：O(n)，树状数组与 vis 各占 O(n)。
class BinaryIndexedTree:  # 树状数组：支持单点加与前缀和查询
    def __init__(self, n):  # 构造函数：n 是下标上界（1..n）
        self.n = n  # 记录下标上界
        self.c = [0] * (n + 1)  # 下标从 1 开始使用，所以开 n+1 个位置

    def update(self, x, delta):  # 在位置 x 上加上 delta
        while x <= self.n:  # 沿树向上跳，直到超出上界
            self.c[x] += delta  # 把增量累加到覆盖 x 的节点
            x += x & -x  # x & -x 取出最低位的 1，跳到父节点

    def query(self, x):  # 查询位置 1..x 的前缀和
        s = 0  # 累加结果
        while x:  # 每次去掉最低位的 1，直到 x 变成 0
            s += self.c[x]  # 累加当前节点覆盖的区间和
            x -= x & -x  # 跳到前一个区间节点
        return s  # 返回 1..x 的累加和


class Solution:  # LeetCode 约定的题解类
    def kEmptySlots(self, bulbs: List[int], k: int) -> int:  # bulbs[i] 是第 i+1 天点亮的灯泡位置；k 是中间要求的空位数
        n = len(bulbs)  # 灯泡总数
        tree = BinaryIndexedTree(n)  # 建树状数组，统计已点亮的灯泡数量
        vis = [False] * (n + 1)  # 标记数组：vis[i] 表示位置 i 是否已点亮
        for i, x in enumerate(bulbs, 1):  # 天数从 1 开始编号，同时取出当天点亮的位置 x
            tree.update(x, 1)  # 在树状数组中给位置 x 加 1
            vis[x] = True  # 标记该位置已点亮
            y = x - k - 1  # 左侧候选的另一个亮灯位置：与 x 恰好隔 k 个空位
            if y > 0 and vis[y] and tree.query(x - 1) - tree.query(y) == 0:  # 左侧已亮，且 (y, x) 之间没有其他亮灯
                return i  # 第 i 天首次出现符合条件的情形
            y = x + k + 1  # 右侧候选的另一个亮灯位置
            if y <= n and vis[y] and tree.query(y - 1) - tree.query(x) == 0:  # 右侧已亮，且 (x, y) 之间没有其他亮灯
                return i  # 第 i 天首次出现符合条件的情形
        return -1  # 始终没有出现，返回 -1
