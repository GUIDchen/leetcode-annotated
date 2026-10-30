// 题目：1189. “气球” 的最大数量（Maximum Number of Balloons）
// 思路：先统计 26 个字母的出现次数，把需要两份的 o、l 折半，再对 b/a/l/o/n 取最小值，短板决定能拼几个 "balloon"。
// 时间复杂度：O(n + 5)，只需扫一遍 text；空间复杂度：O(1)，常数大小的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxNumberOfBalloons(string text) {  // text：可任意打乱使用，问最多能拼出多少个 "balloon"
        int cnt[26]{};  // 26 个字母的计数器，花括号初始化保证全部为 0
        for (char c : text) {  // 遍历字符串的每个字符
            ++cnt[c - 'a'];  // 用 c - 'a' 把字母映射到 0~25 的下标并计数
        }  // 计数循环结束
        cnt['o' - 'a'] >>= 1;  // "balloon" 里有两个 o，所以可用个数先折半（右移一位等于除以 2）
        cnt['l' - 'a'] >>= 1;  // 同理 l 也需要两个，同样折半
        int ans = 1 << 30;  // ans 先取一个足够大的数，作为取最小值的初值
        string t = "balon";  // 每个气球恰好需要这 5 种字母（o、l 已折算成「份数」）
        for (char c : t) {  // 遍历这 5 种关键字母
            ans = min(ans, cnt[c - 'a']);  // 取各种字母可用份数的下界，短板决定最终能拼几个
        }  // 循环结束
        return ans;  // ans 就是能拼出的最大气球数
    }  // 方法结束
};  // 类定义结束