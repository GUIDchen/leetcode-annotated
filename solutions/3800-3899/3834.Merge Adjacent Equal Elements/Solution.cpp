// 3834. 合并相邻且相等的元素 / Merge Adjacent Equal Elements（中等）
// 核心思路：用栈维护已处理好的前缀；每来一个元素就压栈，若栈顶两个元素相等则弹出并压入二者之和，并持续循环，因为新和可能与新的栈顶再次相等。
// 复杂度：每个元素最多入栈一次，摊还时间 O(n)，空间 O(n)。
class Solution {  // 反复合并相邻且相等的元素，直到无法再合并
public:  // 对外接口区
    vector<long long> mergeAdjacent(vector<int>& nums) {  // 返回合并完成后的数组（和可能超过 int 范围，故用 long long）
        vector<long long> stk;  // 用栈保存已经合并好的结果前缀
        for (int x : nums) {  // 从左到右逐个处理元素
            stk.push_back(x);  // 先把当前元素压栈
            while (stk.size() > 1 && stk.back() == stk[stk.size() - 2]) {  // 只要栈顶两个元素相等就继续合并（合并后的和可能与新栈顶再次相等）
                long long a = stk.back();  // 取出栈顶元素
                stk.pop_back();  // 弹出栈顶
                long long b = stk.back();  // 再取出新的栈顶元素
                stk.pop_back();  // 弹出第二个元素
                stk.push_back(a + b);  // 把两数之和压回栈中，继续参与后续合并判断
            }
        }
        return stk;  // 栈中内容即为最终结果
    }
};
