// 题目：1169. 查询无效交易（Invalid Transactions）
// 思路：按姓名分组记录每条交易的 (时间, 城市, 下标)，逐条与该姓名的历史交易比较：金额 > 1000 或 60 分钟内跨城市交易都无效。
// 时间复杂度：O(n^2)，最坏情况同名交易两两比较；空间复杂度：O(n)，哈希分组与无效下标集合都是线性规模。
class Solution {  // 题解类
public:
    vector<string> invalidTransactions(vector<string>& transactions) {  // 找出所有无效交易，按原字符串返回
        unordered_map<string, vector<tuple<int, string, int>>> d;  // 按姓名分组：值是该交易的 (时间, 城市, 下标) 三元组
        unordered_set<int> idx;  // 记录无效交易的下标集合，可自动去重
        for (int i = 0; i < transactions.size(); ++i) {  // 逐条处理交易
            vector<string> e = split(transactions[i], ',');  // 用逗号把一条交易切成四个字段
            string name = e[0];  // 交易人姓名
            int time = stoi(e[1]);  // 交易时间（以分钟计）
            int amount = stoi(e[2]);  // 交易金额
            string city = e[3];  // 交易城市
            d[name].push_back({time, city, i});  // 把本条交易加入该姓名的列表，供后续比对
            if (amount > 1000) {  // 金额超过 1000 的交易必然无效
                idx.insert(i);  // 标记为无效
            }  // if 结束
            for (auto& [t, c, j] : d[name]) {  // 与该姓名已有的所有交易逐一比较
                if (c != city && abs(time - t) <= 60) {  // 城市不同且时间差不超过 60 分钟，说明构成无效
                    idx.insert(i);  // 当前交易无效
                    idx.insert(j);  // 与之冲突的另一条交易也无效
                }  // if 结束
            }  // 内层 for 结束
        }  // 外层 for 结束
        vector<string> ans;  // 存放最终结果
        for (int i : idx) {  // 遍历所有被标记为无效的下标
            ans.emplace_back(transactions[i]);  // 按下标取出原始交易字符串
        }  // for 结束
        return ans;  // 返回结果
    }  // 方法结束

    vector<string> split(string& s, char delim) {  // 按分隔符切分字符串的辅助函数
        stringstream ss(s);  // 用字符串流逐段读取
        string item;  // 存放每次读到的片段
        vector<string> res;  // 存放切分结果
        while (getline(ss, item, delim)) {  // 一直读到流结束
            res.emplace_back(item);  // 收集当前片段
        }  // while 结束
        return res;  // 返回切分结果
    }  // split 方法结束
};  // 类定义结束