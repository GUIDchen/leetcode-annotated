// 4026. 工位的最大间隔 / Maximum Gap Between Stations
// 核心思路：先从右向左贪心求出 skill 每个字符在 station 中最靠右的匹配位置 suf，再从左向右贪心求最靠左的匹配位置 pre，枚举相邻两个字符取 suf[i+1] - pre 的最大值。
// 复杂度：时间 O(n + m)，空间 O(n)（n 为 skill 长度，m 为 station 长度）。
class Solution {  // 题解类定义
public:  // 公有成员：判题器调用的接口
    int maximumGap(string skill, string station) {  // 返回把 skill 作为子序列匹配到 station 时，相邻两个匹配位置之间的最大间隔
        int n = skill.size();  // skill 的长度
        int m = station.size();  // station 的长度

        vector<int> suf(n);  // suf[i] 记录 skill[i] 在 station 中最靠右的可行匹配位置（下标 0 不使用）
        int j = m - 1;  // 从 station 末尾开始扫描的指针

        for (int i = n - 1; i > 0; i--) {  // 从右向左为 skill 的每个字符寻找最靠右的匹配位置
            while (station[j] != skill[i]) {  // 指针左移，直到找到与 skill[i] 相同的字符
                j--;  // 指针继续左移一位
            }  // 结束内层查找

            suf[i] = j;  // 记录该字符最靠右的匹配位置
            j--;  // 指针再左移一格，保证匹配位置严格递减
        }  // 结束倒序匹配

        int ans = 0;  // 记录最大间隔
        int pre = 0;  // 从左向右贪心匹配的指针

        for (int i = 0; i < n - 1; i++) {  // 枚举相邻的两个 skill 字符（i 与 i+1）
            while (station[pre] != skill[i]) {  // 指针右移，直到找到与 skill[i] 相同的字符
                pre++;  // 指针继续右移一位
            }  // 结束内层查找

            ans = max(ans, suf[i + 1] - pre);  // 让 skill[i] 尽量靠左、skill[i+1] 尽量靠右，得到该处的最大间隔
            pre++;  // 指针右移一格，保证下一个匹配位置严格递增
        }  // 结束正序匹配

        return ans;  // 返回最大间隔
    }  // 结束函数
};  // 结束类定义