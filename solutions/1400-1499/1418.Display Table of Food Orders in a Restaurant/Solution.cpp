// 题目：1418. 点菜展示表（Display Table of Food Orders in a Restaurant）
// 核心思路：用 map 按桌号归组并保持桌号升序，用 set 收集菜名并保持字典序，再逐桌统计每道菜的点单次数填成二维表。
// 时间复杂度：O(n log T + T·log m + n + T·m)，n 为订单数、T 为桌数、m 为菜品种类数；空间复杂度：O(n + T·m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {  // orders：每个元素形如 [顾客名, 桌号字符串, 菜名]
        map<int, vector<string>> tables;  // 桌号 → 该桌的点单菜名列表；map 让桌号天然按数值升序
        set<string> sortedItems;  // 菜名集合；set 自动按字典序排列，用来生成表头并决定每列的先后
        for (auto& o : orders) {  // 逐条订单扫描
            int table = stoi(o[1]);  // 把订单里的字符串桌号转成整数，方便按数值排序
            string foodItem = o[2];  // 取出这一单点的菜名
            tables[table].push_back(foodItem);  // 把菜名记到该桌名下；同桌重复点同一道菜就重复记一次
            sortedItems.insert(foodItem);  // 菜名存入集合去重，最终得到所有出现过的菜
        }  // 订单遍历结束
        vector<vector<string>> ans;  // 结果二维表：首行是表头，其后每行对应一张桌
        vector<string> header = {"Table"};  // 表头第一格固定为字符串 Table
        header.insert(header.end(), sortedItems.begin(), sortedItems.end());  // 把排好序的菜名依次追加到表头后面
        ans.push_back(header);  // 表头作为结果的第一行
        for (auto& [table, items] : tables) {  // 按桌号升序遍历；结构化绑定同时取出桌号与该桌的菜名列表
            unordered_map<string, int> cnt;  // 临时统计当前桌每道菜被点了几次
            for (string& item : items) {  // 遍历该桌的全部点单记录
                cnt[item]++;  // 同一道菜每出现一次，计数加一
            }  // 该桌记录统计完毕
            vector<string> row;  // 当前桌要输出的一整行
            row.push_back(to_string(table));  // 第一列是桌号，需要再转回字符串
            for (const string& item : sortedItems) {  // 按表头的菜名顺序逐列填写
                row.push_back(to_string(cnt[item]));  // 该桌没点过的菜计数为 0，也要填 "0" 占位
            }  // 该桌各列填完
            ans.push_back(row);  // 该桌这一行追加到结果中
        }  // 所有桌处理完毕
        return ans;  // 返回表头行加上所有桌的统计行
    }  // 方法结束
};  // 题解类定义结束
