# 3697. Compute Decimal Representation（3697. 计算十进制表示）
# 核心思路：从低位到高位逐位拆出数字 d，把 d × 当前位权值 10^p 加入答案（跳过数位为 0 的位），最后反转得到从高位到低位的顺序。
# 复杂度：时间 O(log n)（十进制位数），空间 O(log n)。
class Solution:  # 定义题解类
    def decimalRepresentation(self, n: int) -> List[int]:  # 主函数：把 n 表示成若干“数位 × 10 的幂”的列表
        ans = []  # ans 保存每一项
        p = 1  # p 是当前位的权值，从个位（1）开始
        while n:  # 逐位处理直到 n 为 0
            n, v = divmod(n, 10)  # divmod 同时得到去掉最低位后的 n 和最低位数字 v
            if v:  # 该位非零才需要计入
                ans.append(p * v)  # 把“数位 × 权值”加入答案
            p *= 10  # 权值提升一个数量级
        ans.reverse()  # 目前低位在前，反转为高位在前
        return ans  # 返回结果
