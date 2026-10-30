# 题目：1647. 字符频次唯一的最小删除次数（Minimum Deletions to Make Character Frequencies Unique）
# 思路：统计频次并降序排序，贪心地让每个频次严格小于前一个；冲突就削到 pre-1，pre 降到 0 后剩余频次全部删空。
# 时间复杂度：O(n + 26 log 26)，统计 O(n) 加排序常数级；空间复杂度：O(1)，只有 26 个字母的计数。
class Solution:  # LeetCode 约定的题解类
    def minDeletions(self, s: str) -> int:  # s：输入字符串，返回让所有字符频次互不相同所需的最小删除次数
        cnt = Counter(s)  # 统计每个字符出现的次数
        ans, pre = 0, inf  # ans 记录删除次数；pre 记录上一个保留的频次，inf 保证最大值原样保留
        for v in sorted(cnt.values(), reverse=True):  # 频次从大到小逐个处理
            if pre == 0:  # pre 已是 0，后面更小的频次也无处可放
                ans += v  # 当前频次只能全部删掉
            elif v >= pre:  # 频次与上一个冲突（或不小于它），必须削到 pre - 1
                ans += v - pre + 1  # 削到 pre - 1 需要删除 v - (pre - 1) 个字符
                pre -= 1  # 可用的频次上限跟着递减
            else:  # 频次比 pre 小，可以原样保留
                pre = v  # 更新上一个保留下来的频次
        return ans  # 返回最小删除次数
