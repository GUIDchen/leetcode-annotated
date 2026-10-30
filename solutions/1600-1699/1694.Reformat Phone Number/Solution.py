# 题目：1694. 重新格式化电话号码（Reformat Phone Number）
# 思路：先删掉空格和短横线得到纯数字串；再按每 3 位分组，末尾余 1 位时把最后一组拆成 2+2，余 2 位时单独加一组 2 位。
# 时间复杂度：O(n)，字符串替换与切片拼接各一遍；空间复杂度：O(n)，需要保存纯数字串与分组列表。
class Solution:  # LeetCode 约定的题解类
    def reformatNumber(self, number: str) -> str:  # number：可能含空格与 '-' 的原始号码
        number = number.replace("-", "").replace(" ", "")  # 去掉所有短横线与空格，只留数字
        n = len(number)  # 纯数字的位数，决定后面如何分组
        ans = [number[i * 3 : i * 3 + 3] for i in range(n // 3)]  # 先按每块 3 位切分，共 n//3 块
        if n % 3 == 1:  # 末尾还剩 1 位：不能出现长度为 1 的块，需要拆成 2+2
            ans[-1] = ans[-1][:2]  # 把最后一块 3 位砍成 2 位
            ans.append(number[-2:])  # 再补上最后剩下的 2 位
        elif n % 3 == 2:  # 末尾还剩 2 位：正好可以自成一块
            ans.append(number[-2:])  # 直接追加这 2 位数字
        return "-".join(ans)  # 用短横线连接各块，得到最终格式
