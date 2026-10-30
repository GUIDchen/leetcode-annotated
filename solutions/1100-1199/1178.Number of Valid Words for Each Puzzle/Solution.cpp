// 题目：1178. 猜字谜（Number of Valid Words for Each Puzzle）
// 思路：把每个单词压成 26 位字母集合掩码并计数；对每个谜面求出掩码后枚举其全部子集，
//       只要子集含有谜面首字母，该掩码上的单词都合法。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {  // words 为候选词表，puzzles 为字谜列表
        unordered_map<int, int> cnt;  // 哈希表：键是字母集合掩码，值是该掩码对应的单词个数
        for (auto& w : words) {  // 逐个单词压缩成掩码
            int mask = 0;  // mask 的第 b 位为 1 表示该词含字母 b
            for (char& c : w) {  // 遍历单词中的每个字符
                mask |= 1 << (c - 'a');  // 把当前字母对应位置为 1（重复字母不影响结果）
            }  // 单词字符处理完毕
            cnt[mask]++;  // 相同字母集合的单词合并计数，便于后面按掩码批量取数
        }  // 所有单词统计完毕
        vector<int> ans;  // 按谜面顺序保存答案
        for (auto& p : puzzles) {  // 逐个谜面处理
            int mask = 0;  // 重新构造当前谜面的字母集合掩码
            for (char& c : p) {  // 遍历谜面的每个字符
                mask |= 1 << (c - 'a');  // 置入对应字母位
            }  // 谜面掩码构造完成
            int x = 0;  // x 累计当前谜面合法的单词数
            int i = p[0] - 'a';  // i 是谜面首字母的位号：合法单词必须包含它
            for (int j = mask; j; j = (j - 1) & mask) {  // 枚举 mask 的所有非空子集，(j-1)&mask 保证只降不增且始终是子集
                if (j >> i & 1) {  // 子集若不含首字母则该类单词不合法，跳过
                    x += cnt[j];  // 累加该掩码上记录的单词数
                }  // 子集枚举结束
            }  // 答案写入结果数组，顺序与 puzzles 一致
            ans.push_back(x);  // 所有谜面处理完毕
        }  // 返回每个谜面的合法单词数
        return ans;  // 方法体结束
    }  // 题解类结束
};