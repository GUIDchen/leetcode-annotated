// 3598. 相邻字符串之间的最长公共前缀（Longest Common Prefix Between Adjacent Strings After Removals）
// 核心思路：用有序多重集维护当前所有相邻串对的 LCP，逐一下标执行“删除两对 → 新增跨过被删下标的一对 → 取最大值 → 恢复”的增量维护。
// 复杂度：时间 O(n · L + n log n)，空间 O(n)，其中 L 为字符串长度上界。
class Solution {  // 主解类
public:  // 对外接口
    vector<int> longestCommonPrefix(vector<string>& words) {  // 对每个下标，删除该单词后返回相邻字符串最长公共前缀的最大值
        multiset<int> ms;  // 有序多重集：维护当前所有相邻对的 LCP，支持重复值
        int n = words.size();  // 单词个数
        auto calc = [&](const string& s, const string& t) {  // 计算两个字符串的最长公共前缀长度
            int m = min(s.size(), t.size());  // 最多只需比较到较短串的长度
            for (int k = 0; k < m; ++k) {  // 逐位比较两串
                if (s[k] != t[k]) {  // 首次出现不同字符
                    return k;  // 公共前缀长度就是 k
                }  // if 结束
            }  // 循环结束
            return m;  // 其中一个是另一个的前缀，取较短串长度
        };  // calc 结束
        for (int i = 0; i + 1 < n; ++i) {  // 枚举初始状态下的每一对相邻字符串
            ms.insert(calc(words[i], words[i + 1]));  // 把这对的 LCP 放入有序多重集
        }  // 循环结束
        vector<int> ans(n);  // 答案数组
        auto add = [&](int i, int j) {  // 下标合法时把一对相邻关系的 LCP 加入多重集
            if (i >= 0 && i < n && j >= 0 && j < n) {  // 两个下标都必须落在 [0, n) 内
                ms.insert(calc(words[i], words[j]));  // 插入这对的 LCP
            }  // if 结束
        };  // add 结束
        auto remove = [&](int i, int j) {  // 下标合法时把一对相邻关系的 LCP 从多重集移除
            if (i >= 0 && i < n && j >= 0 && j < n) {  // 两个下标都必须落在 [0, n) 内
                int x = calc(words[i], words[j]);  // 重新算出这对的 LCP
                auto it = ms.find(x);  // 在多重集中找到该值的一个副本
                if (it != ms.end()) {  // 确实存在这个副本
                    ms.erase(it);  // 只删除找到的这一个副本，保留其余重复值
                }  // if 结束
            }  // if 结束
        };  // remove 结束
        for (int i = 0; i < n; ++i) {  // 枚举被删除（被跳过）的下标 i
            remove(i, i + 1);  // 删除后 (i, i+1) 不再是相邻对
            remove(i - 1, i);  // 删除后 (i-1, i) 也不再是相邻对
            add(i - 1, i + 1);  // 删除 i 后 i-1 与 i+1 变成新的相邻对
            ans[i] = ms.empty() ? 0 : *ms.rbegin();  // 当前所有相邻对 LCP 的最大值即本次答案，空集记 0
            remove(i - 1, i + 1);  // 撤销刚新增的跨过对
            add(i - 1, i);  // 恢复 (i-1, i) 这对相邻关系
            add(i, i + 1);  // 恢复 (i, i+1) 这对相邻关系
        }  // 循环结束
        return ans;  // 返回每个下标对应的答案
    }  // longestCommonPrefix 结束
};  // 类定义结束
