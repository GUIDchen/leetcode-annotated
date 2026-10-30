# 题目：691. 贴纸拼词（Stickers to Spell Word）
# 思路：状态压缩 BFS。用 n 位掩码表示 target 中已拼出的位置，从 0 出发，每层尝试贴一张贴纸并按字母计数尽量覆盖未拼出的位置，首次到达全 1 掩码即最少贴纸数。
# 时间复杂度：O(2ⁿ · m · n)，m 为贴纸数、n 为目标串长度；空间复杂度：O(2ⁿ) 存访问标记与队列。
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:  # stickers 为可用贴纸列表，target 为要拼出的目标串，返回最少贴纸数
        n = len(target)  # n 是目标串长度，也是状态掩码的位数
        q = deque([0])  # BFS 队列，初始状态为掩码 0（一个字母都没拼出）
        vis = [False] * (1 << n)  # vis[mask] 标记该掩码是否已经入队，避免重复搜索
        vis[0] = True  # 起点状态标记为已访问
        ans = 0  # ans 记录当前已经使用的贴纸数
        while q:  # 队列非空就继续按层扩展
            for _ in range(len(q)):  # 只处理当前层的 len(q) 个状态，保证 ans 的层数语义正确
                cur = q.popleft()  # 取出队首状态（已拼出位置的掩码）
                if cur == (1 << n) - 1:  # 所有位置都已拼出，到达目标状态
                    return ans  # 当前层数就是最少贴纸数
                for s in stickers:  # 枚举每一张贴纸，尝试用它扩展状态
                    cnt = Counter(s)  # 统计这张贴纸里每个字母的个数
                    nxt = cur  # nxt 是贴上该贴纸后得到的新掩码
                    for i, c in enumerate(target):  # 按顺序扫描目标串的每一位
                        if (cur >> i & 1) == 0 and cnt[c] > 0:  # 该位尚未拼出，且贴纸里还有这个字母可用
                            cnt[c] -= 1  # 消耗一个该字母，同一张贴纸的字母不能重复使用
                            nxt |= 1 << i  # 把第 i 位置 1，表示该位置已拼出
                    if not vis[nxt]:  # 新状态若未访问过才入队，保证每个状态只扩展一次
                        vis[nxt] = True  # 标记新状态已访问
                        q.append(nxt)  # 新状态入队，留到下一层扩展
            ans += 1  # 当前层处理完毕，贴纸数加一
        return -1  # 队列耗尽仍未拼出目标串，返回 -1 表示无法完成
