# 题目：3711. Maximum Transactions Without Negative Balance（3711. 不出现负余额的最大交易额 🔒）
# 核心思路：按时间顺序逐笔强行执行，用有序列表保存已选交易额；一旦余额为负，就撤销已选交易中金额最小（最负）的一笔，因为它能让余额回升最多，从而用最少的撤销次数恢复可行性。
# 复杂度：时间 O(n log n)，空间 O(n)。
class Solution:  # LeetCode 约定的题解类
    def maxTransactions(self, transactions: List[int]) -> int:  # 返回余额始终非负时最多能执行的交易笔数
        st = SortedList()  # 有序列表，保存已选交易额，可 O(log n) 取出最小值
        s = 0  # 当前余额
        ans = len(transactions)  # 先假设全部交易都执行
        for x in transactions:  # 按时间顺序处理每笔交易
            s += x  # 先强行执行这笔交易
            st.add(x)  # 把交易额加入有序列表
            while s < 0:  # 余额为负时，撤销金额最小（最负）的已选交易
                y = st.pop(0)  # 弹出最小交易额
                s -= y  # 撤销后余额回升
                ans -= 1  # 执行笔数减一
        return ans  # 返回最多可执行的交易笔数
