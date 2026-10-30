// 题目：395. 至少有 K 个重复字符的最长子串（Longest Substring with At Least K Repeating Characters）
// 思路：某字符在区间内出现次数不足 k 次时它不可能属于答案，于是以它为界把区间切段，对每段递归求解并取最大。
// 时间复杂度：O(n·Σ)，每层按 26 个字母切段，递归深度至多 n；空间复杂度：O(n)，递归栈最深 n 层。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSubstring(string s, int k) {  // s 是原串，k 要求每种出现的字符在子串内至少重复 k 次
        function<int(int, int)> dfs = [&](int l, int r) -> int {  // 递归处理闭区间 [l, r]，返回该区间内最长合法子串的长度
            int cnt[26] = {0};  // 统计区间内每个小写字母的出现次数，初始全为 0
            for (int i = l; i <= r; ++i) {  // 遍历 [l, r] 统计词频
                cnt[s[i] - 'a']++;  // 字符减去 a 映射到 0..25 后计数
            }
            char split = 0;  // 找一个出现次数不足 k 的字符作为分割符，0 表示没找到
            for (int i = 0; i < 26; ++i) {  // 顺序扫描 26 个字母
                if (cnt[i] > 0 && cnt[i] < k) {  // 出现过但总次数不足 k，它一定不在答案里
                    split = 'a' + i;  // 记下这个字符，作为切分依据
                    break;  // 拿到第一个就够，直接跳出
                }
            }
            if (split == 0) {  // 没有字符违反条件，说明整个区间都合法
                return r - l + 1;  // 整个区间就是一个合法子串
            }
            int i = l;  // i 用来在区间内逐个找出被分割符切开的段
            int ans = 0;  // 记录本层各段答案的最大值
            while (i <= r) {  // 逐段扫描，直到区间末尾
                while (i <= r && s[i] == split) {  // 跳过连续出现的分割符本身
                    ++i;  // 右移越过分割符
                }
                if (i >= r) {  // 剩余不足一个字符，后面不可能再有合法段
                    break;  // 提前结束扫描
                }
                int j = i;  // j 负责找出当前段的右端点
                while (j <= r && s[j] != split) {  // 一直走到下一个分割符或区间末尾
                    ++j;  // 右移扩张当前段
                }
                int t = dfs(i, j - 1);  // 递归求这一段的最长合法子串，注意右端点是 j-1
                ans = max(ans, t);  // 用这一段的结果更新本层答案
                i = j;  // 从分割符位置继续往后扫描
            }
            return ans;  // 返回本层各段的最大长度
        };  // lambda 定义结束
        return dfs(0, s.size() - 1);  // 从整个字符串开始递归，右端点是 size-1
    }
};