# 题目：621. 任务调度器（Task Scheduler）
# 思路：用出现最多的字母构造「桶」——(x-1)*(n+1)+s 给出桶模型的答案，任务总数更多时直接取任务总数。
# 时间复杂度：O(m + 26)，m 为任务个数；空间复杂度：O(26)，只用字母计数的哈希表。
class Solution:  # LeetCode 约定的题解类
    def leastInterval(self, tasks: List[str], n: int) -> int:  # tasks 是任务字符列表，n 是相同任务之间的冷却间隔
        cnt = Counter(tasks)  # 统计每个任务字母的出现次数（Counter 由判题环境提供）
        x = max(cnt.values())  # 最大频次，也就是「出现最多的那个字母出现了几次」
        s = sum(v == x for v in cnt.values())  # 统计有多少个字母并列达到最大频次：生成器里比较结果为真计 1
        return max(len(tasks), (x - 1) * (n + 1) + s)  # 两种排布取较大者：能填满桶时用桶公式，任务更多时就是任务总数
