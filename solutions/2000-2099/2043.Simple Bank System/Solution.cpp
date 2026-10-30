// 题目：2043. 简易银行系统（Simple Bank System）
// 思路：用数组保存每个账户余额；存取转三种操作都先检查账户编号是否越界，转账与取款再检查余额是否足够，然后原地加减。
// 时间复杂度：单次操作 O(1)；空间复杂度：O(n)，需要保存 n 个账户的余额。
class Bank {  // Bank 类：维护每个账户的余额
public:  // 对外提供构造函数与三种操作
    vector<long long> balance;  // balance：下标 0 对应 1 号账户，用 long long 防止金额溢出
    int n;  // n：账户数量，用于越界判断

    Bank(vector<long long>& balance) {  // 构造函数：用初始余额初始化银行
        this->balance = balance;  // 拷贝初始余额（形参与成员同名，用 this 区分）
        n = balance.size();  // 记录账户个数
    }

    bool transfer(int account1, int account2, long long money) {  // 转账：从 account1 转 money 到 account2
        if (account1 > n || account2 > n || balance[account1 - 1] < money) return false;  // 账户编号越界或转出方余额不足，转账失败
        balance[account1 - 1] -= money;  // 转出方扣款
        balance[account2 - 1] += money;  // 转入方入账
        return true;  // 转账成功
    }

    bool deposit(int account, long long money) {  // 存款：给 account 账户存入 money
        if (account > n) return false;  // 账户编号越界则失败
        balance[account - 1] += money;  // 余额增加
        return true;  // 存款成功
    }

    bool withdraw(int account, long long money) {  // 取款：从 account 账户取出 money
        if (account > n || balance[account - 1] < money) return false;  // 账户编号越界或余额不足则失败
        balance[account - 1] -= money;  // 余额减少
        return true;  // 取款成功
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */