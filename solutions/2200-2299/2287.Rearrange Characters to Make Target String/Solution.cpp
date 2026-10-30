// 题目：2287. 重排字符形成目标字符串（Rearrange Characters to Make Target String）
// 核心思路：分别统计 s 与 target 中各字母的个数，某个字母能拼出的份数是 cnt1[i] / cnt2[i]，对 target 中出现的所有字母取最小值即可。
// 时间复杂度：O(|s| + |target| + 26)，两次线性扫描加一次字母表枚举；空间复杂度：O(1)，两个定长 26 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int rearrangeCharacters(string s, string target) {  // s：可重排的源字符串；target：目标字符串；返回最多能拼出几个 target
        int cnt1[26]{};  // s 中各字母的出现次数，值初始化为 0
        int cnt2[26]{};  // target 中各字母的出现次数，值初始化为 0
        for (char& c : s) {  // 遍历 s 的每个字符
            ++cnt1[c - 'a'];  // 字母映射到 0..25 的下标，计数加一
        }  // s 统计完毕
        for (char& c : target) {  // 遍历 target 的每个字符
            ++cnt2[c - 'a'];  // 累加该字母在 target 中的需求量
        }  // target 统计完毕
        int ans = 100;  // 答案上界是 100（|s| 不超过 100），先取足够大的初值
        for (int i = 0; i < 26; ++i) {  // 枚举 26 个小写字母
            if (cnt2[i]) {  // 只处理 target 中出现过的字母
                ans = min(ans, cnt1[i] / cnt2[i]);  // 该字母能支撑的份数，与当前答案取小
            }  // 判断结束
        }  // 枚举结束
        return ans;  // 返回最多能拼出的份数
    }  // 方法结束
};  // 类定义结束