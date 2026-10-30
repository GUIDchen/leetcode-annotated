# 题目：752. 打开转盘锁（Open the Lock）——中等
# 思路：从 '0000' 出发做 BFS，把死锁串预先放进集合当作已访问；每层扩展拨动一位得到的 8 个状态，首次命中 target 的层数即最少步数。
# 时间复杂度：O(10^4 * 8)，状态数上限约一万、每个状态 8 条边；空间复杂度：O(10^4)，队列与集合最多保存一万个状态。
class Solution:  # LeetCode 约定的题解类
    def openLock(self, deadends: List[str], target: str) -> int:  # deadends 是死锁串，target 是目标串
        def next(s):  # 内部辅助函数：把 s 的某一位上下拨动一位，返回全部邻居
            res = []  # 收集邻居状态
            s = list(s)  # 转成字符列表，才允许按下标就地修改
            for i in range(4):  # 依次拨动四个拨轮
                c = s[i]  # 暂存原字符，便于最后还原
                s[i] = '9' if c == '0' else str(int(c) - 1)  # 向下拨：0 回绕成 9，其余减一
                res.append(''.join(s))  # 记录向下拨后的状态
                s[i] = '0' if c == '9' else str(int(c) + 1)  # 向上拨：9 回绕成 0，其余加一
                res.append(''.join(s))  # 记录向上拨后的状态
                s[i] = c  # 还原这一位，继续处理下一位
            return res  # 返回全部 8 个邻居状态

        if target == '0000':  # 目标就是起点，0 步即可到达
            return 0
        s = set(deadends)  # 集合同时充当「死锁表」与「已访问表」，用来 O(1) 判重
        if '0000' in s:  # 起点本身就是死锁，永远无法出发
            return -1
        q = deque(['0000'])  # BFS 队列，必须用 deque 才能 O(1) 地从左端弹出
        s.add('0000')  # 把起点登记为已访问
        ans = 0  # 记录的层数，也就是已走的步数
        while q:  # 队列非空说明还有状态可以向外扩展
            ans += 1  # 进入新的一层，步数加一
            for _ in range(len(q)):  # 先固定本层状态个数，保证只扩展这一层
                p = q.popleft()  # 取出并移除当前状态
                for t in next(p):  # 枚举 8 个邻居状态
                    if t == target:  # 首次遇到目标，BFS 保证这是最少步数
                        return ans
                    if t not in s:  # 邻居既不是死锁，也没有被访问过
                        q.append(t)  # 入队，等待下一层继续扩展
                        s.add(t)  # 立刻登记，防止同一层内重复入队
        return -1  # 队列耗尽仍未到达目标，说明被死锁彻底隔断
