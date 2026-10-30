// 题目：1152. 用户网站访问行为分析（Analyze User Website Visit Pattern）
// 思路：先按用户分组并按时间戳排序，枚举每个用户访问序列的所有三元组并去重，统计每个三元组被多少用户使用，取次数最多且字典序最小的。
// 时间复杂度：O(U * m^3)，U 为用户数、m 为单用户访问数；空间复杂度：O(不同三元组个数)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {  // username / timestamp / website 是三个平行数组
        unordered_map<string, vector<pair<int, string>>> d;  // 键是用户名，值是该用户按时间排列的 (时间戳, 网站) 列表
        int n = username.size();  // 访问记录条数
        for (int i = 0; i < n; ++i) {  // 逐条遍历访问记录
            auto user = username[i];  // 当前记录的用户名
            int ts = timestamp[i];  // 当前记录的时间戳
            auto site = website[i];  // 当前记录访问的网站
            d[user].emplace_back(ts, site);  // 按用户分组保存
        }  // 分组结束
        unordered_map<string, int> cnt;  // cnt 统计每个三元组被多少个不同用户访问过
        for (auto& [_, sites] : d) {  // 遍历每个用户的访问列表（结构化绑定，_ 是用户名）
            int m = sites.size();  // 该用户访问的网站个数
            unordered_set<string> s;  // 用集合去重：同一用户重复的三元组只计一次
            if (m > 2) {  // 至少访问 3 次才可能产生三元组
                sort(sites.begin(), sites.end());  // 按时间戳排序，得到真实的访问先后顺序
                for (int i = 0; i < m - 2; ++i) {  // 枚举三元组的第一个位置
                    for (int j = i + 1; j < m - 1; ++j) {  // 第二个位置
                        for (int k = j + 1; k < m; ++k) {  // 第三个位置
                            s.insert(sites[i].second + "," + sites[j].second + "," + sites[k].second);  // 用逗号拼成字符串，插入集合完成去重
                        }  // 第三层循环结束
                    }  // 第二层循环结束
                }  // 第一层循环结束
            }  // if 结束
            for (auto& t : s) {  // 该用户贡献的所有不同三元组
                cnt[t]++;  // 对应三元组的用户数加一
            }  // 用户循环结束
        }  // 全部用户统计完毕
        int mx = 0;  // mx 记录最多的用户数
        string t;  // t 记录答案三元组字符串
        for (auto& [p, v] : cnt) {  // 遍历统计结果
            if (mx < v || (mx == v && t > p)) {  // 次数更多，或次数相同但字典序更小，就更新答案
                mx = v;  // 更新最大次数
                t = p;  // 更新答案字符串
            }  // if 结束
        }  // 遍历结束
        return split(t, ',');  // 把逗号分隔的字符串还原成 3 个网站名
    }  // 方法结束

    vector<string> split(string& s, char c) {  // 按分隔符 c 切分字符串
        vector<string> res;  // 保存切分结果的数组
        stringstream ss(s);  // 用字符串流逐个读取片段
        string t;  // 存放每次切出的片段
        while (getline(ss, t, c)) {  // 逐段读取
            res.push_back(t);  // 收集当前片段
        }  // 读取结束
        return res;  // 返回切分结果
    }  // split 结束
};  // 类定义结束