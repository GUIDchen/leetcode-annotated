# 题目：1058. 最小化舍入误差以满足目标（Minimize Rounding Error to Meet Target）
# 思路：先全部向下取整得到基准和 mi；若还差 d 个，就把小数部分最大的 d 个改成向上取整，其余保持向下取整，总误差最小。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，保存所有小数部分。
class Solution:  # LeetCode 约定的题解类
    def minimizeError(self, prices: List[str], target: int) -> str:  # prices 是价格字符串，target 是取整后的目标和
        mi = 0  # 记录所有价格向下取整后的总和
        arr = []  # 收集所有非零的小数部分
        for p in prices:  # 逐个处理价格
            p = float(p)  # 字符串转成浮点数
            mi += int(p)  # 向下取整后累加
            if d := p - int(p):  # 海象运算符：取出小数部分，为 0 时该条件为假、不计入
                arr.append(d)  # 记录小数部分
        if not mi <= target <= mi + len(arr):  # 目标不在 [全下取整, 全上取整] 区间内则无解
            return "-1"  # 返回题目要求的字符串 -1
        d = target - mi  # 需要改成向上取整的个数
        arr.sort(reverse=True)  # 小数部分从大到小：优先让小数大的进位，总误差更小
        ans = d - sum(arr[:d]) + sum(arr[d:])  # 总误差 = d 个进位各损失 (1-小数) + 其余各多出小数
        return f'{ans:.3f}'  # 按题目要求格式化为三位小数的字符串
