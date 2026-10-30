// 题目：1944. 队列中可以看到的人数（Number of Visible People in a Queue）
// 思路：从右往左扫，维护一个从栈底到栈顶递减的单调栈；比当前人矮的全部出栈并各计一次可见，栈若还不空，栈顶那个更高的人再计一次。
// 时间复杂度：O(n)，每个身高最多入栈出栈一次；空间复杂度：O(n)，栈与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> canSeePersonsCount(vector<int>& heights) {  // heights：每个人的身高，返回每人向右能看到的人数
        int n = heights.size();  // n 是人数
        vector<int> ans(n);  // ans 初值全 0，逐位累加能看见的人数
        stack<int> stk;  // 单调栈，保存从右往左尚未被遮挡的身高，从栈底到栈顶递减
        for (int i = n - 1; ~i; --i) {  // 从右往左遍历；~i 等价于 i >= 0，用位取反省掉一次比较（i 为当前人下标）
            while (stk.size() && stk.top() < heights[i]) {  // 栈顶身高矮于当前人：他看得见，而且会被当前人挡住
                ++ans[i];  // 当前人能看到这一个
                stk.pop();  // 弹出他，继续检查更靠右的下一个候选
            }
            if (stk.size()) {  // 栈里还有更高的人，当前人还能看到他，之后视线被彻底挡住
                ++ans[i];  // 再计一个可见
            }
            stk.push(heights[i]);  // 把当前身高入栈，作为更左边的人向右看时的候选
        }
        return ans;
    }
};