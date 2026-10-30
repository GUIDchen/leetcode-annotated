# 题目：2612. 最少翻转操作数（Minimum Reverse Operations）
# 思路：BFS 求最少翻转次数；翻转只会在同奇偶的下标之间跳，用两个有序集合保存未访问下标，按可达区间批量取出并删除。
# 时间复杂度：O(n log n)，每个下标只被取出删除一次；空间复杂度：O(n)，答案数组与两个有序集合。
class Solution:  # LeetCode 约定的题解类
    def minReverseOperations(  # 返回每个下标变成 1 所需的最少操作数
        self, n: int, p: int, banned: List[int], k: int  # n 是长度，p 是起点，banned 是禁止下标，k 是翻转区间长度
    ) -> List[int]:  # 参数与返回值说明结束
        ans = [-1] * n  # ans：答案，-1 表示无法到达
        ans[p] = 0  # 起点 p 需要 0 次操作
        ts = [SortedSet() for _ in range(2)]  # 按下标奇偶分组的两个有序集合，保存尚未确定答案的下标
        for i in range(n):  # 把所有可用下标按奇偶入集合
            ts[i % 2].add(i)  # i 放进对应的奇偶集合
        ts[p % 2].remove(p)  # 起点已确定答案，从集合中删掉
        for i in banned:  # 处理被禁止的下标
            ts[i % 2].remove(i)  # 禁止下标不可达，直接删除
        ts[0].add(n)  # 加哨兵 n，避免 bisect_left 越界
        ts[1].add(n)  # 两个集合都要加哨兵
        q = deque([p])  # BFS 队列，从起点 p 开始
        while q:  # 队列非空就继续扩展
            i = q.popleft()  # 弹出队首下标
            mi = max(i - k + 1, k - i - 1)  # k 长翻转后能到达的最小下标
            mx = min(i + k - 1, n * 2 - k - i - 1)  # k 长翻转后能到达的最大下标
            s = ts[mi % 2]  # 翻转不改变下标奇偶性，取对应集合
            j = s.bisect_left(mi)  # 找到第一个 >= mi 的未访问位置
            while s[j] <= mx:  # 区间内（<= mx）的下标都能一步到达
                q.append(s[j])  # 新下标入队
                ans[s[j]] = ans[i] + 1  # BFS 层数 + 1 就是最少操作次数
                s.remove(s[j])  # 删除已访问的下标
                j = s.bisect_left(mi)  # 重新定位到下一个未访问位置
        return ans  # 返回每个下标的最少操作次数
