// 题目：1593. 拆分字符串使唯一子字符串的数目最大（Split a String Into the Max Number of Unique Substrings）
// 思路：回溯枚举每个切分点，用哈希集合判重；当「已用子串数 + 剩余字符数」都不优于当前最优时剪枝。
// 时间复杂度：O(n * 2^n)，最坏枚举所有切分并比较子串；空间复杂度：O(n^2)，集合与递归栈存放子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxUniqueSplit(string s) {  // s 为待拆分的原字符串，返回最多能得到的不同子串个数
        unordered_set<string> st;  // 保存当前切分方案里已经用过的子串，用于判重
        int n = s.size();  // 字符串长度，后面反复用到
        int ans = 0;  // 记录搜索过程中得到的最大不同子串数目
        auto dfs = [&](this auto&& dfs, int i) -> void {  // C++23 显式对象参数递归 lambda：从下标 i 开始继续切分
            if (st.size() + n - i <= ans) {  // 剪枝：剩余字符全部单独成段也超不过现有答案
                return;  // 该分支不可能更优，直接回溯
            }  // 剪枝判断结束
            if (i >= n) {  // 走到字符串末尾，说明完成了一种完整切分
                ans = max(ans, (int) st.size());  // 用当前方案的不同子串数更新答案
                return;  // 到底了，返回上一层
            }  // 越界判断结束
            for (int j = i + 1; j <= n; ++j) {  // 枚举下一段的结束位置 j（区间为左闭右开）
                string t = s.substr(i, j - i);  // 取出本段子串 s[i, j)
                if (!st.contains(t)) {  // C++20 的 contains：该子串此前没出现过才允许切
                    st.insert(t);  // 选择这一段，加入已用集合
                    dfs(j);  // 从 j 继续往后切分
                    st.erase(t);  // 撤销选择，回到搜索前的状态
                }  // 判重分支结束
            }  // 段尾枚举结束
        };  // 递归 lambda 定义结束
        dfs(0);  // 从下标 0 开始搜索
        return ans;  // 返回所有切分方案中的最大数目
    }  // 方法结束
};  // 类结束
