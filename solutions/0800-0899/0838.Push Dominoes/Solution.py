# 题目：838. 推多米诺（Push Dominoes）
# 思路：把初始有方向的骨牌当作多源 BFS 起点，time 记录被推动的时刻，force 记录同一时刻作用方向；只有受力唯一时才真正倒下，同时刻受两向力则保持竖直。
# 时间复杂度：O(n)，每块骨牌最多入队常数次；空间复杂度：O(n)，time、force、ans 与队列各 O(n)。
class Solution:  # LeetCode 约定的题解类
    def pushDominoes(self, dominoes: str) -> str:  # dominoes 由 'L'、'R'、'.' 组成，返回所有推力传播结束后的状态
        n = len(dominoes)  # 骨牌数量
        q = deque()  # BFS 队列，按被推动的时刻逐层扩展
        time = [-1] * n  # time[i] 表示骨牌 i 被推动的时刻，-1 表示还没被推动
        force = defaultdict(list)  # force[i] 收集同一时刻作用到骨牌 i 上的所有方向
        for i, f in enumerate(dominoes):  # 枚举下标与字符，把初始有方向的骨牌作为多源 BFS 起点
            if f != '.':  # 只处理 'L' 与 'R'，竖直骨牌跳过
                q.append(i)  # 入队，等待它的力向外扩散
                time[i] = 0  # 初始时刻记为 0
                force[i].append(f)  # 把自身方向记为作用在它上面的一份力
        ans = ['.'] * n  # 最终状态先全部置为竖直
        while q:  # 队列非空说明还有力需要继续传播
            i = q.popleft()  # 取出队首骨牌
            if len(force[i]) == 1:  # 只有受力方向唯一时，这块骨牌才会真正倒下
                ans[i] = f = force[i][0]  # 取出唯一方向，并同时写进最终状态
                j = i - 1 if f == 'L' else i + 1  # 力向相邻骨牌传播：L 向左、R 向右
                if 0 <= j < n:  # 邻居下标必须仍在范围内
                    t = time[i]  # 当前骨牌被推动的时刻
                    if time[j] == -1:  # 邻居第一次被推，需要记录时刻并入队
                        q.append(j)  # 邻居入队，轮到它时再继续向外推
                        time[j] = t + 1  # 邻居被推动的时刻是当前时刻加一
                        force[j].append(f)  # 记录这一份方向力
                    elif time[j] == t + 1:  # 邻居恰好在同一时刻被反方向也推了一次
                        force[j].append(f)  # 两份力并存，邻居受力不唯一，最终保持竖直
        return ''.join(ans)  # 返回最终状态
