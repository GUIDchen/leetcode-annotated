// 3438. 找到字符串中合法的相邻数字 / Find Valid Pair of Adjacent Digits in String
// 核心思路：先统计每个数字出现次数，再顺序扫描相邻数字对，要求两数字不同且各自频次恰等于自身数值。
// 复杂度：时间 O(n)，空间 O(1)（固定 10 个计数桶）。
class Solution {  // 定义题解类
public:  // 公有方法
    string findValidPair(string s) {  // 返回第一个合法相邻数字对，不存在时返回空串
        int cnt[10]{};  // cnt[d] 记录数字 d 的出现次数
        for (char c : s) {  // 遍历字符串统计频次
            ++cnt[c - '0'];  // 字符转数字后计数
        }  // 结束统计循环
        for (int i = 1; i < s.size(); ++i) {  // 枚举相邻数字对（下标 i-1 与 i）
            int x = s[i - 1] - '0';  // 左侧数字
            int y = s[i] - '0';  // 右侧数字
            if (x != y && cnt[x] == x && cnt[y] == y) {  // 两数字不同，且各自频次都等于自身数值
                return s.substr(i - 1, 2);  // 返回该相邻数字对
            }  // 结束判定分支
        }  // 结束扫描循环
        return "";  // 没有合法数字对
    }  // 结束 findValidPair 方法
};  // 结束 Solution 类
