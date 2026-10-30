# 3433. Count Mentions Per User / 3433. 统计用户被提及情况
# 核心思路：按 (时间戳, 事件类型第三个字符) 排序后线性扫描，用 online_t 记下线时间、lazy 延迟累计 @all。
# 复杂度：时间 O(n log n + m * n)，空间 O(n)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def countMentions(self, numberOfUsers: int, events: List[List[str]]) -> List[int]:  # 返回每个用户被提及的次数
        events.sort(key=lambda e: (int(e[1]), e[0][2]))  # 按 (时间戳, 事件类型第三个字符) 升序排序，同一时刻先处理 OFFLINE
        ans = [0] * numberOfUsers  # 每个用户的提及计数
        online_t = [0] * numberOfUsers  # 每个用户的下线时刻，0 表示当前仍在线
        lazy = 0  # 延迟累计的 @all 提及次数
        for etype, ts, s in events:  # 按时间顺序处理每个事件
            cur = int(ts)  # 当前事件时间戳
            if etype[0] == "O":  # OFFLINE 事件：该用户下线，在线状态保持到 cur + 60
                online_t[int(s)] = cur + 60  # 记录该用户编号的下线时刻
            elif s[0] == "A":  # MESSAGE 事件中提到所有人
                lazy += 1  # 先累计到 lazy，最后统一结算给所有用户
            elif s[0] == "H":  # MESSAGE 事件中提到在线用户 HERE
                for i, t in enumerate(online_t):  # 遍历所有用户及其下线时刻
                    if t <= cur:  # 该用户事发时在线
                        ans[i] += 1  # 该用户被提及，计数加一
            else:  # 其余 MESSAGE 事件：提及具体的用户编号列表
                for a in s.split():  # 按空白拆分出每个提及项
                    ans[int(a[2:])] += 1  # 去掉 id 前缀，取用户编号并累加提及次数
        if lazy:  # 存在 @all 提及需要统一结算
            for i in range(numberOfUsers):  # 遍历所有用户
                ans[i] += lazy  # 把 lazy 次 @all 提及补加给每个用户
        return ans  # 返回每个用户的提及次数
