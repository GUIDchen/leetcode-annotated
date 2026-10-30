// 题目：893. 特殊等价字符串组（Groups of Special-Equivalent Strings）
// 核心思路：两个字符串特殊等价，当且仅当偶数位字符集合与奇数位字符集合分别相同；各自排序拼成规范键去重。
// 时间复杂度：O(n·m log m)，m 为串长，每串两次排序；空间复杂度：O(n·m)，集合保存全部规范键。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSpecialEquivGroups(vector<string>& words) {  // words：字符串数组
        unordered_set<string> s;  // 集合保存每组规范化后的键，天然去重
        for (auto& word : words) {  // 逐个字符串处理
            string a = "", b = "";  // a 收集奇数位字符，b 收集偶数位字符
            for (int i = 0; i < word.size(); ++i) {  // 逐位扫描
                if (i & 1)  // 下标为奇数
                    a += word[i];  // 放入奇数位桶
                else  // 下标为偶数
                    b += word[i];  // 放入偶数位桶
            }
            sort(a.begin(), a.end());  // 奇数位字符排序，得到只看字符多重集的规范形式
            sort(b.begin(), b.end());  // 偶数位字符排序同理
            s.insert(a + b);  // 两部分拼接成唯一键：特殊等价的串会得到同一个键
        }
        return s.size();  // 集合大小就是组数
    }
};  // 类定义结束