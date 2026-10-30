# 题目：1215. 步进数（Stepping Numbers）
# 思路：以 1~9 为种子做 BFS，每次在末位数字上拼接 x-1 或 x+1 生成相邻的步进数，按数值递增顺序扩展到 high 为止。
# 时间复杂度：O(high 以内的步进数个数)，每个数只入队出队一次；空间复杂度：O(同上的队列与答案规模)。
class Solution:  # LeetCode 约定的题解类
    def countSteppingNumbers(self, low: int, high: int) -> List[int]:  # low/high：闭区间边界；返回区间内所有步进数（升序）
        ans = []  # 收集答案，BFS 按数值递增出队，所以天然有序
        if low == 0:  # 0 按题面约定也算步进数，但它无法由 1~9 的种子扩展得到，需要单独处理
            ans.append(0)  # 区间包含 0 时先把 0 放进答案
        q = deque(range(1, 10))  # 双端队列：把 1~9 作为一位数的种子批量入队
        while q:  # 队列非空就继续扩展，出队顺序保证从小到大
            v = q.popleft()  # 取出当前待扩展的步进数（Python 整数不会溢出，无需担心位数）
            if v > high:  # 队列有序，一旦超过上界，之后扩展出的数只会更大
                break  # 结束整个 BFS
            if v >= low:  # 只有落在 [low, high] 区间内才需要收集
                ans.append(v)  # 把合法步进数加入答案
            x = v % 10  # 取末位数字 x，它决定下一步可以拼接哪两个数字
            if x:  # 末位非 0 才能拼接 x-1（相邻数字差为 1）
                q.append(v * 10 + x - 1)  # 生成 v 后面接一位更小数字的新步进数
            if x < 9:  # 末位小于 9 才能拼接 x+1（相邻数字差为 1）
                q.append(v * 10 + x + 1)  # 生成 v 后面接一位更大数字的新步进数
        return ans  # 返回升序排列的答案
