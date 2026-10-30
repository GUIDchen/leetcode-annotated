// 题目：2337. 移动片段得到字符串（Move Pieces to Obtain a String）
// 核心思路：忽略空位 '_' 后两个字符串的非空字符序列必须完全相同；再用原下标比对方向——'L' 只能左移（开始下标不小于目标下标），'R' 只能右移（开始下标不大于目标下标）。
// 时间复杂度：O(n)，两次扫描加一次逐项比对；空间复杂度：O(n)，存放非空字符及其下标。
using pii = pair<int, int>;  // 类型别名：first 表示字符种类（1='L'，2='R'），second 表示它在原串中的下标

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canChange(string start, string target) {  // start：初始字符串；target：目标字符串；返回能否通过移动片段得到 target
        auto a = f(start);  // 抽出 start 中所有非空位字符及其下标，保持原有先后顺序
        auto b = f(target);  // 抽出 target 中所有非空位字符及其下标
        if (a.size() != b.size()) return false;  // 片段数量不同，无论怎么移动都不可能一致
        for (int i = 0; i < a.size(); ++i) {  // 按顺序逐个比对两边的第 i 个片段
            auto x = a[i], y = b[i];  // x 是 start 里的片段，y 是 target 里对应位置的片段
            if (x.first != y.first) return false;  // 字符种类不同（'L' 与 'R' 互换）则不可能通过滑动得到
            if (x.first == 1 && x.second < y.second) return false;  // 'L' 只能向左移动，所以 start 中的下标必须不小于 target 中的下标
            if (x.first == 2 && x.second > y.second) return false;  // 'R' 只能向右移动，所以 start 中的下标必须不大于 target 中的下标
        }  // 下标 i 自增，回到循环条件比对下一对片段
        return true;  // 所有片段都满足约束，说明可以变换成功
    }  // canChange 方法结束

    vector<pair<int, int>> f(string s) {  // 辅助函数：把字符串里所有 'L'、'R' 连同下标抽成有序列表
        vector<pii> res;  // res 保存 (种类, 下标) 二元组
        for (int i = 0; i < s.size(); ++i) {  // 从左到右扫描字符串，保证下标递增
            if (s[i] == 'L')  // 遇到 'L' 片段
                res.push_back({1, i});  // 种类记为 1，并记下当前位置
            else if (s[i] == 'R')  // 遇到 'R' 片段
                res.push_back({2, i});  // 种类记为 2，并记下当前位置
        }  // 扫描结束
        return res;  // 返回抽出的片段序列
    }  // f 方法结束
};  // Solution 类结束