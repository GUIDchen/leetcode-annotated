// 题目：2468. 根据限制分割消息（Split Message Based on Limit）
// 核心思路：枚举段数 k，用前缀量 sa（编号位数和）、sb（编号位数×k）、sc（标记里 3 个符号×k）算标记总开销，若 k*limit 扣掉开销仍能装下全文就按顺序切分并拼上 <j/k> 标记；取最小的可行 k。
// 时间复杂度：O(n^2)，外层枚举 k、内层切分都不超过 n；空间复杂度：O(n)，存放结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> splitMessage(string message, int limit) {  // message 是原文，limit 是每段（含编号标记）允许的最大长度
        int n = message.size();  // 原文字符数
        int sa = 0;  // sa：编号 1..k 的十进制位数之和，随 k 递增累加
        vector<string> ans;  // 存放切分结果，找不到方案时保持为空
        for (int k = 1; k <= n; ++k) {  // 枚举段数 k，最多 n 段（每段至少一个字符）
            int lk = to_string(k).size();  // k 的十进制位数，用来估算编号占用多少字符
            sa += lk;  // 把 k 的位数累加进 sa，得到 1..k 的位数总和
            int sb = lk * k;  // sb：k 个编号各自的位数占用（都按 k 的位数 lk 估算）
            int sc = 3 * k;  // sc：每个标记里的 '<'、'/'、'>' 共 3 个字符，k 段合计 3k
            if (k * limit - (sa + sb + sc) >= n) {  // 总容量减去标记开销后，剩下的位置是否够放全文
                int i = 0;  // i：已经取走的原文字符数
                for (int j = 1; j <= k; ++j) {  // 逐段生成第 j 段
                    string tail = "<" + to_string(j) + "/" + to_string(k) + ">";  // 构造编号标记，形如 <j/k>
                    string t = message.substr(i, limit - tail.size()) + tail;  // 取本段能放下的原文前缀，再拼上标记
                    ans.emplace_back(t);  // 把这一段加入结果
                    i += limit - tail.size();  // 指针前移，跳过本段已消费的原文
                }
                break;  // 第一个可行的 k 就是最小段数，按题目要求取它
            }
        }
        return ans;  // 返回切分结果；没有可行方案时是空数组
    }
};