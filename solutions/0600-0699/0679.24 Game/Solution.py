# 题目：679. 24 点游戏（24 Game）
# 思路：把四张牌转成浮点数，每次任取两张做 + - * / 得到一个新数并递归，只剩一个数时与 24 比较。
# 时间复杂度：O(1)（牌数恒为 4，搜索规模是常数）；空间复杂度：O(1)，递归深度与临时列表长度都以 4 为界。
class Solution:  # LeetCode 约定的题解类
    def judgePoint24(self, cards: List[int]) -> bool:  # cards 是四张牌的点数
        def dfs(nums: List[float]):  # 内部递归函数：nums 是当前剩下的所有数字
            n = len(nums)  # 当前剩余数字的个数
            if n == 1:  # 只剩一个数，到达递归出口
                if abs(nums[0] - 24) < 1e-6:  # 用浮点误差容忍判断是否等于 24
                    return True  # 恰好是 24，说明这条表达式成立
                return False  # 不是 24，这条分支失败
            ok = False  # 记录当前层是否已经找到解
            for i in range(n):  # 枚举第一个操作数的下标
                for j in range(n):  # 枚举第二个操作数的下标（有序枚举，减法和除法不满足交换律）
                    if i != j:  # 两个操作数必须是不同的牌
                        nxt = [nums[k] for k in range(n) if k != i and k != j]  # 取出没参与运算的其余数字
                        for op in ops:  # 依次尝试四种运算符
                            match op:  # Python 3.10 的结构化模式匹配
                                case "/":  # 除法分支
                                    if nums[j] == 0:  # 除数不能为 0
                                        continue  # 跳过这次除法
                                    ok |= dfs(nxt + [nums[i] / nums[j]])  # 把商并入剩余数字后继续递归
                                case "*":  # 乘法分支
                                    ok |= dfs(nxt + [nums[i] * nums[j]])  # 把积并入剩余数字后继续递归
                                case "+":  # 加法分支
                                    ok |= dfs(nxt + [nums[i] + nums[j]])  # 把和并入剩余数字后继续递归
                                case "-":  # 减法分支
                                    ok |= dfs(nxt + [nums[i] - nums[j]])  # 把差并入剩余数字后继续递归（顺序不能交换）
                            if ok:  # 任意一个分支成功就可以提前结束
                                return True  # 向上层报告找到解
            return ok  # 所有分支都失败

        ops = ("+", "-", "*", "/")  # 四种可用的运算符
        nums = [float(x) for x in cards]  # 统一转成 float，避免整数除法丢失小数
        return dfs(nums)  # 从初始四张牌开始搜索
