# 题目：2446. 判断两个事件是否存在冲突（Determine if Two Events Have Conflict）
# 思路：每个事件用 [开始, 结束] 两个 "HH:MM" 字符串表示，定长的同格式时间按字典序比较即等价于按时间比较；两个闭区间冲突等价于「event1 不在 event2 之后，且 event1 不在 event2 之前」。
# 时间复杂度：O(1)，只做常数次字符串比较；空间复杂度：O(1)，只用常数个临时值。
class Solution:  # LeetCode 约定的题解类
    def haveConflict(self, event1: List[str], event2: List[str]) -> bool:  # event1、event2 都是 [开始时间, 结束时间] 两个字符串
        return not (event1[0] > event2[1] or event1[1] < event2[0])  # 前一个条件说 event1 开始晚于 event2 结束，后一个说 event1 结束早于 event2 开始；两个都不满足即两区间重叠，所以整体取 not
