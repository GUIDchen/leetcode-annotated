// 题目：3211. 生成不含相邻零的二进制字符串（Generate Binary Strings Without Adjacent Zeros）
// 思路：DFS 逐位尝试填 0/1，只有首位或上一位为 1 时才允许填 0，递归到长度 n 即得到一个合法串。
// 时间复杂度：O(n · F(n))，结果个数为斐波那契量级；空间复杂度：O(n)，递归与回溯路径深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> validStrings(int n) {  // n：目标字符串长度
        vector<string> ans;  // 收集所有合法的二进制字符串
        string t;  // 回溯路径，保存当前已构造的前缀
        auto dfs = [&](this auto&& dfs, int i) {  // C++23 显式对象参数的递归 lambda；i 为当前要填的位置
            if (i >= n) {  // 已经填满 n 位
                ans.emplace_back(t);  // 当前前缀就是一个合法解，加入答案
                return;  // 结束本层递归
            }
            for (int j = 0; j < 2; ++j) {  // 依次尝试填入 0 和 1
                if ((j == 0 && (i == 0 || t[i - 1] == '1')) || j == 1) {  // 填 0 要求是首位或上一位为 1；填 1 永远合法
                    t.push_back('0' + j);  // 把字符 '0' 或 '1' 追加到路径末尾
                    dfs(i + 1);  // 递归填下一位
                    t.pop_back();  // 回溯，撤销本位的选择
                }
            }
        };  // lambda 定义结束
        dfs(0);  // 从第 0 位开始搜索
        return ans;  // 返回全部合法字符串
    }
};
