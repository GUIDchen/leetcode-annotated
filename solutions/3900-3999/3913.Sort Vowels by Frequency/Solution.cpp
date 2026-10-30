// 3913. Sort Vowels by Frequency | 按频率对元音排序（中等）
// 核心思路：先统计每个元音字母出现的次数，再按频次降序给出现过的元音字母排序；然后把排序后的字母依次填回原串中那些“元音位置”（非元音位置保持不动），每填写一个就把对应频次减一，配额用完就换下一个字母。
// 复杂度：时间 O(n + V log V)，V 至多为 5（元音种类数）；空间 O(n + V)，用于结果串与频次表。
class Solution {  // 定义题解类
public:  // 公有接口
    string sortVowels(string s) {  // 把元音字母按出现频率降序重排，非元音字符保持原位
        unordered_set<char> st = {'a', 'e', 'i', 'o', 'u'};  // 元音字符集合（题目只考虑小写）
        vector<char> vowels;  // 出现过的元音字母，每个字母只存一份
        unordered_map<char, int> cnt;  // 每个元音字母的剩余出现次数
        for (char c : s) {  // 第一遍扫描：统计元音频次
            if (!st.count(c)) {  // 当前字符不是元音
                continue;  // 跳过，保持原位
            }  // if 结束
            if (!cnt.count(c)) {  // 第一次遇到这个元音字母
                vowels.push_back(c);  // 记录该元音字母（相同字母只记一次）
            }  // if 结束
            cnt[c]++;  // 该元音的频次加一
        }  // 第一遍扫描结束
        sort(vowels.begin(), vowels.end(), [&](char a, char b) {  // 按频次降序排列这些元音字母
            return cnt[a] > cnt[b];  // 频次大的排在前面（严格大于，相等时顺序不作要求）
        });  // 排序回调结束
        string ans = s;  // 复制原串作为答案的基底，非元音位置直接沿用
        int i = 0;  // 指向当前正在填写的元音字母
        for (int k = 0; k < s.size(); k++) {  // 第二遍扫描：把排好序的元音依次写回元音位置
            if (!st.count(s[k])) {  // 原串当前位置不是元音
                continue;  // 跳过，该位置内容不变
            }  // if 结束
            char c = vowels[i];  // 取出当前应该填入的元音字母
            ans[k] = c;  // 写入该位置
            if (--cnt[c] == 0) {  // 该字母的剩余配额减一，减到 0 说明用完了
                i++;  // 换到下一个元音字母
            }  // if 结束
        }  // 第二遍扫描结束
        return ans;  // 返回重排后的字符串
    }  // 方法结束
};  // 类定义结束
