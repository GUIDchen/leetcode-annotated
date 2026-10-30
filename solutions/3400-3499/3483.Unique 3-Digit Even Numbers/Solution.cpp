// 3483. 不同三位偶数的数目 / Unique 3-Digit Even Numbers
// 核心思路：枚数百位、十位、个位的下标组合，个位必须是偶数且百位不能为 0，把拼出的三位数放入哈希集合去重后统计个数。
// 复杂度：时间 O(n^3)，空间 O(n^3)（去重集合最多存 n^3 个数）。
class Solution {  // 定义题解类
public:  // 公有接口
    int totalNumbers(vector<int>& digits) {  // 主函数：返回能组成的不同三位偶数的数目
        unordered_set<int> s;  // 哈希集合用于对构造出的三位数按数值去重
        int n = digits.size();  // 可选数字的个数
        for (int i = 0; i < n; ++i) {  // 枚举个位数字的下标 i
            if (digits[i] % 2 == 1) {  // 个位必须是偶数，奇数直接跳过
                continue;  // 跳过这个奇数个位
            }  // 结束个位奇偶判断
            for (int j = 0; j < n; ++j) {  // 枚举十位数字的下标 j
                if (i == j) {  // 十位与个位不能使用同一下标
                    continue;  // 跳过下标冲突的情况
                }  // 结束下标冲突判断
                for (int k = 0; k < n; ++k) {  // 枚举百位数字的下标 k
                    if (digits[k] == 0 || k == i || k == j) {  // 百位不能为 0，且不能与已用的个位、十位下标重复
                        continue;  // 跳过不合法的百位
                    }  // 结束百位合法性判断
                    s.insert(digits[k] * 100 + digits[j] * 10 + digits[i]);  // 拼成三位数并插入集合，重复值自动去重
                }  // 结束百位枚举
            }  // 结束十位枚举
        }  // 结束个位枚举
        return s.size();  // 集合大小即不同三位偶数的数目
    }  // 结束 totalNumbers
};  // 结束 Solution 类
