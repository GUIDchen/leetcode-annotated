# 题目：636. 函数的独占时间（Exclusive Time of Functions）
# 思路：用栈模拟调用：遇到 start 先结算栈顶函数的时间再压栈；遇到 end 弹栈并结算，end 的时间点 +1 表示区间闭合。
# 时间复杂度：O(L)，L 为日志条数；空间复杂度：O(n)，栈深最多 n。
class Solution:  # LeetCode 约定的题解类
    def exclusiveTime(self, n: int, logs: List[str]) -> List[int]:  # n 是函数个数，logs 是调用日志，返回每个函数的独占时间
        stk = []  # 调用栈，栈顶是当前正在执行的函数 id
        ans = [0] * n  # ans[i] 记录第 i 个函数的独占时间
        pre = 0  # 下一个待结算的时间点
        for log in logs:  # 按时间顺序处理每条日志
            i, op, t = log.split(":")  # 按冒号切成三段：函数 id、操作名、时间戳（三者都是字符串）
            i, cur = int(i), int(t)  # 把 id 与时间戳转成整数，操作名保持字符串
            if op[0] == "s":  # 首字母是 s 说明是 start 日志
                if stk:  # 栈非空说明有父函数正在执行，被子调用打断
                    ans[stk[-1]] += cur - pre  # 把 pre 到 cur 这段时间累加给父函数
                stk.append(i)  # 当前函数开始执行，压栈成为新的栈顶
                pre = cur  # 结算位置推进到本条日志的时间点
            else:  # 否则是 end 日志
                ans[stk.pop()] += cur - pre + 1  # 栈顶函数执行到 cur（含时间点 cur），所以要 +1；pop 同时出栈
                pre = cur + 1  # 下一个时间点从 cur+1 开始
        return ans  # 返回每个函数的独占时间
