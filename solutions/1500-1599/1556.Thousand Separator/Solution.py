# 题目：1556. 千位分隔数（Thousand Separator）
# 思路：不断用 divmod 取出最低位、追加到答案列表尾部，每凑满 3 位就补一个点，最后反转列表拼成从高位到低位的字符串。
# 时间复杂度：O(log n)（位数级别次循环 + 一次反转）；空间复杂度：O(log n)（列表长度与位数同阶）。
class Solution:  # LeetCode 约定的题解类
    def thousandSeparator(self, n: int) -> str:  # n：待格式化的非负整数
        cnt = 0  # cnt：当前已经拼接了多少个数字位（用来判断是否该插入点）
        ans = []  # ans：按低位到高位的顺序收集字符，最后反转拼接
        while 1:  # 至少处理一位数字，用 break 控制退出
            n, v = divmod(n, 10)  # 同时得到整除结果（去掉最低位）与余数（最低位数字）
            ans.append(str(v))  # 把这一位字符追加到列表尾部
            cnt += 1  # 已拼接的位数加一
            if n == 0:  # 所有位都取完了
                break  # 结束循环（最高位前面不能再加点）
            if cnt == 3:  # 刚好凑满 3 位
                ans.append('.')  # 追加千位分隔符
                cnt = 0  # 位计数清零，开始统计下一组三位
        return ''.join(ans[::-1])  # 反转成从高位到低位的顺序，再拼接成一个字符串返回
