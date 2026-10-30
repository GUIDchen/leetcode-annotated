# 题目：1432. 改变一个整数能得到的最大差值（Max Difference You Can Get From Changing an Integer）
# 思路：分别构造最大值与最小值——最大把首位非 9 数字全换成 9；最小按首位是否为 1 换成 1，或把后续首个非 0/1 数字全换成 0。
# 时间复杂度：O(d²)，d 为位数（replace 会扫描整串）；空间复杂度：O(d)，存放两个数字串。
class Solution:  # LeetCode 约定的题解类
    def maxDiff(self, num: int) -> int:  # num：原整数，返回「替换后的最大值 - 替换后的最小值」
        a, b = str(num), str(num)  # 把数字转成字符串再逐位替换，a 用来求最大值，b 用来求最小值
        for c in a:  # 从最高位开始找第一个不是 '9' 的数字
            if c != "9":  # 找到后全换成 '9'，这样数值最大
                a = a.replace(c, "9")  # str.replace 会替换所有出现位置
                break  # 只需替换一次，后面的位不再处理
        if b[0] != "1":  # 最小值规则：首位不能变成 0（避免前导零）
            b = b.replace(b[0], "1")  # 首位不是 1 就整体换成 1，得到最小且合法的最小值
        else:  # 首位已经是 1，只能改后面的位
            for c in b[1:]:  # 从第二位开始找第一个既不是 0 也不是 1 的数字
                if c not in "01":  # 换成 0 不会造成前导零，可以放心替换
                    b = b.replace(c, "0")  # 把它所有出现的位置都换成 0
                    break  # 只替换一次即可
        return int(a) - int(b)  # 两个替换后的数字相减即为最大差值
