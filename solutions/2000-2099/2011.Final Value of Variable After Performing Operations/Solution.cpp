// 题目：2011. 执行操作后的变量值（Final Value of Variable After Performing Operations）
// 思路：每个操作串的第 2 个字符是 '+' 就加 1，否则减 1，一次遍历累加得到最终值。
// 时间复杂度：O(n)，n 为操作个数；空间复杂度：O(1)，只用常数额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int finalValueAfterOperations(vector<string>& operations) {  // operations：操作字符串数组；返回变量 X 的最终值
        int ans = 0;  // ans 记录 X 的当前值，初始为 0
        for (auto& s : operations) {  // 按引用遍历每个操作串，避免字符串拷贝
            ans += s[1] == '+' ? 1 : -1;  // s[1] 是 '+' 就加 1，否则减 1
        }  // 循环体结束
        return ans;  // 返回全部操作执行完后 X 的值
    }  // 方法结束
};  // 类定义结束
