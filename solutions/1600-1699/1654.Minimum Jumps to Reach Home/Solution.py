# 题目：1654. 到家的最少跳跃次数（Minimum Jumps to Reach Home）
# 思路：BFS 按跳跃次数分层搜索，状态为 (位置, 状态位)，状态位区分上一步是前进还是后退；位置限制在 [0, 6000) 内避免无限搜索。
# 时间复杂度：O(n)，n 为位置上界 6000，每个状态最多入队一次；空间复杂度：O(n)，visited 集合与队列。
class Solution:  # LeetCode 约定的题解类
    def minimumJumps(self, forbidden: List[int], a: int, b: int, x: int) -> int:  # forbidden 是禁区，a 前进距离，b 后退距离，x 是目标位置
        s = set(forbidden)  # 禁区转成集合，便于 O(1) 判禁
        q = deque([(0, 1)])  # BFS 队列，元素是 (位置, 状态位)，状态位 1 表示允许后退
        vis = {(0, 1)}  # 已访问集合，起点 (0,1) 直接标记
        ans = 0  # 当前层对应的跳跃次数
        while q:  # 队列非空就继续按层扩展
            for _ in range(len(q)):  # 只处理当前层，保证 ans 等于层数
                i, k = q.popleft()  # 取出队头状态
                if i == x:  # 到达目标位置
                    return ans  # 当前层数就是最少跳跃次数
                nxt = [(i + a, 1)]  # 候选下一步：总能前进到 i+a，状态位重置为 1
                if k & 1:  # 状态位为奇数说明上一步是前进，允许这次后退
                    nxt.append((i - b, 0))  # 追加后退到 i-b，状态位 0 表示下一步不能再后退
                for j, k in nxt:  # 枚举候选状态
                    if 0 <= j < 6000 and j not in s and (j, k) not in vis:  # 位置合法：非负、未越上界、不是禁区、状态没访问过
                        q.append((j, k))  # 入队，等下一层处理
                        vis.add((j, k))  # 同时标记已访问，防止重复入队
            ans += 1  # 一层处理完，跳跃次数加一
        return -1  # 队列空了仍未到家，说明不可达
