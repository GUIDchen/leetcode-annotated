# 题目：282. 给表达式添加运算符（Expression Add Operators）
# 思路：DFS 枚举每个切分点与运算符（+ - *），用 prev 保存上一个乘数，乘号需要把 curr 中的 prev 撤回再乘，从而让 * 优先。
# 时间复杂度：O(4ⁿ)，每个数字后有 4 种选择；空间复杂度：O(n)，递归栈与临时路径。
class Solution:  # LeetCode 约定的题解类
    def addOperators(self, num: str, target: int) -> List[str]:  # num 是数字字符串，target 是目标值，返回所有能得到 target 的表达式
        ans = []  # 收集所有合法表达式

        def dfs(u, prev, curr, path):  # u：当前切分起点，prev：上一段的值，curr：当前累计值，path：已拼好的表达式
            if u == len(num):  # 数字已全部用完，递归到叶子
                if curr == target:  # 当前累计值正好等于目标值
                    ans.append(path)  # 记录这条合法表达式
                return  # 无论是否相等都要返回
            for i in range(u, len(num)):  # 枚举本次截取的数字 num[u..i]
                if i != u and num[u] == '0':  # 防止前导零：非首位且以 0 开头时，再延长只会得到带前导零的数
                    break  # 直接结束本层枚举
                next = int(num[u : i + 1])  # 截取子串并转成整数，作为本次参与运算的操作数
                if u == 0:  # 第一个操作数前面不能加运算符
                    dfs(i + 1, next, next, path + str(next))  # 首段直接作为初始累计值，后续乘法要靠它回退
                else:  # 非首段：尝试加、减、乘三种运算符
                    dfs(i + 1, next, curr + next, path + "+" + str(next))  # 加号：累计值加上 next，prev 变成 next
                    dfs(i + 1, -next, curr - next, path + "-" + str(next))  # 减号：累计值减去 next，prev 变成 -next
                    dfs(  # 乘号：需要先把 curr 中上一段的贡献撤掉
                        i + 1,  # 递归到下一个切分起点
                        prev * next,  # prev * next 成为新的上一段值
                        curr - prev + prev * next,  # 先回退 prev 再加回 prev*next，保证乘法优先
                        path + "*" + str(next),  # 表达式末尾拼接乘号与操作数
                    )  # 结束三参数 dfs 调用

        dfs(0, 0, 0, "")  # 从第 0 个字符起搜索，初始化累计值与上一段值都为 0
        return ans  # 返回所有合法表达式
