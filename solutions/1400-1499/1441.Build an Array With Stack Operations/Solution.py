# 题目：1441. 用栈操作构建数组（Build an Array With Stack Operations）
# 思路：cur 从 1 递增，落在 target 之外的值先 Push 再 Pop 丢弃，落在 target 中的值只 Push。
# 时间复杂度：O(n)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def buildArray(self, target: List[int], n: int) -> List[str]:  # target 是目标数组，n 是可用整数的上界
        ans = []  # ans 保存要返回的操作序列
        cur = 1  # 下一个准备压入栈的整数
        for x in target:  # 按顺序处理 target 的每个元素
            while cur < x:  # cur 不在 target 里，需要跳过
                ans.extend(["Push", "Pop"])  # 一次放入 Push 与 Pop 两个操作，相当于压入后立刻弹出
                cur += 1  # 继续尝试下一个整数
            ans.append("Push")  # x 是需要的数字，压入并保留
            cur += 1  # 下一个数字从 x+1 开始
        return ans  # 返回操作序列
