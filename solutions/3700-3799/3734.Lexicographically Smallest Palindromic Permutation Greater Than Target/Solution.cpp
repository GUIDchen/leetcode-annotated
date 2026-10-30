// 3734. 大于目标字符串的最小字典序回文排列 / Lexicographically Smallest Palindromic Permutation Greater Than Target
// 核心思路：回文由左半边唯一决定，因此只在左半边做 next-permutation 式贪心：先尽量沿用 target 左半的前缀，再从最靠右的位置把某位换成更大字母，剩余位置按字母序最小填充，拼成回文后校验是否大于 target。
// 复杂度：时间 O(26 * n^2)（每个候选位置重建一次左半），空间 O(n + 26)。
class Solution {  // 定义 LeetCode 解法类
public:  // 公有接口
    string buildPalindrome(string left, char middle, int n) {  // 用左半边、中位字符与总长度拼出完整回文
        string right = left;  // 复制左半边作为右半边
        reverse(right.begin(), right.end());  // 反转得到镜像的右半边
        if (n % 2 == 1) {  // 总长度为奇数时需要中位字符
            return left + string(1, middle) + right;  // 左半 + 中位 + 右半
        }  // 分支结束
        return left + right;  // 偶数长度直接左右拼接
    }  // 辅助方法结束

    string lexPalindromicPermutation(string s, string target) {  // 求字典序大于 target 的最小回文排列
        int n = s.size();  // 字符串长度
        vector<int> freq(26, 0);  // 统计每个字母的出现次数
        for (char c : s) {  // 遍历原串
            freq[c - 'a']++;  // 计入当前字母
        }  // 统计结束

        int oddCount = 0;  // 出现奇数次的字母个数
        char middle = 0;  // 唯一的奇数频次字母会放在正中间
        for (int i = 0; i < 26; i++) {  // 遍历 26 个字母
            if (freq[i] % 2 == 1) {  // 该字母出现奇数次
                oddCount++;  // 奇数频次计数加一
                middle = char('a' + i);  // 记为中位字符候选
            }  // 分支结束
        }  // 扫描结束
        if (oddCount > 1) {  // 多于一个奇频字母时无法构成回文
            return "";  // 返回空串表示无解
        }  // 分支结束

        vector<int> halfFreq(26, 0);  // 左半边每个字母可用的次数
        for (int i = 0; i < 26; i++) {  // 遍历 26 个字母
            halfFreq[i] = freq[i] / 2;  // 一半放左边，另一半镜像放右边
        }  // 计算结束

        int halfLen = n / 2;  // 左半边的长度
        string targetHalf = target.substr(0, halfLen);  // 只取 target 的左半边做比较
        vector<int> remaining = halfFreq;  // 剩余可用字母计数
        string prefix = "";  // 已构造出的左半前缀
        int matched = 0;  // 与 target 左半边已匹配的字符数
        for (int i = 0; i < halfLen; i++) {  // 贪心地按 target 左半边逐位匹配
            int x = targetHalf[i] - 'a';  // 当前位需要的字母
            if (remaining[x] == 0) {  // 该字母已经用完
                break;  // 无法继续沿用 target 前缀，退出匹配
            }  // 分支结束
            prefix += targetHalf[i];  // 把该字符追加到前缀
            remaining[x]--;  // 消耗一个该字母
            matched++;  // 匹配长度加一
        }  // 匹配结束

        if (matched == halfLen) {  // 左半边与 target 左半边完全一致
            string candidate = buildPalindrome(prefix, middle, n);  // 构造对应的完整回文
            if (candidate > target) {  // 回文整体字典序大于 target
                return candidate;  // 它就是最小候选，直接返回
            }  // 分支结束
        }  // 分支结束

        int lastPosition = matched == halfLen ? halfLen - 1 : matched;  // 从最靠右的、仍可改动的位置开始回溯
        for (int pos = lastPosition; pos >= 0; pos--) {  // 逐位尝试把该位换成更大的字母
            vector<int> rem = halfFreq;  // 重置剩余字母计数
            bool validPrefix = true;  // 前缀是否可行的标记
            for (int i = 0; i < pos; i++) {  // 重放 pos 之前的前缀
                int x = targetHalf[i] - 'a';  // 前缀需要的字母
                if (rem[x] == 0) {  // 该字母数量不足
                    validPrefix = false;  // 标记前缀不可行
                    break;  // 提前退出重放
                }  // 分支结束
                rem[x]--;  // 消耗该字母
            }  // 重放结束
            if (!validPrefix) {  // 前缀不合法
                continue;  // 换更靠左的位置继续尝试
            }  // 分支结束

            int targetChar = targetHalf[pos] - 'a';  // 该位置在 target 中的字符
            for (int c = targetChar + 1; c < 26; c++) {  // 寻找比它更大的可用字母
                if (rem[c] == 0) {  // 该字母不可用
                    continue;  // 尝试下一个字母
                }  // 分支结束
                string left = targetHalf.substr(0, pos);  // 保留位置 pos 之前的前缀
                left += char('a' + c);  // 放入一个更大的字母
                rem[c]--;  // 消耗一个该字母
                for (int x = 0; x < 26; x++) {  // 剩余位置按字母序从小到大填充
                    while (rem[x] > 0) {  // 该字母还有剩余
                        left += char('a' + x);  // 追加该字母
                        rem[x]--;  // 消耗一个
                    }  // 内层填充结束
                }  // 填充结束
                string candidate = buildPalindrome(left, middle, n);  // 拼出完整回文
                if (candidate > target) {  // 确认字典序大于 target
                    return candidate;  // 字母从小到大枚举，第一个满足的即最小
                }  // 分支结束
                rem = halfFreq;  // 恢复剩余计数，尝试同位置的下一个字母
                for (int i = 0; i < pos; i++) {  // 重新扣掉前缀消耗的字母
                    rem[targetHalf[i] - 'a']--;  // 扣减前缀用掉的字母
                }  // 恢复结束
            }  // 字母枚举结束
        }  // 位置枚举结束

        return "";  // 所有位置都无法构造，返回空串
    }  // 方法结束
};  // 类定义结束
