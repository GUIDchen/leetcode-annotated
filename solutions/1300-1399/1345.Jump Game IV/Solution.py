# 题目：1345. 跳跃游戏 IV（Jump Game IV）
# 思路：等价于在图上做 BFS，相邻下标与「值相同」的下标之间连边；同值下标用 dict 分组，并在首次用尽后 pop 掉，避免重复枚举。
# 时间复杂度：O(n)，每个下标入队一次、同值边只展开一次；空间复杂度：O(n)，用于存分组表、访问集合与队列。
class Solution:  # LeetCode 约定的题解类
    def minJumps(self, arr: List[int]) -> int:  # arr 是输入数组，返回从 0 跳到末尾的最少步数
        g = defaultdict(list)  # g[x] 保存所有值为 x 的下标，等价于图里的同值跳转边
        for i, x in enumerate(arr):  # 一次线性扫描，按值分组
            g[x].append(i)  # 把下标 i 加入值 x 的分组
        q = deque([0])  # BFS 队列，从起点 0 开始
        vis = {0}  # vis 记录已入队的下标，防止重复访问
        ans = 0  # ans 记录当前已经跳过的步数（BFS 层数）
        while 1:  # 终点必然可达，所以写成 while 1 死循环，靠 return 退出
            for _ in range(len(q)):  # 只处理当前这一层，range(len(q)) 在进入循环时就确定了层大小
                i = q.popleft()  # 取出队首下标
                if i == len(arr) - 1:  # 到达末尾说明找到了最短步数
                    return ans  # 直接返回当前层数（即步数）
                for j in (i + 1, i - 1, *g.pop(arr[i], [])):  # 候选下一步：i+1、i-1，以及所有同值下标；g.pop 取出后删除该键，保证同值边总共只展开一次
                    if 0 <= j < len(arr) and j not in vis:  # 筛选：下标在范围内且未访问过
                        q.append(j)  # 入队等待下一层处理
                        vis.add(j)  # 同时标记为已访问
            ans += 1  # 本层处理完，步数加一
