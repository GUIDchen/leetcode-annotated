// 3687. Library Late Fee Calculator（3687. 图书馆逾期罚款计算器）
// 核心思路：按逾期天数分段计费（1 天 1 元、2 到 5 天每天 2 元、超过 5 天每天 3 元），累加每本书的罚款。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 题解类
public:  // 公有接口，供判题器调用
    int lateFee(vector<int>& daysLate) {  // 返回所有书籍的逾期罚款总额
        auto f = [](int x) {  // 局部 lambda：计算单本书逾期 x 天的罚款
            if (x == 1) {  // 只逾期 1 天
                return 1;  // 罚款 1 元
            } else if (x > 5) {  // 逾期超过 5 天
                return 3 * x;  // 每天 3 元
            } else {  // 逾期 2 到 5 天
                return 2 * x;  // 每天 2 元
            }
        };

        int ans = 0;  // 累加总罚款
        for (int x : daysLate) {  // 遍历每本书的逾期天数
            ans += f(x);  // 加上这本书的罚款
        }
        return ans;  // 返回罚款总额
    }
};
