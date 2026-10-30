// 题目：1441. 用栈操作构建数组（Build an Array With Stack Operations）
// 思路：让 cur 从 1 递增，遇到 target 里没有的数字就压入再立刻弹出，遇到需要的数字只压入。
// 时间复杂度：O(n)，最多 2n 次操作；空间复杂度：O(n)，结果最多 2n 个字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> buildArray(vector<int>& target, int n) {  // target 是目标数组，n 是可用整数的上界
        vector<string> ans;  // ans 保存要返回的操作序列
        int cur = 1;  // 下一个准备压入栈的整数，从 1 开始
        for (int x : target) {  // 按顺序处理 target 的每个元素 x
            while (cur < x) {  // cur 还没到 x，说明 cur 不在 target 中，需要跳过它
                ans.push_back("Push");  // 先压入 cur
                ans.push_back("Pop");  // 立刻弹出，栈恢复原状，等于丢弃 cur
                ++cur;  // 继续尝试下一个整数
            }
            ans.push_back("Push");  // x 是需要的数字，一次 Push 让它留在栈中
            ++cur;  // 下一个数字从 x+1 开始
        }
        return ans;  // 返回完整的操作序列
    }
};
