// 题目：2241. 设计一个 ATM 机器（Design an ATM Machine）
// 思路：面额按 20/50/100/200/500 升序存好，取款时从最大面额开始贪心，能取多少取多少，最后若仍有余额则失败。
// 时间复杂度：deposit 为 O(5)，withdraw 为 O(5)，均视作 O(1)；空间复杂度：O(5) = O(1)，只需记录五种面额的库存。
class ATM {  // 题目要求的 ATM 机器类
public:  // 构造函数、存款、取款三个对外接口
    ATM() {  // 构造函数：库存由成员变量的默认初始化完成，这里无需额外动作
    }

    void deposit(vector<int> banknotesCount) {  // banknotesCount[i] 表示第 i 种面额要存入的张数
        for (int i = 0; i < banknotesCount.size(); ++i) {  // 逐个面额累加
            cnt[i] += banknotesCount[i];  // 该面额的库存张数加上本次存入的张数
        }
    }

    vector<int> withdraw(int amount) {  // 取款 amount 元，返回各面额张数；失败返回 {-1}
        vector<int> ans(m);  // ans[i] 记录第 i 种面额本次要取出多少张
        for (int i = m - 1; ~i; --i) {  // 从最大面额开始贪心；~i 等价于 i >= 0
            ans[i] = min(1ll * amount / d[i], cnt[i]);  // 该面额最多取几张：既受剩余金额限制，也受库存限制
            amount -= ans[i] * d[i];  // 从待取金额里扣掉该面额已经凑出的部分
        }
        if (amount > 0) {  // 所有面额都取完仍有余额，说明这些钞票凑不出 amount
            return {-1};  // 取款失败，按题意返回 -1
        }
        for (int i = 0; i < m; ++i) {  // 取款成功，才真正扣减库存
            cnt[i] -= ans[i];  // 该面额的库存减去本次取走的张数
        }
        return ans;  // 返回五种面额各自取出的张数
    }

private:  // 以下为内部数据成员
    static constexpr int d[5] = {20, 50, 100, 200, 500};  // 五种面额，按升序排列，保证贪心从后往前即从大到小
    static constexpr int m = size(d);  // 面额种数，由 size(d) 自动推导为 5
    long long cnt[m] = {0};  // cnt[i] 是第 i 种面额的库存张数，用 long long 防止大量存入时溢出
};

// 下面是题目给出的调用示例，仅为注释说明，无需实现
/**
 * Your ATM object will be instantiated and called as such:
 * ATM* obj = new ATM();
 * obj->deposit(banknotesCount);
 * vector<int> param_2 = obj->withdraw(amount);
 */
