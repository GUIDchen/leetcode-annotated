# 3666. Minimum Operations to Equalize Binary String（3666. 使二进制字符串全为 1 的最少操作次数）
# 核心思路：每次操作恰好翻转 k 位，状态只取决于 0 的个数且每次操作后 0 的个数落在区间 [l, r] 内，故以 0 的个数为结点做 BFS，用两个按奇偶分组的有序集合维护未访问状态并整段删除。
# 复杂度：时间 O(n log n)，空间 O(n)，其中 n 为字符串长度。
class Solution:  # 定义题解类
    def minOperations(self, s: str, k: int) -> int:  # 求把二进制串全部变成 1 的最少操作次数
        n = len(s)  # 字符串长度
        ts = [SortedSet() for _ in range(2)]  # 按 0 的个数的奇偶分成两个有序集合，存放尚未访问的状态
        for i in range(n + 1):  # 枚举所有可能的 0 的个数
            ts[i % 2].add(i)  # 按奇偶放入对应集合
        cnt0 = s.count('0')  # 统计初始 0 的个数
        ts[cnt0 % 2].remove(cnt0)  # 起点状态出集合，避免重复入队
        q = deque([cnt0])  # BFS 队列，元素为当前 0 的个数
        ans = 0  # 当前已进行的操作次数（即 BFS 层数）
        while q:  # 队列非空就继续扩展
            for _ in range(len(q)):  # 按层遍历，保证 ans 恰好等于层数
                cur = q.popleft()  # 取出队首状态
                if cur == 0:  # 已经全为 1
                    return ans  # 返回最少操作次数
                l = cur + k - 2 * min(cur, k)  # 一次操作后 0 的个数的下界：多翻 0、少翻 1
                r = cur + k - 2 * max(k - n + cur, 0)  # 一次操作后 0 的个数的上界：多翻 1、少翻 0
                t = ts[l % 2]  # 一次翻转必然改变 0 的个数的奇偶性，故取另一组集合
                j = t.bisect_left(l)  # 从下界开始寻找可达状态
                while j < len(t) and t[j] <= r:  # 扫描区间 [l, r] 内的所有未访问状态
                    q.append(t[j])  # 新状态入队
                    t.remove(t[j])  # 访问后立即从集合删除，每个状态只会入队一次
            ans += 1  # 本层处理完毕，操作次数加一
        return -1  # BFS 结束仍未到达全 1 状态，返回 -1
