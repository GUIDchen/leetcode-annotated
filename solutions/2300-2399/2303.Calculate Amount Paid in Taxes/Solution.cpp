// 题目：2303. 计算应缴税款总额（Calculate Amount Paid in Taxes）
// 思路：按分档区间逐档累加，每档应税额 = max(0, min(收入, 本档上界) - 上一档上界)，乘以该档百分比，最后除以 100。
// 时间复杂度：O(n)，n 为档数，只遍历一次；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double calculateTax(vector<vector<int>>& brackets, int income) {  // brackets：按上界递增的分档 [上界, 百分比]；income：总收入
        int ans = 0, prev = 0;  // ans 累计税款（单位是“分”，整数运算避免浮点误差）；prev 记录上一档的上界
        for (auto& e : brackets) {  // 按顺序逐档处理收入区间
            int upper = e[0], percent = e[1];  // 本档的上界与税率百分比
            ans += max(0, min(income, upper) - prev) * percent;  // 落在本档内的收入 = min(income, upper) - prev，max(0, ...) 表示收入没到本档时为 0
            prev = upper;  // 把本档上界记为下一档的起点 prev
        }  // 档遍历结束
        return ans / 100.0;  // 除以 100，把按百分比累加出的“分”换算成元（100.0 保证是浮点除法）
    }  // 方法结束
};  // 类定义结束