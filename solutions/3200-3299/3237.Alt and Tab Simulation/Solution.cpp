// 题目：3237. Alt 和 Tab 模拟（Alt and Tab Simulation）
// 思路：从后往前扫描 queries，越晚被按下的窗口越靠前；用布尔数组去重，再把没出现过的窗口按原顺序接在末尾。
// 时间复杂度：O(n + q)，n 为窗口数、q 为按键次数；空间复杂度：O(n)，布尔数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> simulationResult(vector<int>& windows, vector<int>& queries) {  // windows：初始窗口顺序；queries：每次 Alt+Tab 按下的窗口编号
        int n = windows.size();  // 窗口数量，也是去重数组需要的上界
        vector<bool> s(n + 1);  // s[x] 表示窗口 x 是否已经进入答案，下标直接用窗口编号
        vector<int> ans;  // 按最终 Z 序收集结果
        for (int i = queries.size() - 1; ~i; --i) {  // 从最后一个按键往前扫：越晚按下，在最终顺序里越靠前
            int q = queries[i];  // 本次按键要激活的窗口编号
            if (!s[q]) {  // 只有第一次遇到时才放进答案
                s[q] = true;  // 标记该窗口已出现
                ans.push_back(q);  // 倒序扫描时按顺序追加，得到的正好是正常的从前到后顺序
            }  // if 结束
        }  // for 结束
        for (int w : windows) {  // 补上从未被按过的窗口，保持它们原来的相对顺序
            if (!s[w]) {  // 只补没有出现在答案里的
                ans.push_back(w);  // 追加到末尾
            }  // if 结束
        }  // for 结束
        return ans;  // 返回最终的窗口顺序
    }  // 方法结束
};  // 类结束
