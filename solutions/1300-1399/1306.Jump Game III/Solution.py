# 题目：1306. 跳跃游戏 III（Jump Game III）
# 核心思路：把下标看成图节点，从 start 出发 BFS，能到达值为 0 的下标即成功；访问过的下标改为 -1 去重。
# 时间复杂度：O(n)，每个下标最多入队一次；空间复杂度：O(n)，队列最多存放 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def canReach(self, arr: List[int], start: int) -> bool:  # arr 是跳跃数组，start 是起点下标
        q = deque([start])  # 双端队列作为 BFS 队列，初始只有起点
        while q:  # 队列非空就继续搜索
            i = q.popleft()  # 取出队首下标（这里是必要的出队操作）
            if arr[i] == 0:  # 到达值为 0 的格子，成功
                return True  # 立即返回真
            x = arr[i]  # 记下当前格子允许的跳跃步数
            arr[i] = -1  # 置为 -1 标记已访问，防止重复入队
            for j in (i + x, i - x):  # 枚举向右、向左两个落点
                if 0 <= j < len(arr) and arr[j] >= 0:  # 落点未越界且未被访问过
                    q.append(j)  # 把合法落点加入队列
        return False  # 所有可达位置都搜完仍未遇到 0，返回失败
