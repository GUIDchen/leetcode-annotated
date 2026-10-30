// 题目：1111. 有效括号的嵌套深度（Maximum Nesting Depth of Two Valid Parentheses Strings）
// 思路：按当前深度的奇偶性分组：'(' 用入栈前的深度判奇偶，')' 用出栈后的深度判奇偶，使两个子序列各自深度约为原来的一半。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，ans 保存每个位置的分组编号。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题接口
    vector<int> maxDepthAfterSplit(string seq) {  // seq 是题目保证合法的括号序列
        int n = seq.size();  // 序列长度
        vector<int> ans(n);  // 答案：ans[i] 取 0 或 1，表示第 i 个字符分配给哪个子序列
        for (int i = 0, x = 0; i < n; ++i) {  // i 是下标，x 是当前嵌套深度
            if (seq[i] == '(') {  // 左括号会让深度加一
                ans[i] = x++ & 1;  // 用自增前的深度奇偶决定分组，然后再把深度加一
            } else {  // 右括号会让深度减一
                ans[i] = --x & 1;  // 先减一回到配对左括号的深度，保证同一对括号分到同一组
            }
        }
        return ans;  // 返回每个位置的子序列编号
    }
};