// 题目：2125. 银行中的激光束数量（Number of Laser Beams in a Bank）
// 核心思路：逐行用 count 数出 '1' 的个数，非空行才与上一个非空行相乘累加，空行直接跳过。
// 时间复杂度：O(m·n)，每行每格只看一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfBeams(vector<string>& bank) {  // bank 每行是只含 '0'/'1' 的字符串；返回所有激光束的条数
        int ans = 0, pre = 0;  // ans 累计光束总数；pre 是上一个非空行中 '1' 的个数
        for (auto& row : bank) {  // 按顺序逐行扫描整个银行
            int cur = count(row.begin(), row.end(), '1');  // 用 std::count 数出本行字符 '1' 的个数
            if (cur) {  // 本行非空（cur > 0）才参与配对
                ans += pre * cur;  // 上一非空行与本行之间的光束条数：pre × cur
                pre = cur;  // 更新「上一个非空行」，供下一行配对使用
            }
        }
        return ans;  // 返回所有激光束的总条数
    }
};