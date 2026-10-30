// 题目：2194. Excel 表中某个范围内的单元格（Cells in a Range on an Excel Sheet）
// 思路：区间串形如 K1:L2，两层循环分别枚举列字母与行号，按“先列后行”的顺序拼出每个单元格名。
// 时间复杂度：O(rows·cols)，即区间内单元格个数；空间复杂度：O(1)，不计返回结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> cellsInRange(string s) {  // s 形如 K1:L2，s[0]/s[1] 是起点列与行，s[3]/s[4] 是终点列与行
        vector<string> ans;  // 保存按列优先顺序排列的单元格名称
        for (char i = s[0]; i <= s[3]; ++i) {  // 列字母从起点列枚举到终点列（字符按编码有序）
            for (char j = s[1]; j <= s[4]; ++j) {  // 行号从起点行枚举到终点行
                ans.push_back({i, j});  // 列字母加行号字符拼出单元格名，例如 A1
            }  // 内层 for 结束
        }  // 外层 for 结束
        return ans;  // 返回结果
    }  // 方法结束
};  // 类定义结束