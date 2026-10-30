# 题目：842. 将数组拆分成斐波那契序列（Split Array into Fibonacci Sequence）
# 思路：回溯枚举前两个数，其后每个数必须等于前两项之和；用 2**31-1 与前缀和剪枝。
# 时间复杂度：O(n^2) 量级的回溯搜索，n 为数字串长度；空间复杂度：O(n)，答案数组与递归栈。
class Solution:  # LeetCode 约定的题解类
    def splitIntoFibonacci(self, num: str) -> List[int]:  # num 是数字串；返回可拆出的斐波那契序列，拆不出时返回空列表
        def dfs(i):  # dfs(i)：从下标 i 开始向后切分，返回是否找到合法拆分
            if i == n:  # 切到末尾时，序列长度必须大于 2
                return len(ans) > 2  # 返回长度是否满足斐波那契序列至少三个数的要求
            x = 0  # 当前要切出的数字，逐位累加
            for j in range(i, n):  # 枚举以 i 开头的数的结束位置 j
                if j > i and num[i] == '0':  # 多位数不能有前导零，首位是 0 就停止本层枚举
                    break  # break 交给外层回溯换一种切法
                x = x * 10 + int(num[j])  # 把第 j 位数字接到当前数末尾
                if x > 2**31 - 1 or (len(ans) > 2 and x > ans[-2] + ans[-1]):  # 超过 int 上限或已大于前两项之和，加长只会更大，剪枝
                    break  # 跳出内层循环
                if len(ans) < 2 or ans[-2] + ans[-1] == x:  # 前两个数可任选；之后必须恰好等于前两项之和
                    ans.append(x)  # 把 x 加入答案序列
                    if dfs(j + 1):  # 递归切分剩余部分，成功则整条路径保留
                        return True  # 找到完整合法拆分，向上返回 True
                    ans.pop()  # 回溯：弹出 x，尝试其他切法
            return False  # 本次递归所有切法都失败

        n = len(num)  # 数字串长度，供 dfs 与末尾判断使用
        ans = []  # 保存当前构造出的拆分结果
        dfs(0)  # 从下标 0 开始搜索
        return ans  # 返回拆分结果，失败时为回溯清空后的空列表
