# 题目：2241. 设计一个 ATM 机器（Design an ATM Machine）
# 思路：面额按 20/50/100/200/500 升序保存，取款时从最大面额开始贪心，能取多少取多少，最后若还有余额则失败。
# 时间复杂度：deposit 与 withdraw 都只遍历 5 种面额，即 O(1)；空间复杂度：O(1)，只需记录五种面额的库存。
class ATM:  # 题目要求的 ATM 机器类
    def __init__(self):  # 构造函数：初始化面额表与各种面额的库存
        self.d = [20, 50, 100, 200, 500]  # 五种面额，升序排列，下标与输入 banknotesCount 一一对应
        self.m = len(self.d)  # 面额种数
        self.cnt = [0] * self.m  # cnt[i] 表示第 i 种面额当前剩余的钞票张数

    def deposit(self, banknotesCount: List[int]) -> None:  # 按面额顺序存入若干张钞票
        for i, x in enumerate(banknotesCount):  # 逐个面额取出本次存入的张数 x
            self.cnt[i] += x  # 累加到对应面额的库存上

    def withdraw(self, amount: int) -> List[int]:  # 取款 amount 元，返回各面额张数；失败返回 [-1]
        ans = [0] * self.m  # ans[i] 记录第 i 种面额本次要取出多少张
        for i in reversed(range(self.m)):  # 从最大面额开始贪心，面额越大越优先使用
            ans[i] = min(amount // self.d[i], self.cnt[i])  # 该面额最多取几张：受剩余金额与库存双重限制
            amount -= ans[i] * self.d[i]  # 从待取金额里扣掉该面额已经凑出的部分
        if amount > 0:  # 所有面额都取完仍有余额，说明凑不出 amount
            return [-1]  # 取款失败，按题意返回 -1
        for i, x in enumerate(ans):  # 取款成功，逐个面额扣减库存
            self.cnt[i] -= x  # 该面额的库存减去本次取走的张数
        return ans  # 返回五种面额各自取出的张数


# 下面是题目给出的调用示例，仅为注释说明，无需实现
# Your ATM object will be instantiated and called as such:
# obj = ATM()
# obj.deposit(banknotesCount)
# param_2 = obj.withdraw(amount)
