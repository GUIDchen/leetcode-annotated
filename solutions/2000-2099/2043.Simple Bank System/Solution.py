# 题目：2043. 简易银行系统（Simple Bank System）
# 思路：用一个列表保存每个账户余额；存取转三种操作都先检查账户编号是否越界，转账与取款再检查余额是否足够，然后原地加减。
# 时间复杂度：单次操作 O(1)；空间复杂度：O(n)，需要保存 n 个账户的余额。
class Bank:  # Bank 类：用一个列表保存所有账户的余额
    def __init__(self, balance: List[int]):  # balance：下标 0 对应 1 号账户
        self.balance = balance  # 保存余额列表的引用，后续操作直接原地修改
        self.n = len(balance)  # n：账户数量，用于越界判断

    def transfer(self, account1: int, account2: int, money: int) -> bool:  # 转账：从 account1 转 money 到 account2
        if account1 > self.n or account2 > self.n or self.balance[account1 - 1] < money:  # 账户编号越界或转出方余额不足，转账失败
            return False  # 转账失败，余额保持不变
        self.balance[account1 - 1] -= money  # 转出方扣款
        self.balance[account2 - 1] += money  # 转入方入账
        return True  # 转账成功

    def deposit(self, account: int, money: int) -> bool:  # 存款：给 account 账户存入 money
        if account > self.n:  # 账户编号越界则失败
            return False  # 账户不存在，存款失败
        self.balance[account - 1] += money  # 余额增加
        return True  # 存款成功

    def withdraw(self, account: int, money: int) -> bool:  # 取款：从 account 账户取出 money
        if account > self.n or self.balance[account - 1] < money:  # 账户编号越界或余额不足则失败
            return False  # 取款失败，余额保持不变
        self.balance[account - 1] -= money  # 余额减少
        return True  # 取款成功


# Your Bank object will be instantiated and called as such:
# obj = Bank(balance)
# param_1 = obj.transfer(account1,account2,money)
# param_2 = obj.deposit(account,money)
# param_3 = obj.withdraw(account,money)
