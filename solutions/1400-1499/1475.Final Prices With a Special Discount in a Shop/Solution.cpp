// 题目：1475. 商品折扣后的最终价格（Final Prices With a Special Discount in a Shop）
// 思路：从右往左扫描，维护一个「单调递减」的下标栈；栈顶就是右侧第一个价格不大于当前价格的位置，也就是能享受的折扣。
// 时间复杂度：O(n)，每个元素最多入栈出栈一次；空间复杂度：O(n)，栈的深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> finalPrices(vector<int>& prices) {  // prices：商品原价，返回值直接复用该数组
        stack<int> stk;  // 单调栈：栈底到栈顶的价格递减，栈顶即当前元素右侧最近的不大于它的价格
        for (int i = prices.size() - 1; ~i; --i) {  // 从右往左扫描，保证处理 i 时它右侧的元素都已入栈；~i 即 i != -1
            int x = prices[i];  // 记下当前商品的原价（后面会被就地修改）
            while (!stk.empty() && stk.top() > x) {  // 栈顶价格比当前还高，用不上，弹出
                stk.pop();  // 弹出不可能是折扣来源的价格
            }
            if (!stk.empty()) {  // 栈非空说明右侧存在第一个不大于当前价格的位置
                prices[i] -= stk.top();  // 直接减去该价格，得到折后价
            }
            stk.push(x);  // 把当前价格入栈，供左边更小的元素使用（入栈的是原价）
        }
        return prices;  // 数组已被就地改写为最终价格，直接返回
    }
};
