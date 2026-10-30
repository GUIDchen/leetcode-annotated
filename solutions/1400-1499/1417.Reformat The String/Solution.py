# 题目：1417. 重新格式化字符串（Reformat The String）
# 思路：分别挑出字母与数字，长度差超过 1 返回空串；交换成「a 较长」，再 zip 交替拼接并补上多余字符。
# 时间复杂度：O(n)，一次遍历加一次拼接；空间复杂度：O(n)，保存两组字符与结果列表。
class Solution:  # LeetCode 约定的题解类
    def reformat(self, s: str) -> str:  # s 是数字与小写字母混合的字符串，返回交替重排后的字符串
        a = [c for c in s if c.islower()]  # 列表推导挑出所有小写字母
        b = [c for c in s if c.isdigit()]  # 列表推导挑出所有数字
        if abs(len(a) - len(b)) > 1:  # 两类数量差超过 1 时无法交替排列
            return ''  # 按题目要求返回空串
        if len(a) < len(b):  # 让 a 始终是较长的那一组
            a, b = b, a  # 同时交换，保证后面逻辑统一
        ans = []  # 结果片段列表
        for x, y in zip(a, b):  # 成对交替拼接，较长的组排在前面
            ans.append(x + y)  # 较长组字符加较短组字符，保证相邻异类
        if len(a) > len(b):  # 较长组恰好多出一个字符
            ans.append(a[-1])  # 把这个字符补到末尾
        return ''.join(ans)  # 拼成字符串返回
