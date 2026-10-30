// 题目：2262. 字符串的总引力（Total Appeal of A String）
// 思路：按子串右端点递推。设 t 为所有以 i 结尾的子串引力之和，字符 c=s[i] 只在起点落在它上次出现位置之后的那些子串里第一次出现，共 i-pos[c] 个，故 t += i-pos[c]，再把 t 累加进答案。
// 时间复杂度：O(n)，一趟扫描；空间复杂度：O(1)，只用了 26 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long appealSum(string s) {  // s：输入字符串；答案最大可达 O(n^2) 级别，用 long long 防溢出
        long long ans = 0, t = 0;  // ans 累加全部子串的引力；t 是以当前位置 i 结尾的所有子串的引力之和
        vector<int> pos(26, -1);  // pos[ch]：字符 ch 最近一次出现的下标，-1 表示尚未出现过
        for (int i = 0; i < s.size(); ++i) {  // 从左到右枚举所有子串的结束位置 i
            int c = s[i] - 'a';  // 把字符映射成 0~25 的整数下标
            t += i - pos[c];  // 起点在 pos[c] 之后（含起点为 i）的 i-pos[c] 个子串因 c 首次出现而各多得 1 点引力
            ans += t;  // 把以 i 结尾的全部子串引力一次性累加进总答案
            pos[c] = i;  // 更新该字符的最新出现位置，供后面的下标复用
        }
        return ans;  // 返回所有子串的引力总和
    }
};