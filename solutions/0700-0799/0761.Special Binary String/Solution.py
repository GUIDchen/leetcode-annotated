# 题目：761. 特殊的二进制字符串（Special Binary String）
# 思路：递归拆出所有平衡的「1...0」子串，内部递归求最大字典序后包回 1/0，最后把子串降序拼接。
# 时间复杂度：O(n^2 log n)，每层递归 O(n) 且需排序；空间复杂度：O(n^2)，递归栈与子串存储。
class Solution:  # LeetCode 约定的题解类
    def makeLargestSpecial(self, s: str) -> str:  # s：只含 '0' 与 '1' 的特殊二进制字符串
        if s == '':  # 空串是递归出口
            return ''  # 直接返回空串
        ans = []  # 收集当前层拆出的每一个特殊子串
        cnt = 0  # 平衡计数：'1' 加 1、'0' 减 1，归零处即为子串边界
        i = j = 0  # i 是扫描指针，j 记录当前子串起点
        while i < len(s):  # 从左到右扫描整个字符串
            cnt += 1 if s[i] == '1' else -1  # 根据当前字符更新平衡计数
            if cnt == 0:  # 计数归零，说明 s[j:i] 是一段平衡特殊串
                ans.append('1' + self.makeLargestSpecial(s[j + 1 : i]) + '0')  # 剥掉外层 1/0，递归求内部最大串，再包回来
                j = i + 1  # 起点移到下一段子串
            i += 1  # 扫描指针后移
        ans.sort(reverse=True)  # 子串按字典序降序排列，使拼接结果最大
        return ''.join(ans)  # 顺序拼接全部子串返回
