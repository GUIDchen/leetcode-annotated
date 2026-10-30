# 题目：2682. 找出转圈游戏输家（Find the Losers of the Circular Game）
# 思路：模拟传圈过程，每步按当前步数 p*k 在环上前进，用 vis 标记已接到球的人；一旦走到已标记的位置就停止，未被标记的人即为输家。
# 时间复杂度：O(n)，每人最多被标记一次；空间复杂度：O(n)，vis 列表记录是否接过球。
class Solution:  # LeetCode 约定的题解类
    def circularGameLosers(self, n: int, k: int) -> List[int]:  # n 是人数，k 是每轮步长的倍数
        vis = [False] * n  # vis[i] 表示编号 i+1 的人是否接到过球
        i, p = 0, 1  # i 是当前持球人下标，p 是本轮步长倍数，都从 0/1 开始
        while not vis[i]:  # 只要持球人还没接过球就继续传
            vis[i] = True  # 标记当前持球人已经接过球
            i = (i + p * k) % n  # 在环上向前走 p*k 步，取模实现循环
            p += 1  # 步长倍数递增，准备下一轮
        return [i + 1 for i in range(n) if not vis[i]]  # 用列表推导收集所有从未接过球的人的编号（i+1 才是题目编号）
