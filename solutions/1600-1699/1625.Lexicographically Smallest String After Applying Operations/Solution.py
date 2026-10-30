# 题目：1625. 执行操作后字典序最小的字符串（Lexicographically Smallest String After Applying Operations）
# 思路：把字符串当作状态做 BFS，每次扩展「奇数位数字加 a」和「右轮转 b 位」两种操作，用集合去重，过程中取字典序最小者。
# 时间复杂度：O(n·10·n/b) 级别，状态数为轮转次数与数字组合数之积；空间复杂度：O(状态数)，用于集合与队列。
class Solution:  # LeetCode 约定的题解类
    def findLexSmallestString(self, s: str, a: int, b: int) -> str:  # s 为初始字符串，a 为加在奇数位上的数字，b 为轮转步长
        q = deque([s])  # BFS 队列，从初始串出发（deque 由判题环境提供）
        vis = {s}  # 访问集合，记录出现过的串，避免重复搜索
        ans = s  # 答案初始化为原串
        while q:  # 队列不空就继续扩展状态
            s = q.popleft()  # 取出队首状态（popleft 比 list.pop(0) 更高效）
            if ans > s:  # 当前串的字典序更小
                ans = s  # 更新答案
            t1 = ''.join(  # 第一种操作：对奇数位数字加 a，先写生成表达式再 join 成串
                [str((int(c) + a) % 10) if i & 1 else c for i, c in enumerate(s)]  # 偶数位原样保留（i & 1 为 0），奇数位取 (数字 + a) % 10
            )  # 括号折行结束，得到操作一的结果串
            t2 = s[-b:] + s[:-b]  # 第二种操作：把后 b 个字符移到前面，即右轮转 b 位
            for t in (t1, t2):  # 依次尝试两种新状态
                if t not in vis:  # 只有没出现过的状态才入队
                    vis.add(t)  # 标记为已访问
                    q.append(t)  # 加入队列等待扩展
        return ans  # 返回搜索过程中得到的最小字典序串
