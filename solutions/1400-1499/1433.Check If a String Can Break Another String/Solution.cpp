// 题目：1433. 检查一个字符串是否可以打破另一个字符串（Check If a String Can Break Another String）
// 思路：两串排序后逐位比较；排序不改变能否重排，因此只需检查「s1 逐位 >= s2」或反向「s2 逐位 >= s1」。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，排序所需的栈空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkIfCanBreak(string s1, string s2) {  // s1、s2：待比较的两个字符串，长度相同
        sort(s1.begin(), s1.end());  // 排序让同一位上可以比较「第 i 小」的字符，从而判定是否存在可行重排
        sort(s2.begin(), s2.end());  // 对 s2 做同样的排序
        return check(s1, s2) || check(s2, s1);  // 只要有一个方向满足逐位不小于即可；check 内部遇不满足会立即返回
    }  // 方法结束

    bool check(string& s1, string& s2) {  // 辅助函数：判断排序后的 s1 是否逐位 >= s2
        for (int i = 0; i < s1.size(); ++i) {  // 逐位扫描两个字符串
            if (s1[i] < s2[i]) {  // 出现 s1 的某位更小，这个方向就被打破，直接返回 false
                return false;  // 返回失败
            }  // if 结束
        }  // 扫描结束
        return true;  // 每一位都不小于，说明 s1 可以打破 s2
    }  // 辅助函数结束
};  // 类定义结束