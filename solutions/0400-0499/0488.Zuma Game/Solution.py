# 题目：488. 祖玛游戏（Zuma Game）
# 思路：把 (桌面串, 手中球) 当作状态做 BFS，每层尝试「用掉一颗球插到桌面某个位置」并反复消去连续 ≥3 的同色球，第一次消空桌面时的层数即最少用球数。
# 时间复杂度：O(|hand|! × |board|²) 级别的搜索（状态数受球数与桌面长度限制）；空间复杂度：O(状态数)，visited 与队列的规模。
class Solution:  # LeetCode 约定的题解类
    def findMinStep(self, board: str, hand: str) -> int:  # board：初始桌面串；hand：手中的球；返回最少用球数，无法消空则返回 -1
        def remove(s):  # 内部函数：反复模拟「连续 3 个及以上同色即消除」直到不再变化
            while len(s):  # 只要串还没被消空就继续尝试消除
                next = re.sub(r'B{3,}|G{3,}|R{3,}|W{3,}|Y{3,}', '', s)  # 正则一次性删掉所有 B/G/R/W/Y 的连续 3 个及以上；next 作为临时变量（这里遮蔽了内置函数名，不影响本题逻辑）
                if len(next) == len(s):  # 长度没变说明本轮没有任何消除，连锁反应结束
                    break  # 跳出循环
                s = next  # 把消除后的串作为下一轮的输入，继续检查新的连锁消除
            return s  # 返回彻底稳定（无法再消）的串

        visited = set()  # visited 记录已经出现过的桌面串，避免同一局面重复入队
        q = deque([(board, hand)])  # BFS 队列：元素是 (当前桌面串, 剩余手牌串)，用剩余球数反推已用球数
        while q:  # 队列非空就继续按层扩展
            state, balls = q.popleft()  # 取出一层中的一个状态
            if not state:  # 桌面被消空，说明已经成功
                return len(hand) - len(balls)  # 已用球数 = 初始球数 - 剩余球数，BFS 保证这是最少的
            for ball in set(balls):  # 用 set 去重：同色球使用顺序不影响结果，每种颜色只试一次
                b = balls.replace(ball, '', 1)  # 从剩余手牌里真的去掉一颗该颜色的球（replace 第三个参数 1 表示只替换一次）
                for i in range(1, len(state) + 1):  # 枚举插入位置：从最左端一直试到最右端之后
                    s = state[:i] + ball + state[i:]  # 把球插到下标 i 的位置（切片拼接，不改动原串）
                    s = remove(s)  # 插入后立刻做连锁消除
                    if s not in visited:  # 这个新局面之前没见过
                        visited.add(s)  # 标记为已访问，防止重复搜索
                        q.append((s, b))  # 把新局面与更新后的手牌一起入队
        return -1  # 队列搜完仍未消空，说明无解
