// 题目：2408. 设计 SQL（Design SQL）
// 思路：用哈希表记录每张表的列数、行号计数器与行数据；插入时校验列数，查询时定位行与列并做越界保护，导出时按行号升序拼接。
// 时间复杂度：C++ 因行表用有序 map，ins/rmv/sel 为 O(log r)，exp 为 O(r*c)；Python 的 ins/rmv/sel 平均 O(1)，exp 为 O(r log r + r*c)；空间复杂度：O(r*c)，r 为行数、c 为列数。
class SQL {  // 设计类：用哈希表模拟多张表的元数据与行数据
public:  // 成员对外公开，便于判题器直接调用
    unordered_map<string, int> cols;  // 表名 → 该表的列数
    unordered_map<string, map<int, vector<string>>> rows;  // 表名 → (行号 → 该行所有单元格)；行号用有序 map 便于导出时排序
    unordered_map<string, int> nxt;  // 表名 → 下一个可分配的行号

    SQL(vector<string>& names, vector<int>& columns) {  // names：表名列表；columns：每张表对应的列数
        for (int i = 0; i < (int) names.size(); ++i) {  // 逐张表完成初始化
            cols[names[i]] = columns[i];  // 记录该表的列数，供插入时校验
            nxt[names[i]] = 1;  // 行号从 1 开始分配
        }  // 初始化循环结束
    }  // 构造函数结束

    bool ins(string name, vector<string> row) {  // 插入一行：表名与该行每个单元格的内容
        if (!cols.count(name) || (int) row.size() != cols[name]) {  // 表不存在，或者给出的列数与该表不一致，属于非法插入
            return false;  // 按题意返回失败
        }  // 合法性校验分支结束
        int id = nxt[name]++;  // 取出当前可用的行号，并把计数器后移
        rows[name][id] = std::move(row);  // 用移动语义存入该行，避免再拷贝一次整行
        return true;  // 插入成功
    }  // ins 结束

    void rmv(string name, int rowId) {  // 删除指定表的指定行
        if (rows.count(name)) {  // 表存在时才需要处理
            rows[name].erase(rowId);  // map 的 erase 对不存在的键是安全的，无需额外判断
        }  // 分支结束
    }  // rmv 结束

    string sel(string name, int rowId, int columnId) {  // 查询某行某列的单元格内容
        if (!rows.count(name) || !rows[name].count(rowId)) {  // 表不存在或者该行不存在
            return "<null>";  // 按题目约定返回空值标记
        }  // 校验分支结束
        auto& row = rows[name][rowId];  // 引用该行，避免拷贝整行数据
        if (columnId < 1 || columnId > (int) row.size()) {  // 列号越界（题目列号从 1 开始）
            return "<null>";  // 同样返回空值标记
        }  // 校验分支结束
        return row[columnId - 1];  // 列号转成从 0 开始的下标后取值
    }  // sel 结束

    vector<string> exp(string name) {  // 导出整张表：每行拼成 id,单元格1,单元格2,... 的形式
        vector<string> ans;  // 保存导出的所有行
        if (!rows.count(name)) {  // 表不存在时导出空列表
            return ans;  // 提前返回空结果
        }  // 分支结束
        for (auto& [id, row] : rows[name]) {  // map 有序，按行号从小到大遍历
            string s = to_string(id);  // 每行以行号开头
            for (auto& cell : row) {  // 依次拼接该行的每个单元格
                s += "," + cell;  // 用逗号分隔各列
            }  // 内层遍历结束
            ans.push_back(s);  // 收下这一行拼好的字符串
        }  // 外层遍历结束
        return ans;  // 返回导出的全部行
    }  // exp 结束
};  // SQL 类定义结束

// 以下是判题器的使用示例，整段都是注释，保持原样不改动
/**
 * Your SQL object will be instantiated and called as such:
 * SQL* obj = new SQL(names, columns);
 * bool param_1 = obj->ins(name,row);
 * obj->rmv(name,rowId);
 * string param_3 = obj->sel(name,rowId,columnId);
 * vector<string> param_4 = obj->exp(name);
 */
