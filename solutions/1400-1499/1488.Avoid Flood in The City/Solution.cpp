// 题目：1488. 避免洪水泛滥（Avoid Flood in The City）
// 核心思路：贪心 + 有序集合。某湖第二次下雨前，必须用上次下雨之后最早的那个晴天把水抽干；找不到可用晴天即无解。
// 时间复杂度：O(n log n)，每次上下界查找与删除是对数级；空间复杂度：O(n)，集合与哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> avoidFlood(vector<int>& rains) {  // rains[i]：第 i 天降雨的湖编号，0 表示晴天
        int n = rains.size();  // 总天数
        vector<int> ans(n, -1);  // 结果数组，雨天默认填 -1
        set<int> sunny;  // 有序集合：记录所有尚未使用的晴天日期
        unordered_map<int, int> rainy;  // 哈希表：湖编号 → 最近一次下雨的日期
        for (int i = 0; i < n; ++i) {  // 逐天模拟
            int v = rains[i];  // 当天的湖编号，0 表示晴天
            if (v) {  // 非 0 即下雨天
                if (rainy.count(v)) {  // 该湖之前下过雨，必须在两次降雨之间抽干
                    auto it = sunny.upper_bound(rainy[v]);  // 取上一个雨天之后的第一个可用晴天（贪心选最早的那个最稳）
                    if (it == sunny.end()) {  // 后面没有可用的晴天
                        return {};  // 返回空数组表示无法避免洪水
                    }  // if (it == sunny.end()) 分支结束
                    ans[*it] = v;  // 把这一天安排为抽干湖 v
                    sunny.erase(it);  // 该晴天已被占用，从集合中移除
                }  // if (rainy.count(v)) 分支结束
                rainy[v] = i;  // 更新该湖最近一次下雨的日期
            } else {  // 否则是晴天
                sunny.insert(i);  // 先记入可用晴天集合，留待以后抽水
                ans[i] = 1;  // 空闲晴天填任意正数即可，这里填 1
            }  // else 分支结束
        }  // for 循环结束
        return ans;  // 返回合法的抽水方案
    }  // 方法结束
};  // Solution 类定义结束