# 题目：2813. 子序列最大优雅度（Maximum Elegance of a K-Length Subsequence）
# 思路：按利润从大到小排序，先贪心取前 k 个得到总利润与类别数；再用后面利润较低但类别全新的元素，替换掉已选中重复类别里利润最小的元素，枚举所有提升类别数的机会取最大优雅度。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(k)，集合与栈最多各存 k 个元素。
class Solution:  # LeetCode 约定的题解类
    def findMaximumElegance(self, items: List[List[int]], k: int) -> int:  # items[i] = [利润, 类别]；k：子序列长度；返回最大优雅度
        items.sort(key=lambda x: -x[0])  # 按利润从大到小排序
        tot = 0  # 当前选中元素的总利润
        vis = set()  # 当前选中元素涵盖的类别集合
        dup = []  # 已选中元素里「类别重复」的利润，依次入栈，末尾就是其中最小的
        for p, c in items[:k]:  # 先贪心取利润最高的 k 个作为初始方案
            tot += p  # 累加总利润
            if c not in vis:  # 类别第一次出现，加入集合
                vis.add(c)  # 重复类别：记下利润，便于后面被替换掉
            else:  # if 分支结束
                dup.append(p)  # 初始选取循环结束
        ans = tot + len(vis) ** 2  # 初始优雅度 = 总利润 + 类别数的平方
        for p, c in items[k:]:  # 用后面利润较低但类别全新的元素去替换重复项
            if c in vis or not dup:  # 类别已存在，或没有重复项可换，本轮无法提升
                continue  # 跳过该候选，继续下一个
            vis.add(c)  # 加入新类别，类别数加一
            tot += p - dup.pop()  # 弹出并扣掉一个重复项的利润，换成当前候选的利润
            ans = max(ans, tot + len(vis) ** 2)  # 更新答案：类别数已经加一
        return ans  # 返回枚举过程中的最大优雅度
