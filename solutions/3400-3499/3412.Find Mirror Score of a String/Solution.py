# 3412. 计算字符串的镜像分数 / Find Mirror Score of a String
# 核心思路：用哈希表为每个字符维护未配对下标栈，遇到其镜像字符就弹出最近下标并累加距离。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution:  # 题解类定义
    def calculateScore(self, s: str) -> int:  # 计算字符串的镜像分数
        d = defaultdict(list)  # 记录每个字符尚未配对的下标栈
        ans = 0  # 累加答案
        for i, x in enumerate(s):  # 从左到右扫描每个字符
            y = chr(ord("a") + ord("z") - ord(x))  # 镜像字符：a<->z, b<->y ...
            if d[y]:  # 存在可配对的镜像字符
                j = d[y].pop()  # 弹出最近的未配对下标
                ans += i - j  # 累加距离作为分数
            else:  # 否则
                d[x].append(i)  # 把当前下标压入自己的栈
        return ans  # 返回总分
