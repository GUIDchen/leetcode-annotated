# 题目：2059. 转化数字的最小运算数（Minimum Operations to Convert Number）
# 思路：BFS 求最短路。状态是当前数值 x，每一步可以选 nums 中任一数与 x 做加、减、异或；越界或已访问的数值不再入队。
# 时间复杂度：O(1000 * n)，状态数被限制在 [0, 1000]；空间复杂度：O(1000)，访问数组与队列的开销。
class Solution:  # LeetCode 约定的题解类
    def minimumOperations(self, nums: List[int], start: int, goal: int) -> int:  # nums：可用操作数；start：起点；goal：目标值
        op1 = lambda x, y: x + y  # 加法运算
        op2 = lambda x, y: x - y  # 减法运算
        op3 = lambda x, y: x ^ y  # 按位异或运算
        ops = [op1, op2, op3]  # 三种运算放进列表，方便统一枚举
        vis = [False] * 1001  # 标记 0..1000 内每个数值是否已经入队，避免重复搜索
        q = deque([(start, 0)])  # BFS 队列，元素是（当前数值, 已用步数）
        while q:  # 队列非空就继续扩展
            x, step = q.popleft()  # 弹出队首状态：当前数值与步数
            for num in nums:  # 枚举可以使用的操作数
                for op in ops:  # 枚举三种运算
                    nx = op(x, num)  # 计算一步之后得到的新数值
                    if nx == goal:  # 一步之后直接命中目标
                        return step + 1  # 这一步也要计入，所以返回步数加一
                    if 0 <= nx <= 1000 and not vis[nx]:  # 只有落在合法范围内且未访问过的状态才入队
                        q.append((nx, step + 1))  # 新状态入队，步数加一
                        vis[nx] = True  # 标记已访问，防止重复搜索
        return -1  # 搜不到目标，返回 -1
