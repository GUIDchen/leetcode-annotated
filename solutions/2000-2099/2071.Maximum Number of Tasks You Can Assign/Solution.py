# 题目：2071. 你可以安排的最多任务数目（Maximum Number of Tasks You Can Assign）
# 思路：排序后二分答案 x，判定时只让最强的 x 名工人做最小的 x 个任务，用单调队列贪心：队头能直接做就做最小的，否则花一颗药丸做最大的。
# 时间复杂度：O((n + m) log(n + m) + min(n, m) · n)；空间复杂度：O(n)，队列最多保存 n 个任务耗时。
class Solution:  # LeetCode 约定的题解类
    def maxTaskAssign(  # 方法定义：返回在药丸辅助下最多能完成的任务数目
        self, tasks: List[int], workers: List[int], pills: int, strength: int  # tasks 是任务耗时，workers 是工人能力，pills 是药丸数，strength 是药丸加成
    ) -> int:  # 返回类型为整数（最多完成的任务数）
        def check(x):  # 判定函数：能否完成恰好 x 个任务
            i = 0  # 指向最小的、尚未进入候选队列的任务下标
            q = deque()  # 双端队列：存放当前工人「加药丸后够得着」的任务耗时，内部升序
            p = pills  # 本次判定可用药丸数（每次判定独立计数）
            for j in range(m - x, m):  # 让最强的 x 名工人上场，从强到弱依次分派
                while i < x and tasks[i] <= workers[j] + strength:  # 把该工人吃药丸后仍能完成的候选任务全部入队
                    q.append(tasks[i])  # 任务入队
                    i += 1  # 候选指针前移
                if not q:  # 队列为空：连最省力的任务都做不了
                    return False  # 判定失败
                if q[0] <= workers[j]:  # 队头最省力，不用药丸就能完成
                    q.popleft()  # 直接拿走最小任务，省下药丸
                elif p == 0:  # 只能靠药丸，但药丸已用完
                    return False  # 判定失败
                else:  # 还有药丸：吃药丸强行完成一个任务
                    p -= 1  # 消耗一颗药丸
                    q.pop()  # 取走最大的任务，把省力的留给更弱的工人
            return True  # x 个任务全部分派成功

        n, m = len(tasks), len(workers)  # n 为任务数，m 为工人数
        tasks.sort()  # 任务耗时升序
        workers.sort()  # 工人能力升序
        left, right = 0, min(n, m)  # 二分区间：最多完成 min(n, m) 个任务
        while left < right:  # 二分答案，寻找满足 check 的最大 x
            mid = (left + right + 1) >> 1  # 上取整中点，配合 left = mid 避免死循环
            if check(mid):  # mid 个任务可以完成
                left = mid  # 答案至少是 mid
            else:  # 否则 mid 不可行
                right = mid - 1  # 答案更小
        return left  # 二分收敛，left 即最多能完成的任务数
