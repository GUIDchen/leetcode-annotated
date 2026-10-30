# 题目：277. 搜寻名人（Find the Celebrity）
# 思路：第一轮 O(n) 用「候选人认识谁就换谁」淘汰，唯一留下的人可能是名人；第二轮再 O(n) 验证他不认识任何人且被所有人认识，否则返回 -1。
# 时间复杂度：O(n)，两轮线性扫描；空间复杂度：O(1)，只用几个变量。
# The knows API is already defined for you.
# return a bool, whether a knows b
# def knows(a: int, b: int) -> bool:


class Solution:  # LeetCode 约定的题解类
    def findCelebrity(self, n: int) -> int:  # n：人数，编号 0..n-1；返回名人编号，没有则返回 -1
        ans = 0  # 候选名人先假设为 0 号
        for i in range(1, n):  # 第一轮：每次询问淘汰一个不可能是名人的人
            if knows(ans, i):  # ans 认识 i，说明 ans 不是名人，候选换成 i
                ans = i  # 更新候选（i 也可能不是，留到第二轮验证）
        for i in range(n):  # 第二轮：验证候选是否满足名人定义
            if ans != i:  # 跳过自己和自己比较
                if knows(ans, i) or not knows(i, ans):  # 名人必须被所有人认识且不认识任何人，任一不满足就无名人
                    return -1  # 返回 -1 表示不存在名人
        return ans  # 验证通过，返回名人编号
