// 3692. Majority Frequency Characters（3692. 众数频率字符）
// 核心思路：先统计每个字母的出现次数，把“出现次数相同的字母”聚成一组；在所有组中取组大小最大者（并列时取出现次数更大的那组），组内字母按字典序拼接返回。
// 复杂度：时间 O(n + 26 log 26)，空间 O(26)，n 为字符串长度。
class Solution {  // 定义题解类
public:  // 公有接口
    string majorityFrequencyGroup(string s) {  // 主函数：返回“众数频率组”里的所有字母（按字典序拼接）
        vector<int> cnt(26, 0);  // cnt 统计 26 个小写字母各自的出现次数
        for (char c : s) {  // 逐个字符统计
            ++cnt[c - 'a'];  // 对应字母计数加一（'a' 映射到下标 0）
        }  // 循环结束

        unordered_map<int, string> f;  // 用“出现次数 -> 字母串”把同频字母聚成一组
        for (int i = 0; i < 26; ++i) {  // 遍历 26 个小写字母
            if (cnt[i] > 0) {  // 只处理出现过的字母
                f[cnt[i]].push_back('a' + i);  // 把该字母追加到对应频率的组里（i 递增，天然是字典序）
            }  // if 分支结束
        }  // 循环结束

        int mx = 0, mv = 0;  // mx 记录最大组大小，mv 记录该组的出现频率
        string ans;  // ans 存放最终选中的那组字母
        for (auto& e : f) {  // 遍历所有频率分组
            int v = e.first;  // v 是这一组的出现频率
            string& cs = e.second;  // cs 是这一组里的字母串
            if (mx < (int) cs.size() || (mx == (int) cs.size() && mv < v)) {  // 组更大则更新；组大小相同则取频率更大者
                mx = cs.size();  // 更新最大组大小
                mv = v;  // 更新对应的出现频率
                ans = cs;  // 记录该组的字母串
            }  // if 分支结束
        }  // 循环结束
        return ans;  // 返回众数频率组
    }  // 主函数结束
};  // 类定义结束
