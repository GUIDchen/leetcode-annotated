// 3484. 设计电子表格 / Design Spreadsheet
// 核心思路：用哈希表保存已设置单元格的名称与数值，getValue 时按 '+' 拆分公式，常量直接转整数、单元格查表取值（未设置视为 0）后累加。
// 复杂度：setCell 与 resetCell 均摊 O(1)，getValue 为 O(L)（L 为公式长度），空间 O(C)（C 为已设置单元格数）。
class Spreadsheet {  // 设计电子表格类
private:  // 私有成员
    unordered_map<string, int> d;  // 哈希表保存单元格名称到数值的映射

public:  // 公有接口
    Spreadsheet(int rows) {}  // 构造函数：题目保证行数范围内可任意操作，只需哈希表即可，无需额外初始化

    void setCell(string cell, int value) {  // 设置单元格的值
        d[cell] = value;  // 直接写入哈希表
    }  // 结束 setCell

    void resetCell(string cell) {  // 清空单元格
        d.erase(cell);  // 从哈希表中删除该键，等价于恢复默认值 0
    }  // 结束 resetCell

    int getValue(string formula) {  // 计算公式的值
        int ans = 0;  // 累加结果，初始为 0
        stringstream ss(formula.substr(1));  // 去掉前导 '='，用字符串流按 '+' 逐段拆分
        string cell;  // 当前待解析的操作数（常量或单元格名）
        while (getline(ss, cell, '+')) {  // 逐个取出以 '+' 分隔的操作数
            if (isdigit(cell[0])) {  // 首字符是数字说明这一段是常量
                ans += stoi(cell);  // 常量直接转成整数累加
            } else {  // 否则这一段是单元格名称
                ans += d.count(cell) ? d[cell] : 0;  // 已设置的单元格取其值，未设置按 0 计
            }  // 结束操作数类型判断
        }  // 结束公式解析循环
        return ans;  // 返回公式计算结果
    }  // 结束 getValue
};  // 结束 Spreadsheet 类

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */
