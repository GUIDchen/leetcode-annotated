# 题目：358. K 距离间隔重排字符串（Rearrange String k Distance Apart）
# 思路：用 Counter 统计词频，构造大根堆（存负数）每次取剩余最多的字符，并用长度 k 的队列冷却，保证同字符间隔至少 k。
# 时间复杂度：O(n + 26 log 26)，每个字符出堆入堆一次；空间复杂度：O(n + 26)，答案与堆/队列开销。
class Solution:  # LeetCode 题解类
    def rearrangeString(self, s: str, k: int) -> str:  # s 是原字符串，k 是相同字符间至少的间隔
        cnt = Counter(s)  # 统计每个字符的出现次数
        pq = [(-v, c) for c, v in cnt.items()]  # 建堆数组：取负数让 Python 小根堆变成大根堆
        heapify(pq)  # 原地堆化，规模仅 26
        q = deque()  # 冷却队列：刚用过的字符要等 k 步才能再用
        ans = []  # 收集答案字符
        while pq:  # 堆非空说明还有字符可用
            v, c = heappop(pq)  # 弹出剩余次数最多（负数最小）的字符
            ans.append(c)  # 该字符追加到答案
            q.append((v + 1, c))  # 负数加一等于剩余次数减一，再进冷却队列
            if len(q) >= k:  # 冷却队列达到 k 个，队首字符可以解冻
                e = q.popleft()  # 取出解冻的字符
                if e[0]:  # 剩余次数不为 0（负数非零）才放回堆
                    heappush(pq, e)  # 重新加入堆参与调度
        return "" if len(ans) < len(s) else "".join(ans)  # 长度不足说明间隔无解，否则拼接成字符串
