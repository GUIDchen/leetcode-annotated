// 题目：784. 字母大小写全排列（Letter Case Permutation）
// 思路：按位置 DFS，每位先沿用原字符递归到底得到一种排列；若该位是字母，再把它切换大小写（异或 32）递归一次。翻转是对合操作，每个位置每层只翻一次，因此回溯时不还原也不会影响其他分支。
// 时间复杂度：O(n·2^n)，结果本身就是这个量级；空间复杂度：O(n)，递归栈深度加工作副本。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> letterCasePermutation(string s) {  // s：输入字符串；返回字母大小写全排列（数字保持原样）
        string t = s;  // t：可修改的工作副本，dfs 中原地翻转字符
        vector<string> ans;  // ans：收集所有排列结果
        auto dfs = [&](this auto&& dfs, int i) -> void {  // 递归 lambda：从第 i 位开始决定该位取原样还是切换大小写；this auto&& 支持自调用
            if (i >= t.size()) {  // i 越过末尾，说明已经凑齐一个完整排列
                ans.push_back(t);  // 把当前字符串存入结果集
                return;  // 结束本分支
            }
            dfs(i + 1);  // 先按原字符把后面的位置递归处理完
            if (isalpha(t[i])) {  // 只有字母才有另一种大小写形态，数字不能翻转
                t[i] ^= 32;  // 异或 32：ASCII 中大小写字母恰好只差这一位，一次操作完成大小写互换
                dfs(i + 1);  // 切换后再递归一次，得到这一位取另一形态的所有排列
            }
        };
        dfs(0);  // 从第 0 位开始搜索
        return ans;  // 返回全部排列
    }  // letterCasePermutation 方法结束
};  // Solution 类定义结束
