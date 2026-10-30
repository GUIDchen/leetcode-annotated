# 题目：649. Dota2 参议院（Dota2 Senate）
# 思路：用两个双端队列分别保存 Radiant 与 Dire 议员的生效下标，每轮取双方队首，下标小的一方先行动并禁言对手，胜者以「下标 + n」进入下一轮。
# 时间复杂度：O(n)，每个议员最多出队、入队各一次；空间复杂度：O(n)，两个队列合计最多存 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def predictPartyVictory(self, senate: str) -> str:  # senate 是议员序列（R 为 Radiant，D 为 Dire），返回获胜方
        qr = deque()  # 存放 Radiant 议员的生效下标
        qd = deque()  # 存放 Dire 议员的生效下标
        for i, c in enumerate(senate):  # 按原顺序遍历每位议员
            if c == "R":  # 当前是 Radiant 议员
                qr.append(i)  # 记录它的下标
            else:  # 否则是 Dire 议员
                qd.append(i)  # 记录它的下标
        n = len(senate)  # 议员总数，用「下标 + n」表示该议员在下一轮的位置
        while qr and qd:  # 双方都还有议员时继续对抗
            if qr[0] < qd[0]:  # Radiant 队首下标更小，本轮先行动并禁言对手
                qr.append(qr[0] + n)  # 胜者加上 n 排到下一轮队尾
            else:  # 否则 Dire 队首先行动
                qd.append(qd[0] + n)  # 胜者加上 n 排到下一轮队尾
            qr.popleft()  # 弹出本轮已处理完的 Radiant 队首（若它获胜，下一轮副本已排到队尾）
            qd.popleft()  # 弹出本轮已处理完的 Dire 队首（若它获胜，下一轮副本已排到队尾）
        return "Radiant" if qr else "Dire"  # Radiant 队列非空则 Radiant 获胜，否则 Dire 获胜
