// 3711. Maximum Transactions Without Negative Balance（3711. 不出现负余额的最大交易额 🔒）
// 核心思路：按时间顺序逐笔强行执行，用有序可重集合保存已选交易额；一旦余额为负，就撤销已选交易中金额最小（最负）的一笔，因为它能让余额回升最多，从而用最少的撤销次数恢复可行性。
// 复杂度：时间 O(n log n)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int maxTransactions(vector<int>& transactions) {  // 返回余额始终非负时最多能执行的交易笔数
        multiset<int> st;  // 有序可重集合，保存已选交易额，便于随时取出最小值
        int ans = transactions.size();  // 先假设全部交易都执行
        long long s = 0;  // 当前余额，用 long long 防止累加溢出
        for (int x : transactions) {  // 按时间顺序处理每笔交易
            s += x;  // 先强行执行这笔交易
            st.insert(x);  // 把交易额放入集合
            while (s < 0) {  // 余额为负时，需要撤销若干笔已选交易
                auto it = st.begin();  // 指向已选交易中金额最小（最负）的一笔
                int y = *it;  // 取出该交易额
                st.erase(it);  // 从集合中删除这笔交易
                s -= y;  // 撤销后余额回升
                --ans;  // 执行笔数减一
            }  // 反复撤销直到余额非负
        }  // 结束交易遍历
        return ans;  // 返回最多可执行的交易笔数
    }  // 方法结束
};  // 类定义结束
